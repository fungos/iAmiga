//
//  MMFixedStickController.mm
//  C64
//
//  Created by Stuart Carnie on 7/6/10.
//  Copyright 2010 Manomio LLC. All rights reserved.
//

#import "MMFixedStickController.h"


@implementation MMFixedStickController

- (id)initWithFrame:(CGRect)frame {
    if ((self = [super initWithFrame:frame])) {
        [self setOpaque:NO];
		self.delegate = self;
		_isFixedCenter = YES;
		self.shouldSwitchSides = YES;
		_dPadState = -1;
    }
    return self;
}

#define DEG2RAD(angle)	((CGFloat)(angle) * M_PI / 180.0f)

#define SIZE_X 140
#define SIZE_Y 140
#define CTR_X  SIZE_X/2.0f
#define CTR_Y  SIZE_Y/2.0f


- (void)drawRect:(CGRect)rect {
    CGRect imageBounds = CGRectMake(0, 0, SIZE_X, SIZE_Y);
	CGRect bounds = self.bounds;
	CGContextRef context = UIGraphicsGetCurrentContext();
	
	CGContextSaveGState(context);
	CGContextTranslateCTM(context, bounds.origin.x, bounds.origin.y);
	CGContextScaleCTM(context, (bounds.size.width / imageBounds.size.width), (bounds.size.height / imageBounds.size.height));
	
	CGPoint points[] = {
		{ -10,  5 },
		{  00, -5 },
		{  10,  5 },
	};
	
	CGMutablePathRef path = CGPathCreateMutable();
	for (int i = 0; i < 8; i+=1) {
		
		CGAffineTransform tx = CGAffineTransformMakeTranslation(CTR_X, CTR_Y);
		tx = CGAffineTransformRotate(tx, DEG2RAD(i*360/8));
				
		if (i==_dPadState) {
			tx = CGAffineTransformTranslate(tx, 0, -50);
			tx = CGAffineTransformScale(tx, 1.3, 1.3);
		} else {
			tx = CGAffineTransformTranslate(tx, 0, -40);
		}
		
		CGPathAddLines(path, &tx, points, 3);		
		CGPathCloseSubpath(path);
	}
	
	UIColor *color = [UIColor colorWithRed:1.0f green:1.0f blue:1.0f alpha:1.0f];
	[color setFill];
	CGContextAddPath(context, path);
	CGContextFillPath(context);
	CGPathRelease(path);
	
	// outer ring
	[color setStroke];
	path = CGPathCreateMutable();
	CGContextSetLineWidth(context, 2);
	CGPathAddEllipseInRect(path, NULL, CGRectInset(imageBounds, 20, 20));
	CGContextAddPath(context, path);
	CGContextDrawPath(context, kCGPathStroke);
	CGPathRelease(path);
	
	// inner centre circle
	path = CGPathCreateMutable();
	CGRect inner = CGRectMake(0, 0, 20, 20);
	inner = CGRectOffset(inner, CTR_X-10, CTR_Y-10);
	CGPathAddEllipseInRect(path, NULL, inner);
	CGContextAddPath(context, path);
	CGContextFillPath(context);
	CGPathRelease(path);
	
	CGContextRestoreGState(context);
}

- (void)joystickStateChanged:(TouchStickDPadState)state {
	_dPadState = state-1;
	[self setNeedsDisplay];
}

@end
