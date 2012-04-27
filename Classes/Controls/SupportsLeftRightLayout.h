//
//  SupportsLeftRightLayout.h
//  C64
//
//  Created by Stuart Carnie on 6/17/10.
//  Copyright 2010 Manomio LLC. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef enum tagControlSide {
	ControlOnLeftSide,
	ControlOnRightSide
} tagControlSide;

@protocol SupportsLeftRightLayout
@required
/*! indicates the control should switch sides
 */
@property (nonatomic) BOOL shouldSwitchSides;
@property (nonatomic) tagControlSide defaultSide;
@property (nonatomic) BOOL swapped;
@end
