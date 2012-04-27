//
//  DynamicLandscapeControls.mm
//  C64
//
//  Created by Stuart Carnie on 6/23/10.
//  Copyright 2010 Manomio LLC. All rights reserved.
//

#import "DynamicLandscapeControls.h"
#import "LandscapeJoystick.h"
#import "JoyButtonBase.h"
#import "MMFixedStickController.h"
#import "ControlDefaultConstants.h"

const int kButtonWidth = 200;

@interface DynamicLandscapeControls()

- (void)initializeState;
- (void)setCurrentStick;
- (UIView*)fixedJoystick;
- (UIView*)landscapeJoystick;
- (void)createJoystick;

@end

@implementation DynamicLandscapeControls

@synthesize layoutName=_layoutName;

+ (void)initialize {
    if (self != [DynamicLandscapeControls class]) return;
    
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
	
	NSDictionary* resourceDict = [NSDictionary dictionaryWithObjectsAndKeys:
								  [NSNumber numberWithBool:YES], kDefaultIsJoystickOnRight,
								  [NSNumber numberWithFloat:30.0], kDefaultJoystickDeadZone,
								  [NSNumber numberWithInt:1], kDefaultJoystickControlMode,
								  [NSNumber numberWithBool:YES], kDefaultIsJoystickFixedInLandscape,
								  nil];
	
	[defaults registerDefaults:resourceDict];
    [defaults synchronize];	
}
	
- (id)initWithFrame:(CGRect)frame {
    if ((self = [super initWithFrame:frame])) {
		[self initializeState];
    }
    return self;
}

- (void)initializeState {
    _defaultIsFixed = BOOL_SETTING(kDefaultIsJoystickFixedInLandscape);
    [self setCurrentStick];
    [self createJoystick];
    
    _joyButton = [[JoyButtonBase alloc] initWithFrame:CGRectMake(0, 0, kButtonWidth, CGRectGetHeight(self.frame))];
    [self addSubview:_joyButton];
    _joyButton.shouldSwitchSides = YES;

    self.layoutName = @"landscape";
}

- (void)awakeFromNib {
    [self initializeState];    
}

- (void)dealloc {
	[_joystick release];
	[_joyButton release];
	[super dealloc];
}

- (UIView*)fixedJoystick {
    CGRect rect;
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
        rect = CGRectMake(864, 404, 160, 160);
    else
        rect = CGRectMake(330, 170, 160, 160);
    
	UIView *r = [[MMFixedStickController alloc] initWithFrame:rect];
	r.alpha = 0.5f;
	return r;
}

- (UIView*)landscapeJoystick {
	UIView *r = [[LandscapeJoystick alloc] initWithFrame:self.frame];
	return r;
}

- (void)setCurrentStick {
	_currentStickClass = _defaultIsFixed || _isFixedOverride ? [MMFixedStickController class] : [LandscapeJoystick class];
}

- (void)createJoystick {
	if ([_joystick isKindOfClass:[_currentStickClass class]]) return;
	
	if (_joystick) {
		[_joystick removeFromSuperview];
		[_joystick release];
	}
	
	_joystick = [_currentStickClass isEqual:[MMFixedStickController class]] ? [self fixedJoystick] : [self landscapeJoystick];
	[self addSubview:_joystick];
}

- (void)actionClearButtons {
	[_joyButton removeFromSuperview];
}

- (void)actionDefaultButtons {
	// remove all views
	for (UIView* v in self.subviews) {
		[v removeFromSuperview];
	}
	
	[self addSubview:_joystick];
	[self addSubview:_joyButton];
}

- (void)actionDefaultStick {
	_isFixedOverride = NO;
	[self setCurrentStick];
	[self createJoystick];
}

- (void)setPreferredStick:(NSString*)stickMode {
	if ([stickMode isEqualToString:@"fixed"]) {
		_isFixedOverride = YES;
		_currentStickClass = [MMFixedStickController class];
		[self createJoystick];
	} else {
		_isFixedOverride = NO;
		[self setCurrentStick];
	}
}

- (void)defaultsChanged {
	_defaultIsFixed = BOOL_SETTING(kDefaultIsJoystickFixedInLandscape);
	[self setCurrentStick];
	[self createJoystick];
}

@end
