//
//  ButtonJoyButton.h
//  C64
//
//  Created by Stuart Carnie on 7/14/10.
//  Copyright 2010 Manomio LLC. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BaseLeftRightAwareView.h"

@interface ButtonJoyButton : BaseLeftRightAwareView {
}

+ (ButtonJoyButton*)buttonWithImage:(UIImage*)image selectedImage:(UIImage*)selectedImage frame:(CGRect)frame;

@end
