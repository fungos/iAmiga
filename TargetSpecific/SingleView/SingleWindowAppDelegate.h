//
//  SingleWindowAppDelegate.h
//  iAmiga
//
//  Created by Stuart Carnie on 6/21/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import <UIKit/UIKit.h>

@class BaseEmulationViewController;

@interface SingleWindowAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow							*window;	
	UIWindow							*externalWindow;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet BaseEmulationViewController *mainController;

@end
