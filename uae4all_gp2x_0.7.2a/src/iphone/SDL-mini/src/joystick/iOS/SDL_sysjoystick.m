//
//  SDL_sysjoystick.m
//  iAmiga
//
//  Created by Stuart Carnie on 6/5/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#include "SDL_events.h"
#include "SDL_joystick.h"
#include "SDL_sysjoystick.h"
#include "SDL_joystick_c.h"
#import "SDLUIAccelerationDelegate.h"
#import "iControlPadReaderView.h"
#import "iCadeReaderView.h"
#import "ButtonStates.h"
#import "SDL_NSObject+Blocks.h"

extern UIView *GetSharedOGLDisplayView();

#define kTouchStick     0
#define kAccelerometer  1
#define kiControlPad    2
#define kiCade          3

const char *accelerometerName = "iPhone accelerometer";
const char *iControlPadName = "iControlPad";
const char *iCadeName = "iCADE";

typedef struct joystick_hwdata {
    UIView *view;
} joystick_hwdata;

inline
static int icp_getState(int button);

int SDL_SYS_JoystickInit(void) {
    return 4;
}

/* Function to get the device-dependent name of a joystick */
const char *SDL_SYS_JoystickName(int index) {
    switch (index) {
        case kTouchStick:
            return "iPhone touch";
        
        case kAccelerometer:
            return accelerometerName;
            
        case kiControlPad:
            return iControlPadName;
            
        case kiCade:
            return iCadeName;
            
        default:
			SDL_SetError("No joystick available with that index");
			return NULL;
    }
}

/* Function to open a joystick for use.
 The joystick to open is specified by the index field of the joystick.
 This should fill the nbuttons and naxes fields of the joystick structure.
 It returns 0, or -1 if there is an error.
 */
int
SDL_SYS_JoystickOpen(SDL_Joystick * joystick)
{    
    if (joystick->index == kiControlPad) {
        joystick->naxes = 0;
        joystick->nhats = 1;
        joystick->nballs = 0;
        joystick->nbuttons = 8;
        joystick->name = iControlPadName;
        joystick->hwdata = (joystick_hwdata *)SDL_malloc(sizeof(joystick_hwdata));
        UIView *view = [[iControlPadReaderView alloc] initWithFrame:CGRectMake(0, 0, 1, 1)];
        UIView *display = GetSharedOGLDisplayView();
        [display performBlock:^(void) {
            // main thread
            [display addSubview:view];
            [view becomeFirstResponder];

        } afterDelay:0.0f];
        joystick->hwdata->view = view;
    } else if (joystick->index == kiCade) {
        joystick->naxes = 0;
        joystick->nhats = 1;
        joystick->nballs = 0;
        joystick->nbuttons = 8;
        joystick->name = iCadeName;
        joystick->hwdata = (joystick_hwdata *)SDL_malloc(sizeof(joystick_hwdata));
        UIView *view = [[iCadeReaderView alloc] initWithFrame:CGRectMake(0, 0, 1, 1)];
        UIView *display = GetSharedOGLDisplayView();
        [display performBlock:^(void) {
            // main thread
            [display addSubview:view];
            [view becomeFirstResponder];
        } afterDelay:0.0f];
        joystick->hwdata->view = view;
    } else if (joystick->index == kAccelerometer) {
		joystick->naxes = 3;
		joystick->nhats = 0;
		joystick->nballs = 0;
		joystick->nbuttons = 0;
		joystick->name  = accelerometerName;
		[[SDLUIAccelerationDelegate sharedDelegate] startup];
	}
	else {
		SDL_SetError("No joystick available with that index");
		return (-1);
	}
	
    return 0;
}

/* Function to update the state of a joystick - called as a device poll.
 * This function shouldn't update the joystick structure directly,
 * but instead should call SDL_PrivateJoystick*() to deliver events
 * and update joystick device state.
 */
