/* 
 * UAE - The Un*x Amiga Emulator
 * 
 * Joystick emulation for Linux and BSD. They share too much code to
 * split this file.
 * 
 * Copyright 1997 Bernd Schmidt
 * Copyright 1998 Krister Walfridsson
 */

#include "sysconfig.h"
#include "sysdeps.h"

#include "uae.h"
#include "joystick.h"
#include "touchstick.h"

#include "vkbd.h"

int nr_joysticks;

SDL_Joystick *uae4all_joy0, *uae4all_joy1;

CJoyStick g_touchStick;

void read_joystick(int nr, unsigned int *dir, int *button)
{
#ifndef MAX_AUTOEVENTS
    int left = 0, right = 0, top = 0, bot = 0;
    int i, num;
	SDL_Joystick *joy = nr == 0 ? uae4all_joy0 : uae4all_joy0;
    
    *dir = 0;
    *button = 0;
    
    nr = (~nr)&0x1;
	
    switch (g_touchStick.dPadState()) {
		case DPadUp:
			top = 1;
			break;
		case DPadUpRight:
			top = 1; right = 1;
			break;
		case DPadRight:
			right = 1;
			break;
		case DPadDownRight:
			bot = 1; right = 1;
			break;
		case DPadDown:
			bot = 1;
			break;
		case DPadDownLeft:
			bot = 1; left = 1;
			break;
		case DPadLeft:
			left = 1;
			break;
		case DPadUpLeft:
			top = 1; left = 1;
			break;
	}
	
	*button = g_touchStick.buttonOneState();
    
    // now read current "SDL" joystick
    num = SDL_JoystickNumButtons (joy);
    
    // NOTE: should really only map one button, but this code maps any button press as a fire
    for (i = 0; i < num; i++)
		//*button |= (SDL_JoystickGetButton (joy, i) & 1) << i;
        *button |= (SDL_JoystickGetButton (joy, i) & 1);
    
    int hat = SDL_JoystickGetHat(joy, 0);
    if (hat & SDL_HAT_LEFT)
        left = 1;
    else if (hat & SDL_HAT_RIGHT)
        right = 1;
    if (hat & SDL_HAT_UP) 
        top = 1;
    else if (hat & SDL_HAT_DOWN)
        bot = 1;
    
    // normal joystick movement
    if (left) top = !top;
    if (right) bot = !bot;
    *dir = bot | (right << 1) | (top << 8) | (left << 9);
#endif
}

void init_joystick(void) {
    nr_joysticks = 1;
    uae4all_joy0 = SDL_JoystickOpen(3);  // iCADE by default
}

void close_joystick(void) {
    SDL_JoystickClose(uae4all_joy0);
}

void switch_joystick(int joynum) {
    SDL_Joystick *newJoystick = SDL_JoystickOpen(joynum);
    SDL_Joystick *oldJoystick = uae4all_joy0;
    uae4all_joy0 = newJoystick;
    SDL_JoystickClose(oldJoystick);
}
