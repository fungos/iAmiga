//
//  VirtualKeyboard.h
//  iAmiga
//
//  Created by Stuart Carnie on 10/22/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class KeyView;

@interface VirtualKeyboard : UIView {
	KeyView					*keyView;
	BOOL					tracking;
	struct t_foundKey		*currentKey;
}

@end
