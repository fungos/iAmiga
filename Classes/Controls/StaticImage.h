//
//  StaticImage.h
//  C64
//
//  Created by Stuart Carnie on 7/14/10.
//  Copyright 2010 Manomio LLC. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BaseLeftRightAwareView.h"

@interface StaticImage : BaseLeftRightAwareView {

}

- (id)initWithImage:(UIImage*)image andFrame:(CGRect)frame;

@end
