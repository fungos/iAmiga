//
//  KeyView.h
//  iAmiga
//
//  Created by Stuart Carnie on 10/22/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SDL.h"

@interface KeyView : UIView {
	UIImage			*keys;
	CGFloat			widthMultiplier;
	SDLKey			key;
}

- (void)showKey:(NSInteger)x width:(NSInteger)w key:(SDLKey)key;
- (void)hideKey;

@end
