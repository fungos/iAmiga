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

#import "EmulationViewController.h"
#import "debug.h"
#import "DisplayView.h"
#import "InputControllerView.h"
#import "uae.h"
#import "JoystickViewLandscape.h"
#import "CocoaUtility.h"
#import "VirtualKeyboard.h"
#import "sdl.h"

EmulationViewController *g_emulatorViewController;

@interface EmulationViewController(PrivateImplementation)

- (void)rotateToPortrait;
- (void)rotateToLandscape;
- (void)didRotate;
- (void)toggleInputMode:(UIButton*)sender;

@end

#define kDisplayFramePortrait					CGRectMake(0, 0, 320, 240)
#define kInputFramePortrait						CGRectMake(0, 0, 320, 480)

// stretched version, specifically cropped for IK+
#define kDisplayFrameLandscape					CGRectMake(0, 0, 480, 366)
//#define kDisplayFrameLandscape					CGRectMake(28, 0, 424, 320)
//#define kDisplayFrameLandscape					CGRectMake(32, 0, 416, 312)
#define kInputFrameLandscape					CGRectMake(0, 0, 480, 320)

// tabbar
#define kTabBarVisible							CGRectMake(0, 0, 320, 480)
#define kTabBarNotVisible						CGRectMake(0, 0, 320, 480 + 50)

// miscellaneous constants
const double kDefaultAnimationDuration					= 250.0 / 1000.0;

@implementation EmulationViewController

@synthesize emulator, emulatorState;
@synthesize displayView, inputController;
@synthesize landscapeJoystickView;

