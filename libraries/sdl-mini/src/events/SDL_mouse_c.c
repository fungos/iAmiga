/*
 *  SDL_mouse.c
 *  iAmiga
 *
 *  Created by Stuart Carnie on 1/2/11.
 *  Copyright 2011 Manomio LLC. All rights reserved.
 *
 */

//
#include "SDL_events.h"
#include "../video/SDL_sysvideo.h"

typedef struct SDL_Mouse SDL_Mouse;

struct SDL_Mouse {
	int x;
    int y;
    int xdelta;
    int ydelta;
    int last_x, last_y;         /* the last reported x and y coordinates */
    Uint8 buttonstate;
    SDL_bool relative_mode;
};

static SDL_Mouse SDL_mouse;

/* Send a mouse motion event */
int SDL_SendMouseMotion(SDL_Window * window, int relative, int x, int y) {
	SDL_Mouse *mouse = &SDL_mouse;
    int posted;
    int xrel;
    int yrel;
	
    /* the relative motion is calculated regarding the system cursor last position */
    if (relative) {
        xrel = x;
        yrel = y;
        x = (mouse->last_x + x);
        y = (mouse->last_y + y);
    } else {
        xrel = x - mouse->last_x;
        yrel = y - mouse->last_y;
    }
	
    /* Drop events that don't change state */
    if (!xrel && !yrel) {
        return 0;
    }
	
    /* Update internal mouse coordinates */
    if (mouse->relative_mode == SDL_FALSE) {
        mouse->x = x;
        mouse->y = y;
    } else {
        mouse->x += xrel;
        mouse->y += yrel;
    }
	
	/*
	int x_max = 0, y_max = 0;

	SDL_GetWindowSize(mouse->focus, &x_max, &y_max);
	
    // make sure that the pointers find themselves inside the windows
    // only check if mouse->xmax is set !
    if (x_max && mouse->x > x_max) {
        mouse->x = x_max;
    } else if (mouse->x < 0) {
        mouse->x = 0;
    }
	
    if (y_max && mouse->y > y_max) {
        mouse->y = y_max;
    } else if (mouse->y < 0) {
        mouse->y = 0;
    }
	 */
	
    mouse->xdelta += xrel;
    mouse->ydelta += yrel;
	
    /* Post the event, if desired */
    posted = 0;
    //if (SDL_GetEventState(SDL_MOUSEMOTION) == SDL_ENABLE) {
        SDL_Event event;
        event.motion.type = SDL_MOUSEMOTION;
        // event.motion.windowID = mouse->focus ? mouse->focus->id : 0;
        event.motion.state = mouse->buttonstate;
        event.motion.x = mouse->x;
        event.motion.y = mouse->y;
        event.motion.xrel = xrel;
        event.motion.yrel = yrel;
        posted = (SDL_PushEvent(&event) > 0);
    //}
    mouse->last_x = mouse->x;
    mouse->last_y = mouse->y;
    return posted;
}

/* Send a mouse button event */
int SDL_SendMouseButton(SDL_Window * window, Uint8 state, Uint8 button) {
	SDL_Mouse *mouse = &SDL_mouse;
    int posted;
    Uint32 type;
	
    /* Figure out which event to perform */
    switch (state) {
		case SDL_PRESSED:
			if (mouse->buttonstate & SDL_BUTTON(button)) {
				/* Ignore this event, no state change */
				return 0;
			}
			type = SDL_MOUSEBUTTONDOWN;
			mouse->buttonstate |= SDL_BUTTON(button);
			break;
		case SDL_RELEASED:
			if (!(mouse->buttonstate & SDL_BUTTON(button))) {
				/* Ignore this event, no state change */
				return 0;
			}
			type = SDL_MOUSEBUTTONUP;
			mouse->buttonstate &= ~SDL_BUTTON(button);
			break;
		default:
			/* Invalid state -- bail */
			return 0;
    }
	
    /* Post the event, if desired */
    posted = 0;
    //if (SDL_GetEventState(type) == SDL_ENABLE) {
        SDL_Event event;
        event.type = type;
        event.button.state = state;
        event.button.button = button;
        event.button.x = mouse->x;
        event.button.y = mouse->y;
        // event.button.windowID = mouse->focus ? mouse->focus->id : 0;
        posted = (SDL_PushEvent(&event) > 0);
    //}
    return posted;
}
