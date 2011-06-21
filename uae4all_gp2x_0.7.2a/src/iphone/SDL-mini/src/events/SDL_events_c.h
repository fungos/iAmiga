//
//  SDL_events_c.h
//  iAmiga
//
//  Created by Stuart Carnie on 6/5/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#include "SDL_config.h"

#ifdef __cplusplus
extern "C" {
#endif
    
/* Useful functions and variables from SDL_events.c */
#include "SDL_events.h"
#include "SDL_mouse_c.h"

extern void SDL_Lock_EventThread(void);
extern void SDL_Unlock_EventThread(void);

#ifdef __cplusplus
}
#endif