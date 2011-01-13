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


/* General keyboard/mouse state definitions */
#define SDL_RELEASED	0
#define SDL_PRESSED		1

/* Event enumerations */
typedef enum { 
	SDL_NOEVENT = 0,                 /* Unused (do not remove) */
	SDL_ACTIVEEVENT,                 /* Application loses/gains visibility */
	SDL_KEYDOWN,                     /* Keys pressed */
	SDL_KEYUP,                       /* Keys released */
	SDL_MOUSEMOTION,                 /* Mouse moved */
	SDL_MOUSEBUTTONDOWN,             /* Mouse button pressed */
	SDL_MOUSEBUTTONUP,               /* Mouse button released */
	SDL_JOYAXISMOTION,               /* Joystick axis motion */
	SDL_JOYBALLMOTION,               /* Joystick trackball motion */
	SDL_JOYHATMOTION,                /* Joystick hat position change */
	SDL_JOYBUTTONDOWN,               /* Joystick button pressed */
	SDL_JOYBUTTONUP,                 /* Joystick button released */
	SDL_QUIT,                        /* User-requested quit */
	SDL_SYSWMEVENT,                  /* System specific event */
	SDL_EVENT_RESERVEDA,             /* Reserved for future use.. */
	SDL_EVENT_RESERVEDB,             /* Reserved for future use.. */
	SDL_VIDEORESIZE,                 /* User resized video mode */
	SDL_VIDEOEXPOSE,                 /* Screen needs to be redrawn */
	SDL_EVENT_RESERVED2,             /* Reserved for future use.. */
	SDL_EVENT_RESERVED3,             /* Reserved for future use.. */
	SDL_EVENT_RESERVED4,             /* Reserved for future use.. */
	SDL_EVENT_RESERVED5,             /* Reserved for future use.. */
	SDL_EVENT_RESERVED6,             /* Reserved for future use.. */
	SDL_EVENT_RESERVED7,             /* Reserved for future use.. */
	/* Events SDL_USEREVENT through SDL_MAXEVENTS-1 are for your use */
	SDL_USEREVENT = 24,
	/* This last event is only for bounding internal arrays
	 It is the number of bits in the event mask datatype -- Uint32
	 */
	SDL_NUMEVENTS = 32
} SDL_EventType;

typedef struct SDL_MouseMotionEvent {
	int type;
	Uint8 state;        /**< The current button state */
	Uint8 padding1;        /**< The current button state */
	Uint8 padding2;        /**< The current button state */
	Uint8 padding3;        /**< The current button state */

	int x,y;
	int xrel, yrel;
} SDL_MouseMotionEvent;

typedef struct SDL_MouseButtonEvent {
	int type;
	Uint8 button;
	Uint8 state;
	
	int x,y;
} SDL_MouseButtonEvent;

typedef struct tagKeyEvent {
	int			type;
	SDL_keysym keysym;
} tagKeyEvent;

/**
 * \struct SDL_JoyAxisEvent
 *
 * \brief Joystick axis motion event structure (event.jaxis.*)
 */
typedef struct SDL_JoyAxisEvent
{
	Uint8 type;         /**< SDL_JOYAXISMOTION */
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
	Uint8 type;         /**< SDL_JOYBALLMOTION */
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
	Uint8 type;         /**< SDL_JOYHATMOTION */
	Uint8 which;        /**< The joystick device index */
	Uint8 hat;          /**< The joystick hat index */
	Uint8 value;        /**< The hat position value:
						 SDL_HAT_LEFTUP   SDL_HAT_UP       SDL_HAT_RIGHTUP
						 SDL_HAT_LEFT     SDL_HAT_CENTERED SDL_HAT_RIGHT
						 SDL_HAT_LEFTDOWN SDL_HAT_DOWN     SDL_HAT_RIGHTDOWN
						 Note that zero means the POV is centered.
						 */
} SDL_JoyHatEvent;

/*
 * Get the current state of a POV hat on a joystick
 * The return value is one of the following positions:
 */
#define SDL_HAT_CENTERED	0x00
#define SDL_HAT_UP			0x01
#define SDL_HAT_RIGHT		0x02
#define SDL_HAT_DOWN		0x04
#define SDL_HAT_LEFT		0x08
#define SDL_HAT_RIGHTUP		(SDL_HAT_RIGHT|SDL_HAT_UP)
#define SDL_HAT_RIGHTDOWN	(SDL_HAT_RIGHT|SDL_HAT_DOWN)
#define SDL_HAT_LEFTUP		(SDL_HAT_LEFT|SDL_HAT_UP)
#define SDL_HAT_LEFTDOWN	(SDL_HAT_LEFT|SDL_HAT_DOWN)

/**
 * \struct SDL_JoyButtonEvent
 *
 * \brief Joystick button event structure (event.jbutton.*)
 */
typedef struct SDL_JoyButtonEvent
{
	Uint8 type;         /**< SDL_JOYBUTTONDOWN or SDL_JOYBUTTONUP */
	Uint8 which;        /**< The joystick device index */
	Uint8 button;       /**< The joystick button index */
	Uint8 state;        /**< SDL_PRESSED or SDL_RELEASED */
} SDL_JoyButtonEvent;

typedef union SDL_Event {
	int type;
	SDL_MouseMotionEvent motion;
	SDL_MouseButtonEvent button;
	tagKeyEvent key;
	SDL_JoyAxisEvent jaxis;         /**< Joystick axis event data */
	SDL_JoyBallEvent jball;         /**< Joystick ball event data */
	SDL_JoyHatEvent jhat;           /**< Joystick hat event data */
	SDL_JoyButtonEvent jbutton;
} SDL_Event;

extern int inputMode;

extern int SDL_PollEvent(SDL_Event *e);
extern int SDL_PushEvent(SDL_Event *e);
extern void SDL_PushKeyEvent(SDLKey key);
extern void SDL_PumpEvents(void);

#define SDL_QUERY	-1
#define SDL_IGNORE	 0
#define SDL_DISABLE	 0
#define SDL_ENABLE	 1

#endif