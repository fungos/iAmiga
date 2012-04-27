//
//  StaticImage.m
//  C64
//
//  Created by Stuart Carnie on 7/14/10.
//  Copyright 2010 Manomio LLC. All rights reserved.
//

#import "StaticImage.h"


@implementation StaticImage

- (id)initWithImage:(UIImage*)image andFrame:(CGRect)frame {
    if ((self = [super initWithFrame:frame])) {
        UIImageView *v = [[UIImageView alloc] initWithImage:image];
		[self addSubview:v];
		[v release];
    }
    return self;
}

@end
