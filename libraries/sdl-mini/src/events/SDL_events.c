//
//  sdl_event.m
//  A2600
//
//  Created by Stuart Carnie on 10/10/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//
#include "SDL_config.h"

/* General event handling code for SDL */

#include "SDL.h"
#include "SDL_events.h"
#include "SDL_sysevents.h"
#include "SDL_events_c.h"

#include "../joystick/SDL_joystick_c.h"

/* Public data -- the event filter */
//SDL_EventFilter SDL_EventOK = NULL;
void *SDL_EventOKParam;

typedef struct {
    Uint32 bits[8];
} SDL_DisabledEventBlock;

static SDL_DisabledEventBlock *SDL_disabled_events[256];
static Uint32 SDL_userevents = SDL_USEREVENT;


/* Private data -- event queue */
#define MAXEVENTS	128
static struct
{
    SDL_mutex *lock;
    int active;
    int head;
    int tail;
    SDL_Event event[MAXEVENTS];
} SDL_EventQ;

/* Private data -- event locking structure */
static struct
{
    SDL_mutex *lock;
    int safe;
} SDL_EventLock;

/* Thread functions */
static SDL_Thread *SDL_EventThread = NULL;      /* Thread handle */
static SDL_threadID event_thread;     /* The event thread id */

void SDL_Lock_EventThread(void) {
}

void SDL_Unlock_EventThread(void) {
}

static __inline__ SDL_bool
SDL_ShouldPollJoystick()
{
#if !SDL_JOYSTICK_DISABLED
    if (SDL_numjoysticks &&
        (!SDL_disabled_events[SDL_JOYAXISMOTION >> 8] ||
         SDL_JoystickEventState(SDL_QUERY))) {
            return SDL_TRUE;
        }
#endif
    return SDL_FALSE;

}

static int
SDL_StartEventThread(Uint32 flags)
{
    /* Reset everything to zero */
    SDL_EventThread = NULL;
    SDL_memset(&SDL_EventLock, 0, sizeof(SDL_EventLock));
    
    /* Create the lock and set ourselves active */
#if !SDL_THREADS_DISABLED
    SDL_EventQ.lock = SDL_CreateMutex();
    if (SDL_EventQ.lock == NULL) {
        return (-1);
    }
#endif /* !SDL_THREADS_DISABLED */
    SDL_EventQ.active = 1;
    
    if ((flags & SDL_INIT_EVENTTHREAD) == SDL_INIT_EVENTTHREAD) {
    } else {
        event_thread = 0;
    }
    return (0);
}

static void
SDL_StopEventThread(void)
{
    SDL_EventQ.active = 0;
    if (SDL_EventQ.lock) {
        SDL_DestroyMutex(SDL_EventQ.lock);
        SDL_EventQ.lock = NULL;
    }
}

SDL_threadID
SDL_EventThreadID(void)
{
    return (event_thread);
}

void
SDL_StopEventLoop(void)
{
    int i;
    
    /* Halt the event thread, if running */
    SDL_StopEventThread();
    
    
    /* Clean out EventQ */
    SDL_EventQ.head = 0;
    SDL_EventQ.tail = 0;
    
    /* Clear disabled event state */
    for (i = 0; i < SDL_arraysize(SDL_disabled_events); ++i) {
        if (SDL_disabled_events[i]) {
            SDL_free(SDL_disabled_events[i]);
            SDL_disabled_events[i] = NULL;
        }
    }
}

/* This function (and associated calls) may be called more than once */
int
SDL_StartEventLoop(Uint32 flags)
{
	//queueLock = [NSRecursiveLock new];
	//eventQueue = new queue<SDL_Event>();
	//return 0;
    
    /* Clean out the event queue */
    SDL_EventThread = NULL;
    SDL_EventQ.lock = NULL;
    SDL_StopEventLoop();

    /* Create the lock and event thread */
    if (SDL_StartEventThread(flags) < 0) {
        SDL_StopEventLoop();
        return (-1);
    }
    return (0);

}

