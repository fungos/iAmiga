//
//  JoyButton.m
//  C64
//
//  Created by Stuart Carnie on 6/15/10.
//  Copyright 2010 Manomio LLC. All rights reserved.
//

#import "JoyButtonBase.h"
#import "touchstick.h"

extern CJoyStick g_touchStick;

@implementation JoyButtonBase

- (void)dealloc {
    [super dealloc];
}

- (void)fireButton:(FireButtonState)state {
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
	g_touchStick.setButtonOneState(FireButtonDown);
	[self fireButton:FireButtonDown];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {	
	// ignore
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
	g_touchStick.setButtonOneState(FireButtonUp);
	[self fireButton:FireButtonUp];
}

@end
