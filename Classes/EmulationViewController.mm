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
#import "TouchHandlerView.h"

EmulationViewController *g_emulatorViewController;

typedef struct {
	CGRect kDisplayFrame;
} ViewLayoutSettings;

@interface EmulationViewController()

- (void)rotateToPortrait;
- (void)rotateToLandscape;
- (void)didRotate;
- (void)toggleInputMode:(UIButton*)sender;
- (void)makeTabBarHidden:(BOOL)hide;
- (void)recalculateCurrentDisplayFrame:(CGRect)contentFrame;

@property (nonatomic,retain) UIWindow	*displayViewWindow;
@property (nonatomic, readonly) CGRect currentDisplayFrame;

@end

#define kDisplayWidth							320.0f
#define kDisplayHeight							240.0f
const float kDisplayRatio =						(kDisplayHeight / kDisplayWidth);

#define kInputFramePortrait						CGRectMake(0, 0, 320.0f * S_PSCALE, 480.0f * S_PSCALE)

// stretched version, specifically cropped for IK+
#define kInputFrameLandscape					CGRectMake(0, 0, 480.0f * S_LSCALE, 320.0f * S_PSCALE)

// miscellaneous constants
const double kDefaultAnimationDuration			= 250.0 / 1000.0;

@implementation EmulationViewController

@synthesize emulator, emulatorState;
@synthesize displayView, inputController;
@synthesize landscapeJoystickView;
@synthesize touchHandler;
@synthesize displayViewWindow;

CGFloat S_WIDTH, S_HEIGHT, S_HALFWIDTH, S_HALFHEIGHT, S_PSCALE, S_LSCALE;

