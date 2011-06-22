//
//  BaseEmulationViewController.h
//  iAmiga
//
//  Created by Stuart Carnie on 6/22/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol DisplayViewSurface;

enum tagEmulatorState {
	EmulatorNotStarted,
	EmulatorPaused,
	EmulatorRunning
} ;

@interface BaseEmulationViewController : UIViewController {
    // Views: both orientations
	UIView<DisplayViewSurface>	*displayView;
		
	// Emulator
	NSThread					*emulationThread;
	enum tagEmulatorState		emulatorState;
		
	BOOL						_isExternal;
	UIWindow					*displayViewWindow;
	BOOL						_integralSize;
}

@property (nonatomic)			BOOL						integralSize;

- (void)startEmulator;
- (void)runEmulator;
- (void)pauseEmulator;
- (void)resumeEmulator;
- (void)setDisplayViewWindow:(UIWindow*)window isExternal:(BOOL)isExternal;

@end
