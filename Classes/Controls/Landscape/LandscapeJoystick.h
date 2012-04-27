//
//  LandscapeJoystick.h
//  C64
//
//  Created by Stuart Carnie on 6/16/10.
//  Copyright 2010 Manomio LLC. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "StickControllerBase.h"

@interface LandscapeJoystick : StickControllerBase {
	UIImageView					*arrows;
	UIImageView					*arrowDirection;
	UIImageView					*stickCentre;
	BOOL						tracking;
	BOOL						controlMode;
	CGFloat						joystickAlpha;
	CGAffineTransform			currentScale;
}

@end
