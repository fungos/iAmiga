//
//  SelectHardware.h
//  iAmiga
//
//  Created by Stuart Carnie on 6/19/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol SelectHardwareDelegate
- (void)didSelectHardware:(int)joystick name:(NSString*)name;
@end

@interface SelectHardware : UIViewController<UIPickerViewDataSource, UIPickerViewDelegate> {
    NSArray *controllers;
	id<SelectHardwareDelegate> delegate;
	NSInteger lastSelectedRow;
}
    
- (void)setDelegate:(id<SelectHardwareDelegate>)delegate;
- (IBAction)done:(id)sender;
    
@end
