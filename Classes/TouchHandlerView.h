//
//  TouchHandlerView.h
//  iAmiga
//
//  Created by Stuart Carnie on 1/2/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface TouchHandlerView : UIView {
	UITouch			*leadTouch;
    UITouch         *rightTouch;
	CGPoint			previousMouseLocation;
	BOOL			didMove;
    CGFloat         x_ratio, y_ratio;
}

@end
