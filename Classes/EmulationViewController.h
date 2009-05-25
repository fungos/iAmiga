/*
 Frodo, Commodore 64 emulator for the iPhone
 Copyright (C) 2007, 2008 Stuart Carnie
 See gpl.txt for license information.
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#import <UIKit/UIKit.h>

@class DisplayView;
@class InputControllerView;
@class JoystickViewLandscape;
class uae;

enum tagEmulatorState {
	EmulatorNotStarted,
	EmulatorPaused,
	EmulatorRunning
};

@interface EmulationViewController : UIViewController {
	// Views: both orientations
	DisplayView					*displayView;
	InputControllerView			*inputController;
	
	// Views: portrait

	
	// Views: landscape
	JoystickViewLandscape		*landscapeJoystickView;

	// Emulator
	uae							*emulator;
	NSThread					*emulationThread;
	tagEmulatorState			emulatorState;
	
	// Layout state information
	UIInterfaceOrientation		layoutOrientation;		// The orientation of the current layout
}

@property (nonatomic)			uae							*emulator;
@property (nonatomic)			tagEmulatorState			emulatorState;

@property (nonatomic, retain)	DisplayView					*displayView;
@property (nonatomic, retain)	InputControllerView			*inputController;

@property (nonatomic, retain)	JoystickViewLandscape		*landscapeJoystickView;


- (void)startEmulator;
- (void)runEmulator;
- (void)pauseEmulator;
- (void)resumeEmulator;

@end

extern EmulationViewController *g_emulatorViewController;
