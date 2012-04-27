//
//  ControlDefaultConstants.h
//  iAmiga
//
//  Created by Stuart Carnie on 12/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#define BOOL_SETTING(x)     [[NSUserDefaults standardUserDefaults] boolForKey:x]
#define INT_SETTING(x)      [[NSUserDefaults standardUserDefaults] integerForKey:x]
#define FLOAT_SETTING(x)    [[NSUserDefaults standardUserDefaults] floatForKey:x]

extern NSString * const kDefaultIsJoystickOnRight;
extern NSString * const kDefaultIsJoystickFixedInLandscape;
extern NSString * const kDefaultJoystickControlMode;
extern NSString * const kDefaultJoystickDeadZone;