void
SDL_SYS_JoystickUpdate(SDL_Joystick * joystick)
{
	if (joystick->index == kAccelerometer) {
        Sint16 orientation[3];
        
        if ([[SDLUIAccelerationDelegate sharedDelegate] hasNewData]) {
            
            [[SDLUIAccelerationDelegate sharedDelegate] getLastOrientation: orientation];
            [[SDLUIAccelerationDelegate sharedDelegate] setHasNewData: NO];
            
            SDL_PrivateJoystickAxis(joystick, 0, orientation[0]);
            SDL_PrivateJoystickAxis(joystick, 1, orientation[1]);
            SDL_PrivateJoystickAxis(joystick, 2, orientation[2]);
            
        }
    } else if (joystick->index == kiControlPad) {
        
        // buttons
        for(int i = ICP_BUTTON_BEGIN; i <= ICP_BUTTON_END; i++) {
            SDL_PrivateJoystickButton(joystick, i-ICP_BUTTON_BEGIN, icp_getState(i));
        }
        
        // hat
        int hat_value = SDL_HAT_CENTERED;
        hat_value |= icp_getState(ICP_BUTTON_UP) ? SDL_HAT_UP : 0;
        hat_value |= icp_getState(ICP_BUTTON_RIGHT) ? SDL_HAT_RIGHT : 0;
        hat_value |= icp_getState(ICP_BUTTON_LEFT) ? SDL_HAT_LEFT : 0;
        hat_value |= icp_getState(ICP_BUTTON_DOWN) ? SDL_HAT_DOWN : 0;
        SDL_PrivateJoystickHat(joystick, 0, hat_value);
    } else if (joystick->index == kiCade) {
        
        // buttons
        iCadeReaderView *view = (iCadeReaderView *)joystick->hwdata->view;
        iCadeState state = view.iCadeState;
        
        for(int i=iCadeButtonFirst, btn=0; i <= iCadeButtonLast; i <<= 1, btn++) {
            SDL_PrivateJoystickButton(joystick, btn, (i & state) != 0);
        }
        
        SDL_PrivateJoystickHat(joystick, 0, state & 0x0f);
    }
}

/* Function to close a joystick after use */
void
SDL_SYS_JoystickClose(SDL_Joystick * joystick)
{
	if (joystick->index == kAccelerometer && [[SDLUIAccelerationDelegate sharedDelegate] isRunning]) {
		[[SDLUIAccelerationDelegate sharedDelegate] shutdown];
	} else if (joystick->index == kiControlPad) {
        [joystick->hwdata->view removeFromSuperview];
        [joystick->hwdata->view release];
        SDL_free(joystick->hwdata);
    } else if (joystick->index == kiCade) {
        [joystick->hwdata->view removeFromSuperview];
        [joystick->hwdata->view release];
        SDL_free(joystick->hwdata);
    } else {
        SDL_SetError("No joystick open with that index");
    }
    
    return;
}

/* Function to perform any system-specific joystick related cleanup */
void
SDL_SYS_JoystickQuit(void) {
    return;
}

// iControlPad
static int LEFT_BYTE[] = {ICP_BUTTON_UP, ICP_BUTTON_RIGHT, ICP_BUTTON_LEFT, ICP_BUTTON_DOWN, ICP_BUTTON_L, ICP_BUTTON_SELECT};
static int RIGHT_BYTE[] = {ICP_BUTTON_START, ICP_BUTTON_Y, ICP_BUTTON_A, ICP_BUTTON_X, ICP_BUTTON_B, ICP_BUTTON_R};

static char buttons[ICP_MAX_BUTTON];
static char buffer[256];
static int pos = 0;

inline
static int icp_getState(int button) {
    return buttons[button];
}

inline
static void setState(int button, int value) {
    buttons[button] = value;
}

void icp_handle(char c) {
    char left;
    char right;
    
    buffer[pos++] = c;
    
    while(pos > 2 && buffer[0] != 'm')
    {
        for(int i=1; i<pos; i++) buffer[i-1] = buffer[i];
        
        pos--;
    }
    
    if(pos > 2 && buffer[0] == 'm')
    {
        left = buffer[1] - 32;
        right = buffer[2] - 32;
        
        for(int i=0; i<6; i++)
        {
            setState(LEFT_BYTE[i], (left & 0x01));
            left >>= 1;
        }
        
        for(int i=0; i<6; i++)
        {
            setState(RIGHT_BYTE[i], (right & 0x01));
            right >>= 1;
        }
        
        for(int i=3; i<pos; i++) buffer[i-3] = buffer[i];
        
        pos -= 3;
    }
    
    if(pos > 10) NSLog(@"Possible error - %i characters queued!", pos);
    if(pos >= 256) pos = 0;
}
