/*
 *  SDL_video.h
 *  iAmiga
 *
 *  Created by Stuart Carnie on 1/3/11.
 *  Copyright 2011 Manomio LLC. All rights reserved.
 *
 */

#ifndef _SDL_video_h
#define _SDL_video_h

#include "SDL_stdinc.h"
#include "SDL_Surface.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
/* *INDENT-OFF* */
extern "C" {
    /* *INDENT-ON* */
#endif

typedef struct SDL_Window SDL_Window;

/**
 *  \brief Initialize the video subsystem, optionally specifying a video driver.
 *  
 *  \param driver_name Initialize a specific driver by name, or NULL for the 
 *                     default video driver.
 *  
 *  \param flags FIXME: Still needed?
 *  
 *  \return 0 on success, -1 on error
 *  
 *  This function initializes the video subsystem; setting up a connection
 *  to the window manager, etc, and determines the available display modes
 *  and pixel formats, but does not initialize a window or graphics mode.
 *  
 *  \sa SDL_VideoQuit()
 */
extern DECLSPEC int SDLCALL SDL_VideoInit(const char *driver_name,
                                          Uint32 flags);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
    /* *INDENT-OFF* */
}
/* *INDENT-ON* */
#endif

#endif

