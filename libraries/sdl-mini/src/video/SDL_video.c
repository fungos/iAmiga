//
//  SDL_video.c
//  Flashback
//
//  Created by Stuart Carnie on 7/31/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#include "SDL.h"
#include "SDL_video.h"
#include "SDL_sysvideo.h"

#include "../events/SDL_events_c.h"

static SDL_VideoDevice *_this = NULL;

/* Available video drivers */
static VideoBootStrap *bootstrap[] = {
#if SDL_VIDEO_DRIVER_UIKIT
    &UIKIT_bootstrap,
#endif
    NULL
};

/*
 * Initialize the video and event subsystems -- determine native pixel format
 */
int
SDL_VideoInit(const char *driver_name, Uint32 flags)
{
    SDL_VideoDevice *video;
    int index;
    int i;
    
#if defined(MUST_THREAD_EVENTS)
    flags |= SDL_INIT_EVENTTHREAD;
#endif
    
    /* Start the event loop */
    if (SDL_StartEventLoop(flags) < 0) {
        return -1;
    }

    /* Select the proper video driver */
    index = 0;
    video = NULL;
    for (i = 0; bootstrap[i]; ++i) {
        if (bootstrap[i]->available()) {
            video = bootstrap[i]->create(index);
            if (video != NULL) {
                break;
            }
        }
    }
    
    _this = video;
    _this->name = bootstrap[i]->name;

    /* We're ready to go! */
    return 0;
}

SDL_VideoDevice *
SDL_GetVideoDevice(void)
{
    return _this;
}
