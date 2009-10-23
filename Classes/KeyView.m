//
//  KeyView.m
//  iAmiga
//
//  Created by Stuart Carnie on 10/22/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import "KeyView.h"
#import "CocoaUtility.h"
#import <QuartzCore/QuartzCore.h>


@implementation KeyView


- (id)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
		keys = [UIImage imageFromResource:@"keys.png"];
		widthMultiplier = 1.0 / keys.size.width;
		
		CALayer *layer = self.layer;
		layer.contents = (id)keys.CGImage;
		layer.masksToBounds = YES;
		layer.opaque = YES;
		// something insignificant
		layer.contentsRect = CGRectMake(0.0, 0.0, widthMultiplier, 0.25);
    }
    return self;
}

- (void)showKey:(NSInteger)xx width:(NSInteger)ww key:(SDLKey)k {
	key = k;
	self.hidden = NO;
	CALayer *layer = self.layer;
	
	int row = 0;
	if (xx >= 1009) {
		row++;
		xx -= 1009;
	}
	if (xx >= 1009) {
		row++;
		xx -= 1009;
	}
	if (xx >= 1022) {
		row++;
		xx -= 1022;
	}
	
	CGFloat x = xx * widthMultiplier;
	CGFloat w = ww * widthMultiplier;
	layer.contentsRect = CGRectMake(x, row * 0.25, w, 0.25);
	self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, ww, 32.0);
}

- (void)hideKey {
	self.hidden = YES;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
	SDL_Event e = { SDL_KEYDOWN };
	e.key.keysym.sym = key;
	SDL_PushEvent(&e);
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
	SDL_Event e = { SDL_KEYUP };
	e.key.keysym.sym = key;
	SDL_PushEvent(&e);
}


- (void)dealloc {
    [super dealloc];
}


@end
