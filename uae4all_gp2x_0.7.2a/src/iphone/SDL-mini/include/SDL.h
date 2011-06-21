/*
 *  sdl.h
 *  iAmiga
 *
 *  Created by Stuart Carnie on 5/18/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _SDL_H
#define _SDL_H

#ifdef __cplusplus
extern "C" {
#endif
	
#include "SDL_stdinc.h"
#include "SDL_error.h"
#include "SDL_events.h"

typedef struct SDL_Color {
	unsigned r,g,b;
} SDL_Color;

typedef void (*sound_callback_t)(void *userdata, Uint8 *stream, int len);

typedef struct SDL_AudioSpec {
	int freq;
	int format;
	int channels;
	int samples;
	sound_callback_t callback;
	void *userdata;
} SDL_AudioSpec;

typedef struct tagFormat {
	unsigned long Rmask, Gmask, Bmask;
	unsigned short Rshift, Gshift, Bshift;
	unsigned BytesPerPixel;
} tagFormat;

typedef struct SDL_Surface {
	Uint32 flags;
	struct tagFormat *format;
	int w,h;
	int pitch;
	void *pixels;
	
	void *userdata;
} SDL_Surface; 

extern Uint32 SDL_GetTicks();
extern void SDL_UnlockSurface(SDL_Surface*);
extern void SDL_LockSurface(SDL_Surface*);
extern void SDL_FreeSurface(SDL_Surface*);
extern void SDL_FillRect(SDL_Surface*, void*, int);
extern void SDL_UpdateRect(SDL_Surface*, int, int, int, int);
extern void SDL_Delay(Uint32);
extern long int SDL_MapRGB(tagFormat*, int, int, int);
extern int SDL_PollEvent(SDL_Event*);
extern void SDL_VideoQuit();

extern int SDL_Init(int);
extern SDL_Surface* SDL_SetVideoMode(int, int, int, int);
extern SDL_Surface* SDL_GetVideoSurface();
extern void SDL_Flip(SDL_Surface*);
extern char* SDL_GetError();
extern int SDL_OpenAudio(SDL_AudioSpec*,void*);
extern void SDL_CloseAudio();
extern void SDL_PauseAudio(int);


#define SDL_ENABLE 1
#define SDL_DISABLE 0
#define SDL_INIT_VIDEO 0

// video init
#define SDL_HWSURFACE 0x00000001
#define SDL_DOUBLEBUF 0x40000000

#define AUDIO_S16 0
#define AUDIO_U8 0

extern int SDL_ShowCursor(int);
	
#import "SDL_events.h"
	
#ifdef __cplusplus
}
#endif

#endif