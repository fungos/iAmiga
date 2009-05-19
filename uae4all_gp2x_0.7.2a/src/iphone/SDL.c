/*
 *  SDL.c
 *  iAmiga
 *
 *  Created by Stuart Carnie on 5/19/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "stdlib.h"
#include "SDL.h"
Uint32 SDL_GetTicks() {
	return 0;
}

void SDL_UnlockSurface(SDL_Surface* a) {
}

void SDL_LockSurface(SDL_Surface* a) {
}

void SDL_FreeSurface(SDL_Surface* a) {
}

void SDL_FillRect(SDL_Surface* a, void* b, int c) {
}

void SDL_UpdateRect(SDL_Surface* s, int a, int b, int c, int d) {
}

void SDL_Delay(Uint32 a) {
}

long int SDL_MapRGB(tagFormat* a, int b, int c, int d) {
	return 0;
}

int SDL_PollEvent(SDL_Event* a) {
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
	return 0;
}

SDL_Surface* SDL_SetVideoMode(int a, int b, int c, int d) {
	static SDL_Surface s;
	static tagFormat fmt;
	fmt.Rshift = 0;
	fmt.Gshift = 5;
	fmt.Bshift = 10;
	fmt.Rmask = 0x1f;
	fmt.Gmask = 0x1f << 5;
	fmt.Bmask = 0x1F << 10;
	fmt.BytesPerPixel = 2;
	s.format = &fmt;
	s.w = 320;
	s.h = 240;
	s.pitch = 640;
	static unsigned short pixels[320 * 240 * 2];
	s.pixels = pixels; //malloc(320 * 240 * 2);
	return &s;
}

char* SDL_GetError() {
	return 0;
}

int SDL_ShowCursor(int a) {
	return 0;
}
