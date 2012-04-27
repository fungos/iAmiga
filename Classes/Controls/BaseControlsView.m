//
//  BaseControlsView.m
//  C64
//
//  Created by Stuart Carnie on 6/17/10.
//  Copyright 2010 Manomio LLC. All rights reserved.
//

#import "BaseControlsView.h"
#import "SupportsLeftRightLayout.h"
#import "ControlDefaultConstants.h"

#pragma mark - Views
#import "ImageJoyButton.h"
#import "StaticImage.h"
#import "ButtonJoyButton.h"

@interface BaseControlsView()
- (void)generateLayout;
- (void)defaultsChanged:(NSNotification*)notification;

#pragma mark - actions
- (void)actionDefaultButtons;
- (void)actionDefaultStick;
- (void)actionClearButtons;
- (void)setPreferredStick:(NSString*)stickMode;
- (void)defaultsChanged;

@end

@implementation BaseControlsView


- (id)initWithFrame:(CGRect)frame {
    if ((self = [super initWithFrame:frame])) {
        // Initialization code
		_controlLayoutChanged = YES;
		_joystickOnRight = BOOL_SETTING(kDefaultIsJoystickOnRight);
		[[NSNotificationCenter defaultCenter] addObserver:self 
												 selector:@selector(defaultsChanged:) 
													 name:NSUserDefaultsDidChangeNotification object:nil];
    }
    return self;
}

- (void)defaultsChanged:(NSNotification*)notification {
	[self defaultsChanged];

    
	BOOL newValue = BOOL_SETTING(kDefaultIsJoystickOnRight);
	if (newValue == _joystickOnRight)
		return;
	
	_joystickOnRight = newValue;
	[self setNeedsLayout];
}

- (void)defaultsChanged {}

- (NSString*)layoutName {
	[self doesNotRecognizeSelector:_cmd];
	return nil;
}

- (void)updateLayout:(NSDictionary*)dictionary {
	NSDictionary *layout = [dictionary objectForKey:[self layoutName]];
	if ([_layout isEqual:layout])
		return;
	
	[layout retain];
	[_layout release];
	_layout = layout;
	_controlLayoutChanged = YES;
	[self setNeedsLayout];
}

- (void)layoutSubviews {
	if (_controlLayoutChanged)
		[self generateLayout];
	
	BOOL swapped = !_joystickOnRight;
	
	for (id view in self.subviews) {
		if ([view conformsToProtocol:@protocol(SupportsLeftRightLayout)]) {
			UIView<SupportsLeftRightLayout> *v = view;
			if (v.shouldSwitchSides)
				v.swapped = swapped;
		}
		[view layoutSubviews];
	}
		
	_controlLayoutChanged = NO;
}


- (void)generateLayout {
	[self actionDefaultStick];
	[self actionDefaultButtons];
	
	// process options
	NSDictionary *options = [_layout objectForKey:@"options"];
	if (options) {
		NSString *preferredStick = [options objectForKey:@"preferredStick"];
		if (preferredStick) [self setPreferredStick:preferredStick];
	}
	
	// process layout (actions)
	NSArray *actions = [_layout objectForKey:@"actions"];
	for (NSDictionary *action in actions) {
		NSString *aType = [action objectForKey:@"action"];
		if (!aType) {
			NSLog(@"missing action type");
			continue;
		}
		
		if ([aType isEqualToString:@"clear"]) {
			[self actionClearButtons];
			continue;
		}
		
		if (![aType isEqualToString:@"add"]) {
			NSLog(@"unrecognized action type");
			continue;
		}
		
		NSString *type = [action objectForKey:@"type"];
		if (!type) {
			NSLog(@"missing 'type' for controls button");
			continue;
		}
		
		options = [action objectForKey:@"options"];
		if (!options) {
			NSLog(@"missing 'options' dictionary for controls button");
			continue;
		}
		
		// extract options
		
		// primary image
		NSString *imageName = [options objectForKey:@"image"];
		UIImage *primaryImage = nil;
		
		if (imageName) { 
            primaryImage = [UIImage imageNamed:imageName];
		}
		
		// secondary (down / active) image
		UIImage *activeImage = nil;
		if (![imageName hasSuffix:@"png"]) {
			activeImage = [UIImage imageNamed:[imageName stringByAppendingString:@"-active"]];
		}
		
		// Get size. If size is not specified, then use image size
		CGSize size;
		NSString *val;
		if ((val = [options objectForKey:@"size"])) {
			size = CGSizeFromString(val);
		} else {
			size = primaryImage.size;
		}
		
		// Get position. If pos not specified, the set to origin
		CGPoint pos = CGPointFromString([options objectForKey:@"pos"]);
		if ((val = [options objectForKey:@"pos"])) {
			pos = CGPointFromString(val);
		} else {
			pos = CGPointZero;
		}
		
		// adjust pos if setting center
		if ((val = [options objectForKey:@"center"])) {
			CGPoint desiredCenter = CGPointFromString(val);
			CGPoint currentCtr = { size.width / 2.0f, size.height / 2.0f };
			CGPoint delta = { desiredCenter.x - currentCtr.x, desiredCenter.y - currentCtr.y };
			pos = CGPointMake(pos.x + delta.x, pos.y + delta.y);
		}
		CGRect r = { pos, size };
		
		// view creation
		UIView<SupportsLeftRightLayout> *v = nil;
        /*
		if ([type isEqualToString:@"KeyButton"]) {
			NSString *key = [options objectForKey:@"key"];
			tagKey *keydecl = findKey([key cStringUsingEncoding:[NSString defaultCStringEncoding]]);

			v = [KeyButton buttonWithCode:keydecl->code buttonImage:primaryImage selectedImage:activeImage frame:r delegate:g_emulatorViewController];
		} else */
        if ([type isEqualToString:@"JoyButton"]) {
			ButtonJoyButton *btn = [ButtonJoyButton buttonWithImage:primaryImage selectedImage:activeImage frame:r];
			v = btn;
		} else if ([type isEqualToString:@"StaticImage"]) {
			StaticImage *img = [[StaticImage alloc] initWithImage:primaryImage andFrame:r];
			[img autorelease];
			v = img;
		}
		if (v) [self addSubview:v];
			
		NSNumber *vAlpha = [options objectForKey:@"alpha"];
		if (vAlpha)
			v.alpha = [vAlpha floatValue];
		
		NSNumber *vShouldSwapSides = [options objectForKey:@"autoSwap"];
		if (vShouldSwapSides)
			v.shouldSwitchSides = [vShouldSwapSides boolValue];
		else
			v.shouldSwitchSides = YES;
	}
	
	[self generateMissingControls];
}

- (void)generateMissingControls {}
			
#pragma mark -
#pragma mark actions

// should be overridden in a derived class to clear static buttons

- (void)actionDefaultButtons {}
- (void)actionDefaultStick {}
- (void)actionClearButtons {}
- (void)setPreferredStick:(NSString*)stickMode {}

- (void)dealloc {
    [super dealloc];
}


@end
