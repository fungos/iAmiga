/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997-2010 Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Sam Lantinga
    slouken@libsdl.org
*/

#ifndef _SDL_thread_h
#define _SDL_thread_h

/**
 *  \file SDL_thread.h
 *  
 *  Header for the SDL thread management routines.
 */

#include "SDL_stdinc.h"
#include "SDL_error.h"

/* Thread synchronization primitives */
#include "SDL_mutex.h"

#include "begin_code.h"
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
/* *INDENT-OFF* */
extern "C" {
/* *INDENT-ON* */
#endif

/* The SDL thread structure, defined in SDL_thread.c */
struct SDL_Thread;
typedef struct SDL_Thread SDL_Thread;

/* The SDL thread ID */
typedef unsigned long SDL_threadID;

/* The function passed to SDL_CreateThread()
   It is passed a void* user context parameter and returns an int.
 */
typedef int (SDLCALL * SDL_ThreadFunction) (void *data);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
/* *INDENT-OFF* */
}
/* *INDENT-ON* */
#endif
#include "close_code.h"

#endif /* _SDL_thread_h */

/* vi: set ts=4 sw=4 expandtab: */
