//
//  BaseControlsView.h
//  C64
//
//  Created by Stuart Carnie on 6/17/10.
//  Copyright 2010 Manomio LLC. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface BaseControlsView : UIView {
	NSDictionary		*_layout;
	BOOL				_controlLayoutChanged;
	BOOL				_joystickOnRight;
}

- (NSString*)layoutName;
- (void)updateLayout:(NSDictionary*)dictionary;

/*! overridden in derived class to generate any missing controls
 */
- (void)generateMissingControls;

@end
