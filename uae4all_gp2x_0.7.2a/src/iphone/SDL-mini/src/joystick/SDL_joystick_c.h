//
//  SDL_joystick_c.h
//  iAmiga
//
//  Created by Stuart Carnie on 6/5/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#ifdef __cplusplus
extern "C" {
#endif

#include "SDL_config.h"
#include "SDL_joystick.h"

extern Uint8 SDL_numjoysticks;

/* Initialization and shutdown functions */
extern int SDL_JoystickInit(void);
extern void SDL_JoystickQuit(void);
    
/* Internal event queueing functions */
extern int SDL_PrivateJoystickAxis(SDL_Joystick * joystick,
                                   Uint8 axis, Sint16 value);
extern int SDL_PrivateJoystickBall(SDL_Joystick * joystick,
                                   Uint8 ball, Sint16 xrel, Sint16 yrel);
extern int SDL_PrivateJoystickHat(SDL_Joystick * joystick,
                                  Uint8 hat, Uint8 value);
extern int SDL_PrivateJoystickButton(SDL_Joystick * joystick,
                                     Uint8 button, Uint8 state);

#ifdef __cplusplus
}
#endif