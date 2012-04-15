//
//  SDL_UIKitEvents.m
//  Flashback
//
//  Created by Stuart Carnie on 7/31/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#include "SDL_config.h"

//#include "../../events/SDL_sysevents.h"
#include "../../events/SDL_events_c.h"

#include "SDL_UIKitVideo.h"
#include "SDL_UIKitEvents.h"

#import <Foundation/Foundation.h>

void
UIKit_PumpEvents(_THIS)
{
	/* 
     When the user presses the 'home' button on the iPod
     the application exits -- immediatly.
	 
     Unlike in Mac OS X, it appears there is no way to cancel the termination.
	 
     This doesn't give the SDL user's application time to respond to an SDL_Quit event.
     So what we do is that in the UIApplicationDelegate class (SDLUIApplicationDelegate),
     when the delegate receives the ApplicationWillTerminate message, we execute
     a longjmp statement to get back here, preventing an immediate exit.
	 */	
//	if (setjmp(*jump_env()) == 0) {
		/* if we're setting the jump, rather than jumping back */
		SInt32 result;
		do {
			result = CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0, TRUE);
		} while(result == kCFRunLoopRunHandledSource);
//	}
}
