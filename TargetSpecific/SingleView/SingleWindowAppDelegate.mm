//
//  SingleWindowAppDelegate.m
//  iAmiga
//
//  Created by Stuart Carnie on 6/21/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import "SingleWindowAppDelegate.h"
#import "BaseEmulationViewController.h"
#import <AudioToolbox/AudioServices.h>
#import "SDL.h"
#import "UIKitDisplayView.h"

#import "sysconfig.h"
#import "sysdeps.h"
#import "options.h"

@interface SingleWindowAppDelegate()

- (void)screenDidConnect:(NSNotification*)aNotification;
- (void)screenDidDisconnect:(NSNotification*)aNotification;
- (void)configureScreens;

@end

@implementation SingleWindowAppDelegate

@synthesize window, mainController;

- (void)applicationDidFinishLaunching:(UIApplication *)application {
    // load disks into df0: and df1:
    NSString *path = [[NSBundle mainBundle] pathForResource:@"Defender OTC1" ofType:@"ADF"];
    [path getCString:prefs_df[0] maxLength:256 encoding:[NSString defaultCStringEncoding]];
    path = [[NSBundle mainBundle] pathForResource:@"Defender OTC2" ofType:@"ADF"];
    [path getCString:prefs_df[1] maxLength:256 encoding:[NSString defaultCStringEncoding]];

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
		[self.mainController setDisplayViewWindow:nil isExternal:NO];
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
			externalWindow.backgroundColor = [UIColor blackColor];
		} else {
			externalWindow.frame = secondary.bounds;
		}
        
		externalWindow.screen = secondary;
		[self.mainController setDisplayViewWindow:externalWindow isExternal:YES];
		externalWindow.hidden = NO;
	}
}

- (void)dealloc {
    [window release];
    [super dealloc];
}


@end
