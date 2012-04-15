//
//  sdl_event.h
//  A2600
//
//  Created by Stuart Carnie on 10/10/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#ifndef _SDL_events_h
#define _SDL_events_h

#include "SDL_stdinc.h"
#include "SDL_video.h"
#include "SDL_keyboard.h"
#include "SDL_mouse.h"
#include "SDL_joystick.h"

#ifdef __cplusplus
/* *INDENT-OFF* */
extern "C" {
    /* *INDENT-ON* */
#endif


/* General keyboard/mouse state definitions */
#define SDL_RELEASED	0
#define SDL_PRESSED		1

/**
 * \brief The types of events that can be delivered.
 */
typedef enum
{
    SDL_FIRSTEVENT     = 0,     /**< Unused (do not remove) */
    
    /* Application events */
    SDL_QUIT           = 0x100, /**< User-requested quit */
    
    /* Window events */
    SDL_WINDOWEVENT    = 0x200, /**< Window state change */
    SDL_SYSWMEVENT,             /**< System specific event */
    
    /* Keyboard events */
    SDL_KEYDOWN        = 0x300, /**< Keys pressed */
    SDL_KEYUP,                  /**< Keys released */
    SDL_TEXTEDITING,            /**< Keyboard text editing (composition) */
    SDL_TEXTINPUT,              /**< Keyboard text input */
    
    /* Mouse events */
    SDL_MOUSEMOTION    = 0x400, /**< Mouse moved */
    SDL_MOUSEBUTTONDOWN,        /**< Mouse button pressed */
    SDL_MOUSEBUTTONUP,          /**< Mouse button released */
    SDL_MOUSEWHEEL,             /**< Mouse wheel motion */
    
    /* Tablet or multiple mice input device events */
    SDL_INPUTMOTION    = 0x500, /**< Input moved */
    SDL_INPUTBUTTONDOWN,        /**< Input button pressed */
    SDL_INPUTBUTTONUP,          /**< Input button released */
    SDL_INPUTWHEEL,             /**< Input wheel motion */
    SDL_INPUTPROXIMITYIN,       /**< Input pen entered proximity */
    SDL_INPUTPROXIMITYOUT,      /**< Input pen left proximity */
    
    /* Joystick events */
    SDL_JOYAXISMOTION  = 0x600, /**< Joystick axis motion */
    SDL_JOYBALLMOTION,          /**< Joystick trackball motion */
    SDL_JOYHATMOTION,           /**< Joystick hat position change */
    SDL_JOYBUTTONDOWN,          /**< Joystick button pressed */
    SDL_JOYBUTTONUP,            /**< Joystick button released */
    
    /* Touch events */
    SDL_FINGERDOWN      = 0x700,
    SDL_FINGERUP,
    SDL_FINGERMOTION,
    SDL_TOUCHBUTTONDOWN,
    SDL_TOUCHBUTTONUP,    
    
    /* Gesture events */
    SDL_DOLLARGESTURE   = 0x800,
    SDL_DOLLARRECORD,
    SDL_MULTIGESTURE,
    
    /* Clipboard events */
    
    SDL_CLIPBOARDUPDATE = 0x900, /**< The clipboard changed */
    
    /* Obsolete events */
    SDL_EVENT_COMPAT1 = 0x7000, /**< SDL 1.2 events for compatibility */
    SDL_EVENT_COMPAT2,
    SDL_EVENT_COMPAT3,
    
    
    /** Events ::SDL_USEREVENT through ::SDL_LASTEVENT are for your use,
     *  and should be allocated with SDL_RegisterEvents()
     */
    SDL_USEREVENT    = 0x8000,
    
    /**
     *  This last event is only for bounding internal arrays
     */
    SDL_LASTEVENT    = 0xFFFF
} SDL_EventType;

typedef struct SDL_MouseMotionEvent {
	Uint32 type;
	Uint8 state;        /**< The current button state */
	Uint8 padding1;        /**< The current button state */
	Uint8 padding2;        /**< The current button state */
	Uint8 padding3;        /**< The current button state */

	int x,y;
	int xrel, yrel;
} SDL_MouseMotionEvent;

typedef struct SDL_MouseButtonEvent {
	Uint32 type;
	Uint8 button;
	Uint8 state;
	
	int x,y;
} SDL_MouseButtonEvent;

typedef struct SDL_KeyboardEvent {
	Uint32			type;
	SDL_keysym      keysym;
} SDL_KeyboardEvent;

/**
 * \struct SDL_JoyAxisEvent
 *
 * \brief Joystick axis motion event structure (event.jaxis.*)
 */
typedef struct SDL_JoyAxisEvent
{
	Uint32 type;         /**< SDL_JOYAXISMOTION */
	Uint8 which;        /**< The joystick device index */
	Uint8 axis;         /**< The joystick axis index */
	int value;          /**< The axis value (range: -32768 to 32767) */
} SDL_JoyAxisEvent;

/**
 * \struct SDL_JoyBallEvent
 *
 * \brief Joystick trackball motion event structure (event.jball.*)
 */
typedef struct SDL_JoyBallEvent
{
	Uint32 type;         /**< SDL_JOYBALLMOTION */
	Uint8 which;        /**< The joystick device index */
	Uint8 ball;         /**< The joystick trackball index */
	int xrel;           /**< The relative motion in the X direction */
	int yrel;           /**< The relative motion in the Y direction */
} SDL_JoyBallEvent;

/**
 * \struct SDL_JoyHatEvent
 *
 * \brief Joystick hat position change event structure (event.jhat.*)
 */
typedef struct SDL_JoyHatEvent
{
	Uint32 type;         /**< SDL_JOYHATMOTION */
	Uint8 which;        /**< The joystick device index */
	Uint8 hat;          /**< The joystick hat index */
	Uint8 value;        /**< The hat position value:
						 SDL_HAT_LEFTUP   SDL_HAT_UP       SDL_HAT_RIGHTUP
						 SDL_HAT_LEFT     SDL_HAT_CENTERED SDL_HAT_RIGHT
						 SDL_HAT_LEFTDOWN SDL_HAT_DOWN     SDL_HAT_RIGHTDOWN
						 Note that zero means the POV is centered.
						 */
} SDL_JoyHatEvent;

/**
 * \struct SDL_JoyButtonEvent
 *
 * \brief Joystick button event structure (event.jbutton.*)
 */
typedef struct SDL_JoyButtonEvent
{
	Uint32 type;         /**< SDL_JOYBUTTONDOWN or SDL_JOYBUTTONUP */
	Uint8 which;        /**< The joystick device index */
	Uint8 button;       /**< The joystick button index */
	Uint8 state;        /**< SDL_PRESSED or SDL_RELEASED */
} SDL_JoyButtonEvent;

typedef union SDL_Event {
	Uint32 type;
	SDL_KeyboardEvent key;
	SDL_MouseMotionEvent motion;
	SDL_MouseButtonEvent button;
	SDL_JoyAxisEvent jaxis;         /**< Joystick axis event data */
	SDL_JoyBallEvent jball;         /**< Joystick ball event data */
	SDL_JoyHatEvent jhat;           /**< Joystick hat event data */
	SDL_JoyButtonEvent jbutton;
} SDL_Event;

/* Function prototypes */

/**
 *  Pumps the event loop, gathering events from the input devices.
 *  
 *  This function updates the event queue and internal input device state.
 *  
 *  This should only be run in the thread that sets the video mode.
 */
extern void SDL_PumpEvents(void);
    
typedef enum
{
    SDL_ADDEVENT,
    SDL_PEEKEVENT,
    SDL_GETEVENT
} SDL_eventaction;

/**
 *  Checks the event queue for messages and optionally returns them.
 *  
 *  If \c action is ::SDL_ADDEVENT, up to \c numevents events will be added to
 *  the back of the event queue.
 *  
 *  If \c action is ::SDL_PEEKEVENT, up to \c numevents events at the front
 *  of the event queue, within the specified minimum and maximum type,
 *  will be returned and will not be removed from the queue.
 *  
 *  If \c action is ::SDL_GETEVENT, up to \c numevents events at the front 
 *  of the event queue, within the specified minimum and maximum type,
 *  will be returned and will be removed from the queue.
 *  
 *  \return The number of events actually stored, or -1 if there was an error.
 *  
 *  This function is thread-safe.
 */
extern DECLSPEC int SDLCALL SDL_PeepEvents(SDL_Event * events, int numevents,
                                           SDL_eventaction action,
                                           Uint32 minType, Uint32 maxType);
/*@}*/

/**
 *  Checks to see if certain event types are in the event queue.
 */
extern DECLSPEC SDL_bool SDLCALL SDL_HasEvent(Uint32 type);
extern DECLSPEC SDL_bool SDLCALL SDL_HasEvents(Uint32 minType, Uint32 maxType);

/**
 *  This function clears events from the event queue
 */
extern DECLSPEC void SDLCALL SDL_FlushEvent(Uint32 type);
extern DECLSPEC void SDLCALL SDL_FlushEvents(Uint32 minType, Uint32 maxType);

/**
 *  \brief Polls for currently pending events.
 *  
 *  \return 1 if there are any pending events, or 0 if there are none available.
 *  
 *  \param event If not NULL, the next event is removed from the queue and 
 *               stored in that area.
 */
extern int SDL_PollEvent(SDL_Event *eevent);

/**
 *  \brief Waits until the specified timeout (in milliseconds) for the next 
 *         available event.
 *  
 *  \return 1, or 0 if there was an error while waiting for events.
 *  
 *  \param event If not NULL, the next event is removed from the queue and 
 *               stored in that area.
 */
extern DECLSPEC int SDLCALL SDL_WaitEventTimeout(SDL_Event * event,
                                                 int timeout);    
/**
 *  \brief Add an event to the event queue.
 *  
 *  \return 1 on success, 0 if the event was filtered, or -1 if the event queue 
 *          was full or there was some other error.
 */
extern int SDL_PushEvent(SDL_Event *event);

typedef int (SDLCALL * SDL_EventFilter) (void *userdata, SDL_Event * event);
    
#define SDL_QUERY	-1
#define SDL_IGNORE	 0
#define SDL_DISABLE	 0
#define SDL_ENABLE	 1

/**
 *  This function allows you to set the state of processing certain events.
 *   - If \c state is set to ::SDL_IGNORE, that event will be automatically 
 *     dropped from the event queue and will not event be filtered.
 *   - If \c state is set to ::SDL_ENABLE, that event will be processed 
 *     normally.
 *   - If \c state is set to ::SDL_QUERY, SDL_EventState() will return the 
 *     current processing state of the specified event.
 */
extern DECLSPEC Uint8 SDLCALL SDL_EventState(Uint32 type, int state);
/*@}*/
#define SDL_GetEventState(type) SDL_EventState(type, SDL_QUERY)

    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
    /* *INDENT-OFF* */
}
/* *INDENT-ON* */
#endif


#endif