// Implement loadView to create a view hierarchy programmatically.
- (void)loadView {
	g_emulatorViewController		= self;
	self.wantsFullScreenLayout		= YES;
		
	self.hidesBottomBarWhenPushed	= YES;
	self.emulatorState				= EmulatorNotStarted;
	emulator						= &g_emulator;
	
	layoutOrientation				= (UIInterfaceOrientation)[[UIDevice currentDevice] orientation];
	
	// create all the views, order is important to ensure active areas of the UI are layered on top
	CGRect frame = [UIScreen mainScreen].bounds;
	UIView *view = [[UIView alloc] initWithFrame:frame];
	//view.autoresizingMask = UIViewAutoresizingFlexibleBottomMargin;
	view.autoresizingMask = (UIViewAutoresizingFlexibleBottomMargin | UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleWidth);
	view.backgroundColor = [UIColor blackColor];
	
	self.displayView = [[DisplayView alloc] initWithFrame:kDisplayFramePortrait];
	[view addSubview:self.displayView];
	
	
	self.inputController = [[InputControllerView alloc] initWithFrame:kInputFramePortrait];
	//self.inputController.delegate = self.landscapeJoystickView;
	[view addSubview:self.inputController];
	
	//self.landscapeJoystickView = [[JoystickViewLandscape alloc] initWithFrame:kInputFrameLandscape];
	//self.landscapeJoystickView.hidden = YES;
	//[self.inputController addSubview:self.landscapeJoystickView];
	
	// virtual keyboard
	vKeyboard = [[VirtualKeyboard alloc] initWithFrame:CGRectMake(0, 280, 200, 40)];
	inputModeView.autoresizingMask = UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleTopMargin;
	vKeyboard.hidden = YES;
	[view addSubview:vKeyboard];
	
	inputModeView = [UIButton buttonWithType:UIButtonTypeCustom];
	inputModeView.frame = CGRectMake(290, 5, 24, 24);
	inputModeView.autoresizingMask = UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleBottomMargin;
	inputModeView.alpha = 0.5;
	modes[0] = [[UIImage imageFromResource:@"joystick.png"] retain];
	modes[1] = [[UIImage imageFromResource:@"keyboard.png"] retain];
	modes[2] = [[UIImage imageFromResource:@"mouse.png"] retain];
	[inputModeView setImage:modes[0] forState:UIControlStateNormal];
	[inputModeView addTarget:self action:@selector(toggleInputMode:) forControlEvents:UIControlEventTouchUpInside];
	[view addSubview:inputModeView];
		
    self.view = view;
	[view setUserInteractionEnabled:NO];
    [view release];
	
	// monitor device rotation
	[[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
	[[NSNotificationCenter defaultCenter] addObserver:self
											 selector:@selector(didRotate)
												 name:@"UIDeviceOrientationDidChangeNotification" 
											   object:nil];
	
}

- (void)toggleInputMode:(UIButton*)sender {
	if (inputMode == 0) {
		vKeyboard.hidden = NO;
		inputMode = 1;
	} else {
		vKeyboard.hidden = YES;
		inputMode++;
		if (inputMode > 2)
			inputMode = 0;
	}

	
	[inputModeView setImage:modes[inputMode] forState:UIControlStateNormal];
}

#pragma mark Rotation handlers

#define degreesToRadian(x) (M_PI  * x / 180.0)

- (void)didRotate {
	if (self.tabBarController.selectedViewController != self)
		return;
	
	UIDeviceOrientation orientation = [[UIDevice currentDevice] orientation];
	if (!UIDeviceOrientationIsValidInterfaceOrientation(orientation) || layoutOrientation == (UIInterfaceOrientation)orientation)
		return;

	DLog(@"didRotate:");

	layoutOrientation = (UIInterfaceOrientation)orientation;
	
	[UIView beginAnimations:@"rotate" context:nil];

	[UIView setAnimationCurve:UIViewAnimationCurveEaseInOut];
	[UIView setAnimationDuration:kDefaultAnimationDuration];
		
	self.view.center = CGPointMake(160, 240);

	if (UIInterfaceOrientationIsLandscape(layoutOrientation)) {
		self.tabBarController.view.frame = kTabBarNotVisible;

		if (layoutOrientation == UIInterfaceOrientationLandscapeLeft) {
			self.view.transform = CGAffineTransformMakeRotation(degreesToRadian(-90));
		} else {
			self.view.transform = CGAffineTransformMakeRotation(degreesToRadian(90));
		}
		self.view.bounds = CGRectMake(0, 0, 480, 320);
		
		[self rotateToLandscape];
	} else {
		self.tabBarController.view.frame = kTabBarVisible;
		self.view.transform = CGAffineTransformIdentity;
		self.view.bounds = CGRectMake(0, 0, 320, 480);
		self.view.frame = CGRectMake(0, 0, 320, 480);
		
		[self rotateToPortrait];
	}
	[UIView commitAnimations];
}

- (void)rotateToPortrait {
	DLog(@"Rotating to portrait");
		
	self.displayView.frame = kDisplayFramePortrait;
	[self.displayView setNeedsLayout];
	inputModeView.frame = CGRectMake(290, 5, 24, 24);
	//self.landscapeJoystickView.hidden	= YES;
	//self.inputController.delegate		= joystickView;
	self.inputController.frame			= kInputFramePortrait;
}

- (void)rotateToLandscape {
	DLog(@"Rotating to landscape");

	self.displayView.frame				= kDisplayFrameLandscape;
	[self.displayView setNeedsLayout];
	
	//self.landscapeJoystickView.hidden	= NO;
	//self.inputController.delegate		= landscapeJoystickView;	
	self.inputController.frame			= kInputFrameLandscape;
}

- (void)viewDidAppear:(BOOL)animated {
	DLog(@"viewDidAppear: starting emulator");
	[self startEmulator];
}

- (void)viewWillDisappear:(BOOL)animated {
	DLog(@"viewWillDisappear: pausing emulator");
	[self pauseEmulator];
}

#pragma mark Emulator Functions

- (void)enableUserInteraction {
	[self.view setUserInteractionEnabled:YES];
}

- (void)startEmulator {
	if (!emulator) return;

	if (emulatorState == EmulatorPaused) {
		[self resumeEmulator];
	} else if (emulatorState == EmulatorNotStarted) {
		emulationThread = [[NSThread alloc] initWithTarget:self selector:@selector(runEmulator) object:nil];
		[emulationThread start];
		[self.displayView startTimer];
		[self performSelector:@selector(enableUserInteraction) withObject:nil afterDelay:0.25];
	}
}

- (void)stopEmulator {
	NSAssert(emulator != NULL, @"emulator should not be NULL");
	
	[displayView stopTimer];	
	[emulationThread release];
}

- (void)runEmulator {
	self.emulatorState = EmulatorRunning;
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	[NSThread setThreadPriority:0.7];
	emulator->real_main();
	[pool release];
}

- (void)pauseEmulator {
	NSAssert(emulator != NULL, @"emulator cannot be NULL");
	DLog(@"pausing emulator");
	
	[displayView stopTimer];
	emulatorState = EmulatorPaused;
}

- (void)resumeEmulator {
	NSAssert(emulator != NULL, @"emulator cannot be NULL");
	if (emulatorState != EmulatorPaused)
		return;
	
	DLog(@"resuming emulator");
	
	[displayView startTimer];
	emulatorState = EmulatorRunning;
}

- (void)dealloc {
	self.displayView		= nil;
	self.inputController	= nil;
	[super dealloc];	
}

@end
