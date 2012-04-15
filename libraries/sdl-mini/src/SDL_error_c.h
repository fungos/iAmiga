//
//  SDL_error.h
//  iAmiga
//
//  Created by Stuart Carnie on 6/5/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#include "SDL_config.h"

#ifndef _SDL_error_c_h
#define _SDL_error_c_h

#define ERR_MAX_STRLEN	128
#define ERR_MAX_ARGS	5

typedef struct SDL_error
{
    /* This is a numeric value corresponding to the current error */
    int error;
    
    /* This is a key used to index into a language hashtable containing
     internationalized versions of the SDL error messages.  If the key
     is not in the hashtable, or no hashtable is available, the key is
     used directly as an error message format string.
     */
    char key[ERR_MAX_STRLEN];
    
    /* These are the arguments for the error functions */
    int argc;
    union
    {
        void *value_ptr;
#if 0                           /* What is a character anyway?  (UNICODE issues) */
        unsigned char value_c;
#endif
        int value_i;
        double value_f;
        char buf[ERR_MAX_STRLEN];
    } args[ERR_MAX_ARGS];
} SDL_error;

#endif /* _SDL_error_c_h */