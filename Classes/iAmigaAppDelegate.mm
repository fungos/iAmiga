//
//  iAmigaAppDelegate.m
//  iAmiga
//
//  Created by Stuart Carnie on 2/7/09.
//  Copyright __MyCompanyName__ 2009. All rights reserved.
//

#import "iAmigaAppDelegate.h"
#import "DisplayView.h"
#import "uae.h"

@interface iAmigaAppDelegate()

- (void)startEmulator;
- (void)runEmulator;

@end

@implementation iAmigaAppDelegate

@synthesize window;


- (void)applicationDidFinishLaunching:(UIApplication *)application {    

	_displayView = [[DisplayView alloc] initWithFrame:CGRectMake(0, 0, 320, 240)];
	[window addSubview:_displayView];
	[self startEmulator];
	
	
    // Override point for customization after application launch
    [window makeKeyAndVisible];
}
	
- (void)startEmulator {
	emulationThread = [[NSThread alloc] initWithTarget:self selector:@selector(runEmulator) object:nil];
	[emulationThread start];
	[_displayView startTimer];
}

- (void)runEmulator {
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	[NSThread setThreadPriority:0.7];
	emulator.real_main();
	[pool release];
}


- (void)dealloc {
    [window release];
    [super dealloc];
}


@end
