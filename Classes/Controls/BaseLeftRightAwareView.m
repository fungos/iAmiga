//
//  BaseLeftRightAwareView.m
//  C64
//
//  Created by Stuart Carnie on 6/18/10.
//  Copyright 2010 Manomio LLC. All rights reserved.
//

#import "BaseLeftRightAwareView.h"

@implementation BaseLeftRightAwareView

- (id)initWithFrame:(CGRect)frame {
    if ((self = [super initWithFrame:frame])) {
		_originalFrame = frame;
		swapped = NO;
    }
    return self;
}

- (void)setSwapped:(BOOL)value {
	if (swapped == value) return;
	
	swapped = value;
}

- (void)layoutSubviews {
	CGRect screen = self.superview.bounds;
	CGFloat ctr = CGRectGetMidX(screen);
	CGFloat frameCtr = CGRectGetMidX(_originalFrame);
	CGFloat centerDelta = ctr - frameCtr;
	
	if (swapped) {
		self.center = CGPointMake(ctr + centerDelta, self.center.y);
	} else {
		self.center = CGPointMake(ctr - centerDelta, self.center.y);
	}
}

- (void)dealloc {
    [super dealloc];
}

@synthesize defaultSide, swapped, shouldSwitchSides;

@end
