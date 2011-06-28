//
//  TouchHandlerView.m
//  iAmiga
//
//  Created by Stuart Carnie on 1/2/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import "TouchHandlerView.h"
#import "SDL_events.h"
#import "SDL_mouse_c.h"

@implementation TouchHandlerView


- (id)initWithFrame:(CGRect)frame {
    
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code.
		self.multipleTouchEnabled = YES;
    }
    return self;
}

- (void)awakeFromNib {
    self.multipleTouchEnabled = YES;
}

- (void)layoutSubviews {
    [super layoutSubviews];
    x_ratio = self.frame.size.width / 320.0f;
    y_ratio = self.frame.size.height / 240.0f;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
	UITouch *touch = (UITouch*)[touches anyObject];
	int count = [touches count];
	
	// this generates a left click when tapping with two fingers or 
	// with a second finger whilst dragging the first as the mouse
	if ((count == 2 && currentMode == kMouseNone) ||
		(count == 1 && currentMode == kMouseMove)) {
		currentMode |= kMouseClickLeft;
		clickTouch = touch;
		SDL_SendMouseButton(NULL, SDL_PRESSED, SDL_BUTTON_LEFT);
	}
	
	// this starts dragging action
	if (count == 1 && currentMode == kMouseNone) {
		currentMode |= kMouseMove;
		mouseTouch = touch;
		previousMouseLocation = [touch locationInView: self];
		didMove = NO;
		
		// if the user performed a double tap, then we'll also send a left click
		if (touch.tapCount == 2) {
			currentMode |= kMouseClickLeft;
			clickTouch = touch;
			SDL_SendMouseButton(NULL, SDL_PRESSED, SDL_BUTTON_LEFT);
		}
	}
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {	
	if (currentMode & kMouseMove) {
		if ([touches containsObject:mouseTouch]) {			
			CGPoint locationInView = [mouseTouch locationInView: self];
            CGFloat relx = (locationInView.x - previousMouseLocation.x) / x_ratio;
            CGFloat rely = (locationInView.y - previousMouseLocation.y) / y_ratio;
            if (fabsf(relx) < 1.0f)
                relx = 0.f;
            if (fabsf(rely) < 1.0f)
                rely = 0.f;
            
            if (relx != 0.0f || rely != 0.0f) {
                SDL_SendMouseMotion(NULL, SDL_MOTIONRELATIVE, relx, rely);
                if (relx != 0.0f)
                    previousMouseLocation.x = locationInView.x;
                if (rely != 0.0f)
                    previousMouseLocation.y = locationInView.y;
                didMove = YES;                
            }
		}
	}
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
	[self touchesEnded:touches withEvent:event];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
	if (currentMode & kMouseClickLeft && [touches containsObject:clickTouch]) {
		SDL_SendMouseButton(NULL, SDL_RELEASED, SDL_BUTTON_LEFT);
		clickTouch = nil;
		currentMode &= ~kMouseClickLeft;
	}
	
	if (currentMode & kMouseMove && [touches containsObject:mouseTouch]) {
		mouseTouch = nil;
		currentMode &= ~kMouseMove;
		if (didMove == NO) {
			SDL_SendMouseButton(NULL, SDL_PRESSED, SDL_BUTTON_LEFT);
			// 50ms after, push up
			dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 50 * 1000000), dispatch_get_main_queue(), ^{
				SDL_SendMouseButton(NULL, SDL_RELEASED, SDL_BUTTON_LEFT);
			}); 
			
		}
	}
}

- (void)dealloc {
    [super dealloc];
}


@end