// Implement loadView to create a view hierarchy programmatically.
- (void)loadView {

	UITabBarController *tabBarController = self.tabBarController;
	CGRect frame = CGRectMake(tabBarController.view.bounds.origin.x,
							  tabBarController.view.bounds.origin.y,
							  tabBarController.view.bounds.size.width,
							  tabBarController.view.bounds.size.height - tabBarController.tabBar.frame.size.height);

	S_WIDTH = frame.size.width;
	S_HEIGHT = frame.size.height;
	S_HALFWIDTH = S_WIDTH / 2.0f;
	S_HALFHEIGHT = S_HEIGHT / 2.0f;
	S_PSCALE = S_WIDTH / 320.0f;
	S_LSCALE = S_HEIGHT / 480.0f;
	
	
	g_emulatorViewController		= self;
	self.wantsFullScreenLayout		= YES;
		
	self.hidesBottomBarWhenPushed	= YES;
	self.emulatorState				= EmulatorNotStarted;
	emulator						= &g_emulator;
	
	layoutOrientation				= (UIInterfaceOrientation)[[UIDevice currentDevice] orientation];
	
	// create all the views, order is important to ensure active areas of the UI are layered on top
	UIView *view = [[UIView alloc] initWithFrame:frame];
	rootView = [view retain];
	view.autoresizingMask = (UIViewAutoresizingFlexibleBottomMargin | UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleWidth);
	view.backgroundColor = [UIColor blackColor];
	
	self.displayView = [[DisplayView alloc] initWithFrame:self.currentDisplayFrame];
	if (displayViewWindow != nil) {
		[displayViewWindow addSubview:self.displayView];
	} else {
		[view addSubview:self.displayView];
	}
		
	self.inputController = [[InputControllerView alloc] initWithFrame:frame];
	inputController.autoresizingMask = UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleBottomMargin | UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
	//self.inputController.delegate = self.landscapeJoystickView;
	[view addSubview:self.inputController];
	
	self.touchHandler = [[TouchHandlerView alloc] initWithFrame:frame];
	self.touchHandler.hidden = YES;
	touchHandler.autoresizingMask = UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleBottomMargin | UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
	[view addSubview:self.touchHandler];
	
	//self.landscapeJoystickView = [[JoystickViewLandscape alloc] initWithFrame:kInputFrameLandscape];
	//self.landscapeJoystickView.hidden = YES;
	//[self.inputController addSubview:self.landscapeJoystickView];
	
	// virtual keyboard
	vKeyboard = [[VirtualKeyboard alloc] initWithFrame:CGRectMake(0, 380 * S_PSCALE, 200*S_PSCALE, 40*S_PSCALE)];
	vKeyboard.autoresizingMask = UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleTopMargin;
	vKeyboard.hidden = YES;
	[view addSubview:vKeyboard];
	
	inputModeView = [UIButton buttonWithType:UIButtonTypeCustom];
	inputModeView.frame = CGRectMake(290 * S_PSCALE, 5, 24, 24);
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

- (CGRect)currentDisplayFrame {	
	if (_isExternal) {
		// assuming external display it's width > height
		return displayViewWindow.bounds;
	} 
	
	CGSize frameSize = rootView.frame.size;

	// full-screen, landscape mode
	if (UIInterfaceOrientationIsLandscape(layoutOrientation)) {
		// assuming landscape width > height
		return CGRectMake(0, 0, frameSize.height, frameSize.width);
	}
	
	// aspect fill (portrait mode)
	CGFloat xRatio = frameSize.width / kDisplayWidth;
	CGFloat yRatio = frameSize.height / kDisplayHeight;
	CGFloat ratio = MIN(xRatio, yRatio);

	return CGRectMake(0, 0, kDisplayWidth * ratio, kDisplayHeight * ratio);
}

- (void)makeTabBarHidden:(BOOL)hide {
	UITabBarController *tabBarController = self.tabBarController;
	
	// Custom code to hide TabBar
	if ( [tabBarController.view.subviews count] < 2 ) {
		return;
	}
	
	UIView *contentView;
	
	if ( [[tabBarController.view.subviews objectAtIndex:0] isKindOfClass:[UITabBar class]] ) {
		contentView = [tabBarController.view.subviews objectAtIndex:1];
	} else {
		contentView = [tabBarController.view.subviews objectAtIndex:0];
	}
	
	if (hide) {
		contentView.frame = tabBarController.view.bounds;
	}
	else {
		contentView.frame = CGRectMake(tabBarController.view.bounds.origin.x,
									   tabBarController.view.bounds.origin.y,
									   tabBarController.view.bounds.size.width,
									   tabBarController.view.bounds.size.height - tabBarController.tabBar.frame.size.height);
	}
	
	tabBarController.tabBar.hidden = hide;
}

- (void)setDisplayViewWindow:(UIWindow*)window isExternal:(BOOL)isExternal {
	_isExternal = isExternal;
	self.displayViewWindow = window;
	if (displayView == nil)
		return;
	
	if (window) {
		[window addSubview:displayView];
	} else {
		[self.view insertSubview:displayView atIndex:0];
	}
	
	self.displayView.frame = self.currentDisplayFrame;
}

- (void)toggleInputMode:(UIButton*)sender {
	vKeyboard.hidden = YES;
	touchHandler.hidden = YES;
	inputController.hidden = YES;
	
	if (++inputMode > 2)
		inputMode = 0;
	
	switch (inputMode) {
		case 0:
			inputController.hidden = NO;
			break;
			
		case 1:
			vKeyboard.hidden = NO;
			break;
			
		case 2:
			touchHandler.hidden = NO;
			break;
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
		
	if (UIInterfaceOrientationIsLandscape(layoutOrientation)) {
		CGFloat angle = (layoutOrientation == UIInterfaceOrientationLandscapeLeft) ? -90.0f : 90.0f;
		self.view.transform = CGAffineTransformMakeRotation(degreesToRadian(angle));

		[self makeTabBarHidden:YES];
		//[self rotateToLandscape];
	} else {
		self.view.transform = CGAffineTransformIdentity;

		[self makeTabBarHidden:NO];
		//[self rotateToPortrait];
	}
	
	self.displayView.frame = self.currentDisplayFrame;
	
	[UIView commitAnimations];
}

- (void)rotateToPortrait {
	DLog(@"Rotating to portrait");
		
	self.displayView.frame = self.currentDisplayFrame;
	[self.displayView setNeedsLayout];

	//self.landscapeJoystickView.hidden	= YES;
	//self.inputController.delegate		= joystickView;
}

- (void)rotateToLandscape {
	DLog(@"Rotating to landscape");

	self.displayView.frame				= self.currentDisplayFrame;
	[self.displayView setNeedsLayout];
	
	//self.landscapeJoystickView.hidden	= NO;
	//self.inputController.delegate		= landscapeJoystickView;	
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
		[self performSelector:@selector(enableUserInteraction) withObject:nil afterDelay:0.25];
	}
}

- (void)stopEmulator {
	NSAssert(emulator != NULL, @"emulator should not be NULL");
	
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
	
	emulatorState = EmulatorPaused;
	emulator->uae_pause();
}

- (void)resumeEmulator {
	NSAssert(emulator != NULL, @"emulator cannot be NULL");
	if (emulatorState != EmulatorPaused)
		return;
	
	DLog(@"resuming emulator");
	
	emulatorState = EmulatorRunning;
	emulator->uae_resume();
}

- (void)dealloc {
	self.displayView		= nil;
	self.inputController	= nil;
	[super dealloc];	
}

@end
