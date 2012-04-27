//
//  BaseLeftRightAwareView.h
//  C64
//
//  Created by Stuart Carnie on 6/18/10.
//  Copyright 2010 Manomio LLC. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SupportsLeftRightLayout.h"

@interface BaseLeftRightAwareView : UIView<SupportsLeftRightLayout> {
	tagControlSide	defaultSide;
	BOOL shouldSwitchSides, swapped;
	CGRect _originalFrame;
}

@end
