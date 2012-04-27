//
//  ImageJoyButton.m
//  C64
//
//  Created by Stuart Carnie on 6/22/10.
//  Copyright 2010 Manomio LLC. All rights reserved.
//

#import "ImageJoyButton.h"


@implementation ImageJoyButton


- (id)initWithFrame:(CGRect)frame {
    if ((self = [super initWithFrame:frame])) {
        self.shouldSwitchSides = YES;
		
		fireButton = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, frame.size.width, frame.size.height)];
		[self addSubview:fireButton];
    }
    return self;
}

- (void)dealloc {
	[fireButton release];
    [super dealloc];
}

- (void)setImage:(UIImage *)image {
	fireButton.image = image;
}

- (UIImage*)image {
	return fireButton.image;
}

@end
