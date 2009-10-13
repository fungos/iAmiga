/*
 *  SDL.c
 *  iAmiga
 *
 *  Created by Stuart Carnie on 5/19/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import "unistd.h"
#include "stdlib.h"
#include "SDL.h"
#include "AudioQueueManager.h"
#include "DisplayView.h"

const int kBytesPerPixel			= 2;
const int kBitsPerComponent			= 5;
const unsigned int kFormat			= kCGBitmapByteOrder16Little | kCGImageAlphaNoneSkipFirst;

static double				time_start;
BOOL						hasImageChanged;
uint						*imageBuffer;
CGContextRef				context;
#define kBufferWidth		320
#define kBufferHeight		240

Uint32 SDL_GetTicks() {
	double now = CFAbsoluteTimeGetCurrent();
	now = now - time_start;
	return (Uint32)(now * 1000UL);
}

void SDL_UnlockSurface(SDL_Surface* a) {
}

void SDL_LockSurface(SDL_Surface* a) {
}

void SDL_FreeSurface(SDL_Surface* a) {
}

void SDL_FillRect(SDL_Surface* a, void* b, int c) {
	// UpdateScreen();
}

void SDL_UpdateRect(SDL_Surface* s, int a, int b, int c, int d) {
	UpdateScreen();
}

void SDL_Delay(Uint32 duration) {
	usleep(duration * 1000);
}

long int SDL_MapRGB(tagFormat* a, int b, int c, int d) {
	return 0;
}

#include "touchstick.h"

extern "C" CJoyStick g_touchStick;
int SDL_PollEvent(SDL_Event* a) {
	TouchStickDPadState state = g_touchStick.dPadState();
	if (state == DPadCenter)
		return 0;
	
	static Uint32 timer = SDL_GetTicks();
	Uint32 now = SDL_GetTicks();
	if (now - timer < 20) {
		return 0;
	}
	timer = now;
	
	int x=0, y=0;
	
	switch (g_touchStick.dPadState()) {
		case DPadUp:
			y = -1;
			break;
		case DPadUpRight:
			y = -1, x = 1;
			break;
		case DPadRight:
			x = 1;
			break;
		case DPadDownRight:
			y = 1, x = 1;
			break;
		case DPadDown:
			y = 1;
			break;
		case DPadDownLeft:
			y = 1, x = -1;
			break;
		case DPadLeft:
			x = -1;
			break;
		case DPadUpLeft:
			y = -1, x = -1;
			break;
	}
	
	if (x!=0 || y != 0) {
		a->type = SDL_MOUSEMOTION;
		a->motion.yrel = y;
		a->motion.xrel = x;
		return 1;
	}
	return 0;
}

void SDL_JoystickUpdate() {
}

void SDL_VideoQuit() {
}

int SDL_JoystickGetAxis(SDL_Joystick* a, int b) {
	return 0;
}

int SDL_JoystickNumButtons(SDL_Joystick* a) {
	
	return 0;
}

int SDL_JoystickGetButton(SDL_Joystick* a, int b) {
	return 0;
}


int SDL_NumJoysticks() {
	return 0;
}

SDL_Joystick* SDL_JoystickOpen(int a) {
	static SDL_Joystick b;
	return &b;
}

int SDL_JoystickClose(SDL_Joystick* a) {
	return 0;
}

int SDL_Init(int a) {
	time_start = CFAbsoluteTimeGetCurrent();
	// create indexed color palette
	CGColorSpaceRef rgbColorSpace = CGColorSpaceCreateDeviceRGB();
	
	imageBuffer = (uint*)malloc(kBufferWidth * kBufferHeight * kBytesPerPixel + 16);
	context = CGBitmapContextCreate(imageBuffer, 
									kBufferWidth, kBufferHeight, kBitsPerComponent, 
									kBufferWidth * kBytesPerPixel, rgbColorSpace, kFormat);
	
	CFRelease(rgbColorSpace);
	
	hasImageChanged = NO;
	
	return 0;
}

SDL_Surface* SDL_SetVideoMode(int a, int b, int c, int d) {
	static SDL_Surface s;
	static tagFormat fmt;
	fmt.Rshift = 10;
	fmt.Gshift = 5;
	fmt.Bshift = 0;
	fmt.Rmask = 0x1f << 10;
	fmt.Gmask = 0x1f << 5;
	fmt.Bmask = 0x1F;
	fmt.BytesPerPixel = 2;
	s.format = &fmt;
	s.w = 320;
	s.h = 240;
	s.pitch = 640;
	s.pixels = imageBuffer;
	return &s;
}

char* SDL_GetError() {
	return 0;
}

int SDL_ShowCursor(int a) {
	return 0;
}

#pragma mark -
#pragma mark Audio Handlers

static CAudioQueueManager *g_audioQueue;
static SDL_AudioSpec g_spec;

int SDL_OpenAudio(SDL_AudioSpec* spec,void* data) {
	g_spec = *spec;
	g_audioQueue = new CAudioQueueManager(spec->freq, spec->samples, (SoundChannels)spec->channels);
	//g_audioQueue->setCallbackHandler((soundqueue_callback_t)g_spec.callback);
	g_audioQueue->start(false);
	return 0;
}

void SDL_CloseAudio() {
	g_audioQueue->stop();
}

void SDL_PauseAudio(int paused) {
	if (paused) {
		g_audioQueue->pause();
	} else {
		g_audioQueue->resume();
	}
}

