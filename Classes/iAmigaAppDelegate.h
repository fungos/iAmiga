//
//  iAmigaAppDelegate.h
//  iAmiga
//
//  Created by Stuart Carnie on 2/7/09.
//  Copyright __MyCompanyName__ 2009. All rights reserved.
//

#import <UIKit/UIKit.h>

@class EmulationViewController;

@interface iAmigaAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow					*window;
	EmulationViewController		*_emulationView;
	UITabBarController			*_mainController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet UITabBarController *mainController;

@end

