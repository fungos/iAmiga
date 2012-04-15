//
//  SDL_Surface.h
//  Flashback
//
//  Created by Stuart Carnie on 7/24/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#ifndef _SDL_surface_h
#define _SDL_surface_h

#include "SDL_stdinc.h"
#include "SDL_Pixels.h"

typedef struct SDL_Surface {
	Uint32 flags;
	struct tagFormat *format;
	int w,h;
	int pitch;
	void *pixels;
	
	void *userdata;
} SDL_Surface; 


#endif