/* Add an event to the event queue -- called with the queue locked */
static int
SDL_AddEvent(SDL_Event * event)
{
    int tail, added;
    
    tail = (SDL_EventQ.tail + 1) % MAXEVENTS;
    if (tail == SDL_EventQ.head) {
        /* Overflow, drop event */
        added = 0;
    } else {
        SDL_EventQ.event[SDL_EventQ.tail] = *event;
        SDL_EventQ.tail = tail;
        added = 1;
    }
    return (added);
}

/* Cut an event, and return the next valid spot, or the tail */
/*                           -- called with the queue locked */
static int
SDL_CutEvent(int spot)
{
    if (spot == SDL_EventQ.head) {
        SDL_EventQ.head = (SDL_EventQ.head + 1) % MAXEVENTS;
        return (SDL_EventQ.head);
    } else if ((spot + 1) % MAXEVENTS == SDL_EventQ.tail) {
        SDL_EventQ.tail = spot;
        return (SDL_EventQ.tail);
    } else
    /* We cut the middle -- shift everything over */
    {
        int here, next;
        
        /* This can probably be optimized with SDL_memcpy() -- careful! */
        if (--SDL_EventQ.tail < 0) {
            SDL_EventQ.tail = MAXEVENTS - 1;
        }
        for (here = spot; here != SDL_EventQ.tail; here = next) {
            next = (here + 1) % MAXEVENTS;
            SDL_EventQ.event[here] = SDL_EventQ.event[next];
        }
        return (spot);
    }
    /* NOTREACHED */
}

/* Lock the event queue, take a peep at it, and unlock it */
int
SDL_PeepEvents(SDL_Event * events, int numevents, SDL_eventaction action,
               Uint32 minType, Uint32 maxType)
{
    int i, used;
    
    /* Don't look after we've quit */
    if (!SDL_EventQ.active) {
        return (-1);
    }
    /* Lock the event queue */
    used = 0;
    if (SDL_mutexP(SDL_EventQ.lock) == 0) {
        if (action == SDL_ADDEVENT) {
            for (i = 0; i < numevents; ++i) {
                used += SDL_AddEvent(&events[i]);
            }
        } else {
            SDL_Event tmpevent;
            int spot;
            
            /* If 'events' is NULL, just see if they exist */
            if (events == NULL) {
                action = SDL_PEEKEVENT;
                numevents = 1;
                events = &tmpevent;
            }
            spot = SDL_EventQ.head;
            while ((used < numevents) && (spot != SDL_EventQ.tail)) {
                Uint32 type = SDL_EventQ.event[spot].type;
                if (minType <= type && type <= maxType) {
                    events[used++] = SDL_EventQ.event[spot];
                    if (action == SDL_GETEVENT) {
                        spot = SDL_CutEvent(spot);
                    } else {
                        spot = (spot + 1) % MAXEVENTS;
                    }
                } else {
                    spot = (spot + 1) % MAXEVENTS;
                }
            }
        }
        SDL_mutexV(SDL_EventQ.lock);
    } else {
        SDL_SetError("Couldn't lock event queue");
        used = -1;
    }
    return (used);
}

SDL_bool
SDL_HasEvent(Uint32 type)
{
    return (SDL_PeepEvents(NULL, 0, SDL_PEEKEVENT, type, type) > 0);
}

SDL_bool
SDL_HasEvents(Uint32 minType, Uint32 maxType)
{
    return (SDL_PeepEvents(NULL, 0, SDL_PEEKEVENT, minType, maxType) > 0);
}

void
SDL_FlushEvent(Uint32 type)
{
    SDL_FlushEvents(type, type);
}

