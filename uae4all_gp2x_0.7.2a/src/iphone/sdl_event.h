//
//  sdl_event.h
//  A2600
//
//  Created by Stuart Carnie on 10/10/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

extern int inputMode;

extern int SDL_PollEvent(SDL_Event *e);
extern void SDL_PushEvent(SDL_Event *e);
extern void SDL_PushKeyEvent(SDLKey key);