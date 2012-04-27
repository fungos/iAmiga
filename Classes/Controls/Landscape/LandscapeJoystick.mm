//
//  LandscapeJoystick.mm
//  C64
//
//  Created by Stuart Carnie on 6/16/10.
//  Copyright 2010 Manomio LLC. All rights reserved.
//

#import "LandscapeJoystick.h"
#import "ControlDefaultConstants.h"
#import "CocoaUtility.h"

#define LOAD_VIEW_IMAGE(var, file)  \
                                    var = [UIImageView newViewFromImageResource:file]; \
                                    if (!var.image) NSLog(@"ERROR: Image not found: %@", file);

static CGFloat	kOffsetFromCentre			= -70.0;
static CGFloat kDefaultShowHideDuration		= 50.0 / 1000.0;
static CGFloat kDefaultRotateDuration		= 50.0 / 1000.0;
static CGFloat kOffsetWhenFixed				= 40.0;
#define degreesToRadian(x)					(M_PI * x / 180.0)

@interface LandscapeJoystick()
- (void)initLSDefaults;
@end


@implementation LandscapeJoystick

- (id)initWithFrame:(CGRect)frame {
    if ((self = [super initWithFrame:frame])) {
        LOAD_VIEW_IMAGE(arrows, @"ls-bgimage.png");
		arrows.alpha = 0.0;
		[self addSubview:arrows];
		
        LOAD_VIEW_IMAGE(arrowDirection, @"ls-joystick_active.png");
		arrowDirection.alpha = 0.0;
		[self addSubview:arrowDirection];
		
        LOAD_VIEW_IMAGE(stickCentre, @"ls-joystick_rest.png");
		stickCentre.alpha = 0.0;
		[self addSubview:stickCentre];
		
		tracking = NO;

		[self initLSDefaults];
	}
    return self;
}

- (void)updateFromDefaults {
	[super updateFromDefaults];
	[self initLSDefaults];
}

- (void)initLSDefaults {
	switch (INT_SETTING(kDefaultJoystickControlMode)) {
		case 2:
		case 1: {  // fixed
			joystickAlpha = 0.4;
			
			arrows.alpha = joystickAlpha;
			stickCentre.alpha = joystickAlpha;
			arrowDirection.alpha = 0.0;
			tracking = YES;
			
			CGPoint pos = BOOL_SETTING(kDefaultIsJoystickOnRight) ? CGPointMake(CGRectGetHeight(self.frame) - kOffsetWhenFixed, kOffsetWhenFixed) : CGPointMake(kOffsetWhenFixed, kOffsetWhenFixed);
			arrows.center = pos;
			stickCentre.center = pos;
			arrowDirection.center = pos;
			
			currentScale = CGAffineTransformMakeScale(0.5, 0.5);
			arrows.transform = currentScale;
			stickCentre.transform = currentScale;
			arrowDirection.transform = currentScale;
			
			break;
		}
		case 0:
		default:
			arrows.alpha			= 0.0;
			stickCentre.alpha		= 0.0;
			arrowDirection.alpha	= 0.0;
			tracking = NO;
			joystickAlpha = 0.6;
			
			currentScale = CGAffineTransformIdentity;
			arrows.transform = currentScale;
			stickCentre.transform = currentScale;
			arrowDirection.transform = currentScale;
			break;
	}
}

- (void)trackingStarted:(CGPoint)point {
	if (controlMode == 0) {	
		tracking = YES;
		
		arrows.center = point;
		stickCentre.center = arrows.center;
		arrowDirection.center = arrows.center;
		[UIView beginAnimations:@"show" context:nil];
		[UIView setAnimationCurve:UIViewAnimationCurveEaseInOut];
		[UIView setAnimationDuration:kDefaultShowHideDuration];
		
		arrows.alpha = joystickAlpha;
		stickCentre.alpha = joystickAlpha;
		
		[UIView commitAnimations];
	}
}

- (void)trackingEnded {
	if (controlMode == 0) {
		tracking = NO;
		
		[UIView beginAnimations:@"hide" context:nil];
		[UIView setAnimationCurve:UIViewAnimationCurveEaseInOut];
		[UIView setAnimationDuration:kDefaultShowHideDuration];
		
		arrows.alpha			= 0.0;
		stickCentre.alpha		= 0.0;
		arrowDirection.alpha	= 0.0;
		
		[UIView commitAnimations];
	}
}

- (void)joystickStateChanged:(TouchStickDPadState)state {
	if (!tracking)
		return;
	
	bool animate = NO; // disable rotate animations
	
	if (state == DPadCenter) {
		arrowDirection.alpha = 0.0;
		stickCentre.alpha = joystickAlpha;
		return;
	} else if (stickCentre.alpha > 0.0) {
		stickCentre.alpha = 0.0;
		arrowDirection.alpha = joystickAlpha;
		// means we were back in the centre position, so don't animate.
		animate = NO;
	}
	
	CGAffineTransform transform = CGAffineTransformMakeTranslation(0, kOffsetFromCentre);
	transform = CGAffineTransformConcat(transform, currentScale);
	
	switch (state) {
		case DPadUpRight:
			transform = CGAffineTransformConcat(transform, CGAffineTransformMakeRotation(degreesToRadian(45)));
			break;
		case DPadRight:
			transform = CGAffineTransformConcat(transform, CGAffineTransformMakeRotation(degreesToRadian(90)));
			break;
		case DPadDownRight:
			transform = CGAffineTransformConcat(transform, CGAffineTransformMakeRotation(degreesToRadian(135)));
			break;
		case DPadDown:
			transform = CGAffineTransformConcat(transform, CGAffineTransformMakeRotation(degreesToRadian(180)));
			break;
		case DPadDownLeft:
			transform = CGAffineTransformConcat(transform, CGAffineTransformMakeRotation(degreesToRadian(225)));
			break;
		case DPadLeft:
			transform = CGAffineTransformConcat(transform, CGAffineTransformMakeRotation(degreesToRadian(270)));
			break;
		case DPadUpLeft:
			transform = CGAffineTransformConcat(transform, CGAffineTransformMakeRotation(degreesToRadian(315)));
			break;
	}
	
	if (animate) {
		[UIView beginAnimations:@"rotate" context:nil];
		[UIView setAnimationCurve:UIViewAnimationCurveEaseInOut];
		[UIView setAnimationDuration:kDefaultRotateDuration];
	}
	
	arrowDirection.transform = transform;
	arrowDirection.alpha = joystickAlpha;
	
	if (animate)
		[UIView commitAnimations];
}

- (void)dealloc {
    [super dealloc];
}


@end
