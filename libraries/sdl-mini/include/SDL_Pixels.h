//
//  SDL_Pixels.h
//  Flashback
//
//  Created by Stuart Carnie on 7/24/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#ifndef _SDL_Pixels_h
#define _SDL_Pixels_h

#include "begin_code.h"
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
/* *INDENT-OFF* */
extern "C" {
    /* *INDENT-ON* */
#endif


typedef struct SDL_Color {
	unsigned r,g,b;
} SDL_Color;

typedef struct tagFormat {
    unsigned long Rmask, Gmask, Bmask;
    unsigned short Rshift, Gshift, Bshift;
    unsigned BytesPerPixel;
} tagFormat;


    /* Ends C function definitions when using C++ */
#ifdef __cplusplus
    /* *INDENT-OFF* */
}
/* *INDENT-ON* */
#endif
#include "close_code.h"

#endif