//
//  iAmigaAppDelegate.m
//  iAmiga
//
//  Created by Stuart Carnie on 2/7/09.
//  Copyright __MyCompanyName__ 2009. All rights reserved.
//

#import "iAmigaAppDelegate.h"
#import "EmulationViewController.h"
#import <AudioToolbox/AudioServices.h>

@implementation iAmigaAppDelegate

@synthesize window, mainController=_mainController;

- (void)applicationDidFinishLaunching:(UIApplication *)application {    

	//_emulationView = [EmulationViewController new];
	[window addSubview:self.mainController.view];	
	
    // Override point for customization after application launch
    [window makeKeyAndVisible];
	
	OSStatus res = AudioSessionInitialize(NULL, NULL, NULL, NULL);
	UInt32 sessionCategory = kAudioSessionCategory_AmbientSound;
	res = AudioSessionSetProperty(kAudioSessionProperty_AudioCategory, sizeof(sessionCategory), &sessionCategory);
	res = AudioSessionSetActive(true);
}

- (void)dealloc {
    [window release];
    [super dealloc];
}


@end
