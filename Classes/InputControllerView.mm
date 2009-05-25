/*
 Frodo, Commodore 64 emulator for the iPhone
 Copyright (C) 2007, 2008 Stuart Carnie
 See gpl.txt for license information.
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#import "InputControllerView.h"
#import "debug.h"
#import "touchstick.h"
#import "CGVector.h"
#import "CocoaUtility.h"

InputControllerView *sharedInstance;
extern CJoyStick g_touchStick;


@interface FireButtonView : UIView {
@public
	CJoyStick							*TheJoyStick;
	id<InputControllerChangedDelegate>	delegate;
	UIImageView							*fireImage;
	BOOL								showImage;
}

@property (nonatomic, assign)	BOOL	showImage;

@end

@implementation FireButtonView

@synthesize showImage;

- (id)initWithFrame:(CGRect)frame {
	self = [super initWithFrame:frame];
	
	showImage = NO;
	TheJoyStick = &g_touchStick;
	
	return self;
}

- (void)setShowImage:(BOOL)value {
	showImage = value;
	if (showImage) {
		if (!fireImage) {
			fireImage = [UIImageView newViewFromImageResource:@"ls-fire.png"];
			fireImage.hidden = YES;
			[self addSubview:fireImage];
		}
	} else {
		fireImage.hidden = YES;
	}
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
	TheJoyStick->setButtonOneState(FireButtonDown);
	[delegate fireButton:FireButtonDown];
	if (showImage) {
		UITouch *touch = [touches anyObject];
		fireImage.center = [touch locationInView:self];
		fireImage.hidden = NO;
	}
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {	
	// ignore
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
	TheJoyStick->setButtonOneState(FireButtonUp);
	[delegate fireButton:FireButtonUp];
	if (showImage) {
		fireImage.hidden = YES;
	}
}

- (void)dealloc {
	if (fireImage)
		[fireImage release];
	
	[super dealloc];
}

@end

@interface InputControllerView(PrivateMethods)

- (void)calculateDPadState;
- (void)setDPadState:(TouchStickDPadState)state;

@end

@implementation InputControllerView

const int kButtonWidthPortrait			= 110;
const int kButtonWidthLandscape			= 200;

@synthesize delegate;

- (id)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        // Initialization code
		button = [[FireButtonView alloc] initWithFrame:CGRectMake(0, 0, kButtonWidthPortrait, frame.size.height)];
		[self addSubview:button];
		_deadZone = 20.0f;	// radius, in pixels of the dead zone.
		_trackingStick = NO;
		_stickVector = new CGVector2D();
		sharedInstance = self;
		TheJoyStick = &g_touchStick;
    }
    return self;
}

- (void)setDelegate:(id<InputControllerChangedDelegate>)theDelegate {
	delegate = theDelegate;
	button->delegate = theDelegate;
}

- (void)layoutSubviews {
	CGPoint origin = self.frame.origin;
	CGSize size = self.frame.size;
	UIInterfaceOrientation current = (UIInterfaceOrientation)[[UIDevice currentDevice] orientation];
	if (UIInterfaceOrientationIsLandscape(current)) {
		button.frame = CGRectMake(0, 0, kButtonWidthLandscape, size.height);
		button.showImage = YES;
	} else {
		button.frame = CGRectMake(0, 0, kButtonWidthPortrait, size.height);
		button.showImage = NO;
	}
}

- (void)didAddSubview:(UIView*)theView {
	[self bringSubviewToFront:button];
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
	UITouch *touch = [touches anyObject];
	_stickCenter = [touch locationInView:self];
	_stickVector->x = _stickVector->y = 0;
	
	[self setDPadState:DPadCenter];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {	
	UITouch *touch = [touches anyObject];
	_stickLocation = [touch locationInView:self];
	_stickVector->UpdateFromPoints(_stickCenter, _stickLocation);
	[self calculateDPadState];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
	_stickVector->x = _stickVector->y = 0;
	[self setDPadState:DPadCenter];
}

- (void)dealloc {
	delete _stickVector;
    [super dealloc];
}

- (void)calculateDPadState {
	if (_stickVector->length() <= _deadZone) {
		[self setDPadState:DPadCenter];
		return;
	}
	
	CGFloat angle = _stickVector->angle();
	if (angle < 0) angle = 360 + angle;
	
	const CGFloat deg = 22.5;
	TouchStickDPadState dPadState;
	
	if (angle <= 0 + deg || angle > 360 - deg)
		dPadState = DPadRight;
	else if (angle <= 45 + deg && angle > 45 - deg)
		dPadState = DPadDownRight;
	else if (angle <= 90 + deg && angle > 90 - deg)
		dPadState = DPadDown;
	else if (angle <= 135 + deg && angle > 135 - deg)
		dPadState = DPadDownLeft;
	else if (angle <= 180 + deg && angle > 180 - deg)
		dPadState = DPadLeft;
	else if (angle <= 225 + deg && angle > 225 - deg)
		dPadState = DPadUpLeft;
	else if (angle <= 270 + deg && angle > 270 - deg)
		dPadState = DPadUp;
	else if (angle <= 315 + deg && angle > 315 - deg)
		dPadState = DPadUpRight;
	else
		dPadState = DPadCenter;

	[self setDPadState:dPadState];
}

- (void)setDPadState:(TouchStickDPadState)state {
	TouchStickDPadState oldState = TheJoyStick->dPadState();
	if (oldState != state) {
		TheJoyStick->setDPadState(state);
		[delegate joystickStateChanged:state];
	}
}


@end
