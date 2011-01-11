/*
 *  SDL_mouse.h
 *  iAmiga
 *
 *  Created by Stuart Carnie on 1/2/11.
 *  Copyright 2011 Manomio LLC. All rights reserved.
 *
 */

#ifndef _SDL_mouse_c_h
#define _SDL_mouse_c_h

#define SDL_MOTIONABSOLUTE	0
#define SDL_MOTIONRELATIVE	1

/* Send a mouse motion event */
extern int SDL_SendMouseMotion(SDL_Window * window, int relative, int x, int y);

/* Send a mouse button event */
extern int SDL_SendMouseButton(SDL_Window * window, Uint8 state, Uint8 button);

#endif