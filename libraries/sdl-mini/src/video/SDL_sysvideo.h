/*
 *  SDL_sysvideo.h
 *  iAmiga
 *
 *  Created by Stuart Carnie on 1/2/11.
 *  Copyright 2011 Manomio LLC. All rights reserved.
 *
 */

#include "SDL_config.h"

#ifndef _SDL_sysvideo_h
#define _SDL_sysvideo_h

#include "SDL_mouse.h"
#include "SDL_keysym.h"

/* The SDL video driver */

typedef struct SDL_VideoDevice SDL_VideoDevice;

struct SDL_Window {
	const void *magic;
};

/* Define the SDL video driver structure */
#define _THIS	SDL_VideoDevice *_this

struct SDL_VideoDevice
{
    /* * * */
    /* The name of this video driver */
    const char *name;
    
    /* * * */
    /*
     * Event manager functions
     */
    void (*PumpEvents) (_THIS);

    /* * * */
    /* The function used to dispose of this structure */
    void (*free) (_THIS);
};

typedef struct VideoBootStrap
{
    const char *name;
    const char *desc;
    int (*available) (void);
    SDL_VideoDevice *(*create) (int devindex);
} VideoBootStrap;


#if SDL_VIDEO_DRIVER_UIKIT
extern VideoBootStrap UIKIT_bootstrap;
#endif


extern SDL_VideoDevice *SDL_GetVideoDevice(void);

#endif