void
SDL_FlushEvents(Uint32 minType, Uint32 maxType)
{
    /* Don't look after we've quit */
    if (!SDL_EventQ.active) {
        return;
    }
    
    /* Make sure the events are current */
    SDL_PumpEvents();
    
    /* Lock the event queue */
    if (SDL_mutexP(SDL_EventQ.lock) == 0) {
        int spot = SDL_EventQ.head;
        while (spot != SDL_EventQ.tail) {
            Uint32 type = SDL_EventQ.event[spot].type;
            if (minType <= type && type <= maxType) {
                spot = SDL_CutEvent(spot);
            } else {
                spot = (spot + 1) % MAXEVENTS;
            }
        }
        SDL_mutexV(SDL_EventQ.lock);
    }
}

void SDL_PumpEvents(void) {
    //if (!SDL_EventThread) {
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    
    /* Get events from the video subsystem */
    if (_this) {
        _this->PumpEvents(_this);
    }
#if !SDL_JOYSTICK_DISABLED
    /* Check for joystick state change */
    if (SDL_ShouldPollJoystick()) {
        SDL_JoystickUpdate();
    }
#endif
    //}
    
}

/* Public functions */

int
SDL_PollEvent(SDL_Event * event)
{
    return SDL_WaitEventTimeout(event, 0);
}

int
SDL_WaitEvent(SDL_Event * event)
{
    return SDL_WaitEventTimeout(event, -1);
}

int
SDL_WaitEventTimeout(SDL_Event * event, int timeout)
{
    Uint32 expiration = 0;
    
    if (timeout > 0)
        expiration = SDL_GetTicks() + timeout;
    
    for (;;) {
        SDL_PumpEvents();
        switch (SDL_PeepEvents(event, 1, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT)) {
            case -1:
                return 0;
            case 1:
                return 1;
            case 0:
                if (timeout == 0) {
                    /* Polling and no events, just return */
                    return 0;
                }
                if (timeout > 0 && ((int) (SDL_GetTicks() - expiration) >= 0)) {
                    /* Timeout expired and no events */
                    return 0;
                }
                SDL_Delay(10);
                break;
        }
    }
}

int
SDL_PushEvent(SDL_Event * event)
{
    //if (SDL_EventOK && !SDL_EventOK(SDL_EventOKParam, event)) {
    //    return 0;
    //}
    if (SDL_PeepEvents(event, 1, SDL_ADDEVENT, 0, 0) <= 0) {
        return -1;
    }
    
    // SDL_GestureProcessEvent(event);
    
    
    return 1;
}

Uint8
SDL_EventState(Uint32 type, int state)
{
    Uint8 current_state;
    Uint8 hi = ((type >> 8) & 0xff);
    Uint8 lo = (type & 0xff);
    
    if (SDL_disabled_events[hi] &&
        (SDL_disabled_events[hi]->bits[lo/32] & (1 << (lo&31)))) {
        current_state = SDL_DISABLE;
    } else {
        current_state = SDL_ENABLE;
    }
    
    if (state != current_state)
    {
        switch (state) {
            case SDL_DISABLE:
                /* Disable this event type and discard pending events */
                if (!SDL_disabled_events[hi]) {
                    SDL_disabled_events[hi] = (SDL_DisabledEventBlock*) SDL_calloc(1, sizeof(SDL_DisabledEventBlock));
                    if (!SDL_disabled_events[hi]) {
                        /* Out of memory, nothing we can do... */
                        break;
                    }
                }
                SDL_disabled_events[hi]->bits[lo/32] |= (1 << (lo&31));
                SDL_FlushEvent(type);
                break;
            case SDL_ENABLE:
                SDL_disabled_events[hi]->bits[lo/32] &= ~(1 << (lo&31));
                break;
            default:
                /* Querying state... */
                break;
        }
    }
    
    return current_state;
}


/*
int SDL_PushEvent(SDL_Event *e) {
	CNSRecursiveLock autolock(queueLock);	// this ensures the lock is released on function exit	
	eventQueue->push(*e);
	return 1;
} */
