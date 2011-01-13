//
//  TouchHandlerView.h
//  iAmiga
//
//  Created by Stuart Carnie on 1/2/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import <UIKit/UIKit.h>

enum MouseActiveMode {
	kMouseNone,
	kMouseMove			= 0x0001,
	kMouseClickLeft		= 0x0002,
	kMouseClickRight	= 0x0004
};

typedef enum MouseActiveMode MouseActiveMode;

@interface TouchHandlerView : UIView {
	UITouch			*mouseTouch;
	UITouch			*clickTouch;
	MouseActiveMode currentMode;
	int				touchCount;
	CGPoint			previousMouseLocation;
	BOOL			didMove;
}

@end
