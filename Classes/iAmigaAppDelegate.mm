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
#import "UaeDebugger.h"

@interface iAmigaAppDelegate()

- (void)screenDidConnect:(NSNotification*)aNotification;
- (void)screenDidDisconnect:(NSNotification*)aNotification;
- (void)configureScreens;

@end

@implementation iAmigaAppDelegate

@synthesize window, mainController=_mainController;

static UaeDebugger *debugger;

- (void)applicationDidFinishLaunching:(UIApplication *)application {
	//_emulationView = [EmulationViewController new];
	[window addSubview:self.mainController.view];	
	
    // Override point for customization after application launch
    [window makeKeyAndVisible];
	
	OSStatus res = AudioSessionInitialize(NULL, NULL, NULL, NULL);
	UInt32 sessionCategory = kAudioSessionCategory_AmbientSound;
	res = AudioSessionSetProperty(kAudioSessionProperty_AudioCategory, sizeof(sessionCategory), &sessionCategory);
	res = AudioSessionSetActive(true);
	
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(screenDidConnect:) name:UIScreenDidConnectNotification object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(screenDidDisconnect:) name:UIScreenDidDisconnectNotification object:nil];
	[self configureScreens];
	
	//debugger = [[UaeDebugger alloc] init];
	//[debugger startOnPort:2000];
}

- (void)screenDidConnect:(NSNotification*)aNotification {
	[self configureScreens];
}

- (void)screenDidDisconnect:(NSNotification*)aNotification {
	[self configureScreens];
	
}

- (void)configureScreens {
	if ([[UIScreen screens] count] == 1) {
		NSLog(@"Device display");
		// disable extras		
		if (externalWindow) {
			externalWindow.hidden = YES;
		}
		[_emulationView setDisplayViewWindow:nil isExternal:NO];
	} else {
		NSLog(@"External display");
		UIScreen *secondary = [[UIScreen screens] objectAtIndex:1];
		UIScreenMode *bestMode = [secondary.availableModes objectAtIndex:0];
		int modes = [secondary.availableModes count];
		if (modes > 1) {
			UIScreenMode *current;
			for (current in secondary.availableModes) {
				if (current.size.width > bestMode.size.width)
					bestMode = current;
			}
		}
		secondary.currentMode = bestMode;
		if (!externalWindow) {
			externalWindow = [[UIWindow alloc] initWithFrame:secondary.bounds];
		} else {
			externalWindow.frame = secondary.bounds;
		}

		externalWindow.screen = secondary;
		[_emulationView setDisplayViewWindow:externalWindow isExternal:YES];
		externalWindow.hidden = NO;
	}
}

- (void)dealloc {
    [window release];
    [super dealloc];
}


@end
