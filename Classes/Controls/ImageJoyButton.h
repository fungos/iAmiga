//
//  ImageJoyButton.h
//  C64
//
//  Created by Stuart Carnie on 6/22/10.
//  Copyright 2010 Manomio LLC. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "JoyButtonBase.h"

@interface ImageJoyButton : JoyButtonBase {
	UIImageView					*fireButton;
}

@property (nonatomic, assign) UIImage		*image;

@end
