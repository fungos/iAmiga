//
//  SDL_error.c
//  iAmiga
//
//  Created by Stuart Carnie on 6/5/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#include "SDL_config.h"

#include "SDL_error.h"
#include "SDL_error_c.h"

void SDL_SetError(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    va_end(ap);
}

/* Very common errors go here */
void
SDL_Error(SDL_errorcode code)
{
    switch (code) {
        case SDL_ENOMEM:
            SDL_SetError("Out of memory");
            break;
        case SDL_EFREAD:
            SDL_SetError("Error reading from datastream");
            break;
        case SDL_EFWRITE:
            SDL_SetError("Error writing to datastream");
            break;
        case SDL_EFSEEK:
            SDL_SetError("Error seeking in datastream");
            break;
        case SDL_UNSUPPORTED:
            SDL_SetError("That operation is not supported");
            break;
        default:
            SDL_SetError("Unknown SDL error");
            break;
    }
}