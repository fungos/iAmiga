//
//  StickControllerBase.h
//  C64
//
//  Created by Stuart Carnie on 6/15/10.
//  Copyright 2010 Manomio LLC. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CGVector.h"
#import "touchstick.h"
#import "StickControllerDelegate.h"
#import "BaseLeftRightAwareView.h"

@interface StickControllerBase : BaseLeftRightAwareView<StickControllerDelegate> {
	CGPoint								_stickCenter;
	CGPoint								_stickLocation;
	CGVector2D							*_stickVector;
	BOOL								_trackingStick;
	
	float								_deadZone;		// represents the deadzone radius, where the DPad state will be considered DPadCenter
	id<StickControllerDelegate>			_delegate;
	
@protected
	BOOL								_isFixedCenter;
}

@property (nonatomic) CGPoint stickCenter;
@property (nonatomic, assign) id<StickControllerDelegate> delegate;

/*! override in derived class to initialize any implementation specific defaults
 */
- (void)updateFromDefaults;

@end
