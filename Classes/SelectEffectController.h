//
//  SelectEffectController.h
//  iAmiga
//
//  Created by Stuart Carnie on 1/19/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol SelectEffectDelegate
- (void)didSelectEffect:(int)effect name:(NSString*)name;
@end

@interface SelectEffectController : UIViewController<UIPickerViewDataSource, UIPickerViewDelegate> {
	NSArray *effects;
	id<SelectEffectDelegate> delegate;
	NSInteger lastSelectedRow;
}

- (void)setDelegate:(id<SelectEffectDelegate>)delegate;
- (IBAction)done:(id)sender;

@end
