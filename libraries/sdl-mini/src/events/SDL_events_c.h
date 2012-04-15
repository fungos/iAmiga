//
//  SDL_events_c.h
//  iAmiga
//
//  Created by Stuart Carnie on 6/5/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#include "SDL_config.h"

/* Useful functions and variables from SDL_events.c */
#include "SDL_events.h"
#include "SDL_thread.h"
#include "SDL_mouse_c.h"

/* Start and stop the event processing loop */
extern int SDL_StartEventLoop(Uint32 flags);
extern void SDL_StopEventLoop(void);

extern void SDL_Lock_EventThread(void);
extern void SDL_Unlock_EventThread(void);
extern SDL_threadID SDL_EventThreadID(void);

/* The event filter function */
extern SDL_EventFilter SDL_EventOK;
extern void *SDL_EventOKParam;
