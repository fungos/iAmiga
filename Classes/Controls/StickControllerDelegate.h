//
//  StickControllerDelegate.h
//  C64
//
//  Created by Stuart Carnie on 6/15/10.
//  Copyright 2010 Manomio LLC. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "touchstick-types.h"

@protocol StickControllerDelegate
- (void)trackingStarted:(CGPoint)point;
- (void)trackingEnded;

- (void)joystickStateChanged:(TouchStickDPadState)state;
@end
