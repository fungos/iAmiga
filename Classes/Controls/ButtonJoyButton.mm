//
//  ButtonJoyButton.m
//  C64
//
//  Created by Stuart Carnie on 7/14/10.
//  Copyright 2010 Manomio LLC. All rights reserved.
//

#import "ButtonJoyButton.h"
#import "touchstick.h"
#import "CocoaUtility.h"

extern CJoyStick g_touchStick;

@implementation ButtonJoyButton

#pragma mark - Instance methods

- (void)touchDown:(id)sender {
	g_touchStick.setButtonOneState(FireButtonDown);
}

- (void)touchUp:(id)sender {
    g_touchStick.setButtonOneState(FireButtonUp);
}

- (void)dealloc {
    [super dealloc];
}

#pragma mark -
#pragma mark Class methods

+ (ButtonJoyButton*)buttonWithImage:(UIImage*)image selectedImage:(UIImage*)selectedImage frame:(CGRect)frame {
	ButtonJoyButton *b = [[ButtonJoyButton alloc] initWithFrame:frame];
	
	UIButton* btn = [UIButton buttonWithImage:image andSelectedImage:selectedImage];
	btn.frame = CGRectMake(0, 0, frame.size.width, frame.size.height);
	[btn addTarget:b action:@selector(touchDown:) forControlEvents:UIControlEventTouchDown];
	[btn addTarget:b action:@selector(touchUp:) forControlEvents:UIControlEventTouchUpInside | UIControlEventTouchUpOutside];
	[b addSubview:btn];
	
	return [b autorelease];
}

@end
