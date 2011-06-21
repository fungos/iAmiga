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

@class InputControllerView;
@class JoystickViewLandscape;
@class VirtualKeyboard;
@class TouchHandlerView;
@protocol DisplayViewSurface;

class uae;

enum tagEmulatorState {
	EmulatorNotStarted,
	EmulatorPaused,
	EmulatorRunning
};

typedef enum {
	/*! Sizes the display to the exact pixel size */
	MMScreenModeActualPixel, 

	/*! Sizes the display to fill the screen area, 
	 *  honoring the correct aspect ratio */
	MMScreenModeFillAspectFit,

	/*! Sizes the display to the nearest full-pixel
	 *  multiple.  e.g. 320x200, 640x400, 1280x800, etc */
	MMScreenModeFullPixel,
	
	/*! Fills the entire screen area, regardless of aspect ratio */
	MMScreenModeFill,
} DisplayScreenMode;

@interface EmulationViewController : UIViewController {
	// Views: both orientations
	UIView						*rootView;
	UIView<DisplayViewSurface>	*displayView;
	InputControllerView			*inputController;
	VirtualKeyboard				*vKeyboard;
	TouchHandlerView			*touchHandler;
	
	UIImage						*modes[3];
	UIButton					*inputModeView;
	
	// Views: portrait

	
	// Views: landscape
	JoystickViewLandscape		*landscapeJoystickView;

	// Emulator
	uae							*emulator;
	NSThread					*emulationThread;
	tagEmulatorState			emulatorState;
	
	// Layout state information
	UIInterfaceOrientation		layoutOrientation;		// The orientation of the current layout
	
	BOOL						_isExternal;
	UIWindow					*displayViewWindow;
	BOOL						_integralSize;
}

@property (nonatomic)			uae							*emulator;
@property (nonatomic)			tagEmulatorState			emulatorState;

@property (nonatomic, retain)	UIView<DisplayViewSurface>	*displayView;
@property (nonatomic, retain)	InputControllerView			*inputController;
@property (nonatomic, retain)	TouchHandlerView			*touchHandler;

@property (nonatomic, retain)	JoystickViewLandscape		*landscapeJoystickView;

@property (nonatomic)			BOOL						integralSize;


- (void)startEmulator;
- (void)runEmulator;
- (void)pauseEmulator;
- (void)resumeEmulator;
- (void)setDisplayViewWindow:(UIWindow*)window isExternal:(BOOL)isExternal;

@end

extern EmulationViewController *g_emulatorViewController;
