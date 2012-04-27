//
//  JoyButton.h
//  C64
//
//  Created by Stuart Carnie on 6/15/10.
//  Copyright 2010 Manomio LLC. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "touchstick-types.h"
#import "BaseLeftRightAwareView.h"

@interface JoyButtonBase : BaseLeftRightAwareView {
}

- (void)fireButton:(FireButtonState)state;

@end
