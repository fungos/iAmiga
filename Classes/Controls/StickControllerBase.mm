//
//  StickControllerBase.mm
//  C64
//
//  Created by Stuart Carnie on 6/15/10.
//  Copyright 2010 Manomio LLC. All rights reserved.
//

#import "StickControllerBase.h"
#import "touchstick.h"
#import "JoystickDirMaps.h"
#import "ControlDefaultConstants.h"

extern CJoyStick g_touchStick;

@interface StickControllerBase()

- (void)calculateDPadState;
- (void)setDPadState:(tagDPadState)state;
- (void)initStickDefaults;
- (void)defaultsChanged:(NSNotification*)notification;
- (void)gameChanged;

@end

@implementation StickControllerBase

- (id)initWithFrame:(CGRect)frame {
    if ((self = [super initWithFrame:frame])) {
		_stickVector = new CGVector2D();
		_stickCenter = CGPointMake(frame.size.width / 2.0, frame.size.height / 2.0);	// defaults to view center
		
		self.userInteractionEnabled = YES;	
		[self initStickDefaults];
		
		[[NSNotificationCenter defaultCenter] addObserver:self 
												 selector:@selector(defaultsChanged:) 
													 name:NSUserDefaultsDidChangeNotification object:nil];
		
    }
    return self;
}

- (void)dealloc {
	[[NSNotificationCenter defaultCenter] removeObserver:self];
	delete _stickVector;
    [super dealloc];
}

- (void)defaultsChanged:(NSNotification*)notification {
	[self updateFromDefaults];
}

- (void)updateFromDefaults {
	[self initStickDefaults];
}

- (void)initStickDefaults {
	_deadZone = FLOAT_SETTING(kDefaultJoystickDeadZone);
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
	UITouch *touch = [touches anyObject];
	
	if (_isFixedCenter) {
		// added
		_stickLocation = [touch locationInView:self];
		_stickVector->UpdateFromPoints(_stickCenter, _stickLocation);

		[self calculateDPadState];
	} else {
		_stickCenter = [touch locationInView:self];
		_stickVector->x = _stickVector->y = 0;
	}
	[_delegate trackingStarted:_stickCenter];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {	
	UITouch *touch = [touches anyObject];
	_stickLocation = [touch locationInView:self];
	_stickVector->UpdateFromPoints(_stickCenter, _stickLocation);
	[self calculateDPadState];
}

static const tagDPadState kDPadCenter = {DPadCenter, DPadCenter};

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
	_stickVector->x = _stickVector->y = 0;
	[self setDPadState:kDPadCenter];
	[_delegate trackingEnded];
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
	_stickVector->x = _stickVector->y = 0;
	[self setDPadState:kDPadCenter];
	[_delegate trackingEnded];
}

static tagDPadMap *currentMap = joydirs_8way;

static tagDPadState mapAngleToDPadState(tagDPadMap *map, float angle) {
	tagDPadMap *c=map;
	if (angle <= c->min || angle > c->max)
		return c->state;
	
	for (c++; c != nil; c++) {
		if (angle <= c->min && angle > c->max) {
			return c->state;
		}
	}
	return kDPadCenter;
}

- (void)calculateDPadState {
	if (_stickVector->length() <= _deadZone) {
		
		[self setDPadState:kDPadCenter];
		return;
	}
	
	CGFloat angle = _stickVector->angle();
	if (angle < 0) angle = 360 + angle;
	
	tagDPadState dPadState = mapAngleToDPadState(currentMap, angle);
	[self setDPadState:dPadState];
}

- (void)setDPadState:(tagDPadState)state {
	TouchStickDPadState oldState = g_touchStick.dPadState();
	if (oldState != state.dPadState) {
		g_touchStick.setDPadState(state.dPadState);
		[_delegate joystickStateChanged:state.joystickState];
	}
}

#pragma mark - StickControllerDelegate implementation

- (void)trackingStarted:(CGPoint)point {}
- (void)trackingEnded {}
- (void)joystickStateChanged:(TouchStickDPadState)state {}

#pragma mark - properties

@synthesize stickCenter = _stickCenter;
@synthesize delegate = _delegate;

@end
