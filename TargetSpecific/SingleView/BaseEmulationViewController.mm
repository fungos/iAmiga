//
//  BaseEmulationViewController.m
//  iAmiga
//
//  Created by Stuart Carnie on 6/22/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import "BaseEmulationViewController.h"
#import "uae.h"
#import "CocoaUtility.h"
#import "SDL.h"
#import "UIKitDisplayView.h"
#import "TouchHandlerView.h"

#define kDisplayWidth							320.0f
#define kDisplayHeight							240.0f


@interface BaseEmulationViewController()

@property (nonatomic, retain) UIView<DisplayViewSurface>	*displayView;
@property (nonatomic,retain) UIWindow	*displayViewWindow;
@property (nonatomic, readonly) CGRect currentDisplayFrame;

@end

@implementation BaseEmulationViewController

@synthesize displayView, displayViewWindow;
@synthesize integralSize=_integralSize;

- (void)dealloc
{
    [super dealloc];
}

#pragma mark - View lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // self.integralSize = YES;
    
    UIView *view = self.view;
    
    SDL_Init(0);
	SDL_Surface *surface = SDL_SetVideoMode(320, 240, 16, 0);
	UIView<DisplayViewSurface> *surfaceView = (UIView<DisplayViewSurface>*)surface->userdata;
	surfaceView.paused = NO;
	surfaceView.frame = self.currentDisplayFrame;
    
    // TODO: Remove, as this is Defender of the Crown specific
    UIView *touchHandler = [[TouchHandlerView alloc] initWithFrame:self.view.frame];
	touchHandler.autoresizingMask = UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleBottomMargin | UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
	[view addSubview:touchHandler];
    [touchHandler release];

	
	self.displayView = surfaceView;
	if (displayViewWindow != nil) {
		[displayViewWindow addSubview:self.displayView];
	} else {
		[view addSubview:self.displayView];
	}
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsLandscape(interfaceOrientation);
}

- (void)viewDidAppear:(BOOL)animated {
	[self startEmulator];
}

- (void)viewWillDisappear:(BOOL)animated {
	[self pauseEmulator];
}

- (void)setIntegralSize:(BOOL)value {
	_integralSize = value;
	self.displayView.frame = self.currentDisplayFrame;
}

static CGRect CreateIntegralScaledView(CGRect aFrame, BOOL top) {
	CGSize frameSize = aFrame.size;
	CGFloat scale = frameSize.width < frameSize.height ? floorf(frameSize.width / kDisplayWidth) : floorf(frameSize.height / kDisplayHeight);
	int width = kDisplayWidth * scale, height = kDisplayHeight * scale;
	CGFloat y = top ? 0 : (frameSize.height - height) / 2;
	return CGRectMake((frameSize.width - width) / 2, y, width, height);
}

- (CGRect)currentDisplayFrame {	
	if (_isExternal) {
		if (_integralSize) {
			return CreateIntegralScaledView(displayViewWindow.bounds, NO);
		}
		// assuming external display it's width > height
		return displayViewWindow.bounds;
	} 
    
	CGSize frameSize = self.view.frame.size;
    //if (self.tabBarController) {
    CGSize tmp = frameSize;
    frameSize.width = tmp.height;
    frameSize.height = tmp.width;
    //}
	
	if (_integralSize) {
		CGRect aFrame;
		if (UIInterfaceOrientationIsLandscape(self.interfaceOrientation)) {
			aFrame = CGRectMake(0, 0, frameSize.width, frameSize.height);
		} else {
			aFrame = self.view.frame;
		}
		return CreateIntegralScaledView(aFrame, YES);
	}
	
	// full-screen, landscape mode
	if (UIInterfaceOrientationIsLandscape(self.interfaceOrientation)) {
		// assuming landscape width > height
		return CGRectMake(0, 0, frameSize.width, frameSize.height);
	}
	
	// aspect fill (portrait mode)
	CGFloat xRatio = frameSize.width / kDisplayWidth;
	CGFloat yRatio = frameSize.height / kDisplayHeight;
	CGFloat ratio = MIN(xRatio, yRatio);
    
	return CGRectMake(0, 0, kDisplayWidth * ratio, kDisplayHeight * ratio);
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

#pragma mark - Emulator Functions

- (void)enableUserInteraction {
	[self.view setUserInteractionEnabled:YES];
}

- (void)startEmulator {
	if (emulatorState == EmulatorPaused) {
		[self resumeEmulator];
	} else if (emulatorState == EmulatorNotStarted) {
		emulationThread = [[NSThread alloc] initWithTarget:self selector:@selector(runEmulator) object:nil];
		[emulationThread start];
		[self performSelector:@selector(enableUserInteraction) withObject:nil afterDelay:0.25];
	}
}

- (void)stopEmulator {
	[emulationThread release];
    emulationThread = nil;
    emulatorState = EmulatorNotStarted;
}

- (void)runEmulator {
	emulatorState = EmulatorRunning;
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	[NSThread setThreadPriority:0.7];
	g_emulator.real_main();
	[pool release];
}

- (void)pauseEmulator {
	emulatorState = EmulatorPaused;
	g_emulator.uae_pause();
	displayView.paused = YES;
}

- (void)resumeEmulator {
	if (emulatorState != EmulatorPaused)
		return;
	emulatorState = EmulatorRunning;
	g_emulator.uae_resume();
	displayView.paused = NO;
}


@end
