//
//  DynamicLandscapeControls.h
//  C64
//
//  Created by Stuart Carnie on 6/23/10.
//  Copyright 2010 Manomio LLC. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BaseControlsView.h"

@class JoyButtonBase, LandscapeJoystick;

@interface DynamicLandscapeControls : BaseControlsView {
	UIView					*_joystick;
	JoyButtonBase			*_joyButton;
	Class					_currentStickClass;
	BOOL					_defaultIsFixed;
	BOOL					_isFixedOverride;
}

@property (nonatomic, retain) NSString *layoutName;

@end
