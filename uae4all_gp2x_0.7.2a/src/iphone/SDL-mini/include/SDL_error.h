//
//  SDL_error.h
//  iAmiga
//
//  Created by Stuart Carnie on 6/5/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#ifndef _SDL_error_h
#define _SDL_error_h

#include "SDL_stdinc.h"

extern void SDL_SetError(const char *fmt, ...);

/**
 *  \name Internal error functions
 *  
 *  \internal 
 *  Private error message function - used internally.
 */
/*@{*/
#define SDL_OutOfMemory()	SDL_Error(SDL_ENOMEM)
#define SDL_Unsupported()	SDL_Error(SDL_UNSUPPORTED)
typedef enum
{
    SDL_ENOMEM,
    SDL_EFREAD,
    SDL_EFWRITE,
    SDL_EFSEEK,
    SDL_UNSUPPORTED,
    SDL_LASTERROR
} SDL_errorcode;
extern void SDL_Error(SDL_errorcode code);
/*@}*//*Internal error functions*/

#endif