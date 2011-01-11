/* 
 Flashback for iPhone - Flashback interpreter
 Copyright (C) 2009 Stuart Carnie
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

#import "DisplayView.h"
#import <QuartzCore/QuartzCore.h>

static DisplayView* sharedView;

void UpdateScreen() {
	[sharedView performSelectorOnMainThread:@selector(updateScreen) withObject:nil waitUntilDone:NO];
}

@interface DisplayView() 

- (void)updateScreen;

@end

@implementation DisplayView

- (id)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
		sharedView = [self retain];
        self.opaque = YES;
    }
    return self;
}

extern CGContextRef context;

- (void)updateScreen {
	CALayer *layer = self.layer;
	CGImageRef image = CGBitmapContextCreateImage(context);
	layer.contents = (id)image;
	layer.contentsRect = CGRectMake(0.0, 0.0, 1.0, 1.0);
	CFRelease(image);
}

- (void)dealloc {
    [super dealloc];
}


@end
