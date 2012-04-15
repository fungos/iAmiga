//
//  SDL_sysjoystick.h
//  iAmiga
//
//  Created by Stuart Carnie on 6/5/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#include "SDL_config.h"

/* This is the system specific header for the SDL joystick API */

#include "SDL_joystick.h"

/* The SDL joystick structure */
struct _SDL_Joystick
{
    Uint8 index;                /* Device index */
    const char *name;           /* Joystick name - system dependent */
    
    int naxes;                  /* Number of axis controls on the joystick */
    Sint16 *axes;               /* Current axis states */
    
    int nhats;                  /* Number of hats on the joystick */
    Uint8 *hats;                /* Current hat states */
    
    int nballs;                 /* Number of trackballs on the joystick */
    struct balldelta
    {
        int dx;
        int dy;
    } *balls;                   /* Current ball motion deltas */
    
    int nbuttons;               /* Number of buttons on the joystick */
    Uint8 *buttons;             /* Current button states */
    
    struct joystick_hwdata *hwdata;     /* Driver dependent information */

    int ref_count;
};

/* Function to scan the system for joysticks.
 * Joystick 0 should be the system default joystick.
 * This function should return the number of available joysticks, or -1
 * on an unrecoverable fatal error.
 */
extern int SDL_SYS_JoystickInit(void);

/* Function to get the device-dependent name of a joystick */
extern const char *SDL_SYS_JoystickName(int index);

/* Function to open a joystick for use.
 The joystick to open is specified by the index field of the joystick.
 This should fill the nbuttons and naxes fields of the joystick structure.
 It returns 0, or -1 if there is an error.
 */
extern int SDL_SYS_JoystickOpen(SDL_Joystick * joystick);

/* Function to update the state of a joystick - called as a device poll.
 * This function shouldn't update the joystick structure directly,
 * but instead should call SDL_PrivateJoystick*() to deliver events
 * and update joystick device state.
 */
extern void SDL_SYS_JoystickUpdate(SDL_Joystick * joystick);

/* Function to close a joystick after use */
extern void SDL_SYS_JoystickClose(SDL_Joystick * joystick);

/* Function to perform any system-specific joystick related cleanup */
extern void SDL_SYS_JoystickQuit(void);