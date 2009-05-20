//
//  iAmigaAppDelegate.h
//  iAmiga
//
//  Created by Stuart Carnie on 2/7/09.
//  Copyright __MyCompanyName__ 2009. All rights reserved.
//

#import <UIKit/UIKit.h>

@class DisplayView;

@interface iAmigaAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow					*window;
	NSThread					*emulationThread;
	DisplayView					*_displayView;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;

@end

