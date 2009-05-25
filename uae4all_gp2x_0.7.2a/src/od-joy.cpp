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
	/*
    num = SDL_JoystickNumButtons (joy);
    if (num > 16)
		num = 16;
    for (i = 0; i < num; i++)
		*button |= (SDL_JoystickGetButton (joy, i) & 1) << i;
	 */
    //if (left) top = !top;
    //if (right) bot = !bot;
    //*dir = bot | (right << 1) | (top << 8) | (left << 9);
	
	if (vkbd_mode && nr)
	{
		// move around the virtual keyboard instead
		if (left)
			vkbd_move |= VKBD_LEFT;
		else
		{
			vkbd_move &= ~VKBD_LEFT;
			if (right)
				vkbd_move |= VKBD_RIGHT;
			else
				vkbd_move &= ~VKBD_RIGHT;
		}
		if (top)
			vkbd_move |= VKBD_UP;
		else
		{
			vkbd_move &= ~VKBD_UP;
			if (bot)
				vkbd_move |= VKBD_DOWN;
			else
				vkbd_move &= ~VKBD_DOWN;
		}
		if (*button)
		{
			vkbd_move=VKBD_BUTTON;
			*button=0;
		}
		// TODO: add vkbd_button2 mapped to button2
	}
	else
	{
		// normal joystick movement
	    if (left) top = !top;
		if (right) bot = !bot;
		*dir = bot | (right << 1) | (top << 8) | (left << 9);
	}
#endif
}

void init_joystick(void) {
    nr_joysticks = 1;
}

void close_joystick(void) {
}
