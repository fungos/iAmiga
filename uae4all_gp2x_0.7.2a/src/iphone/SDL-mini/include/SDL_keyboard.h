/*
 *  SDL_keyboard.h
 *  iAmiga
 *
 *  Created by Stuart Carnie on 1/2/11.
 *  Copyright 2011 Manomio LLC. All rights reserved.
 *
 */

#ifndef _SDL_keyboard_h
#define _SDL_keyboard_h

#include "SDL_keysym.h"

typedef struct SDL_keysym {
	SDLKey sym;
	int unicode;
	SDLMod mod;
} SDL_keysym;

#endif