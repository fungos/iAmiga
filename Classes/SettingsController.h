//
//  SettingsController.h
//  iAmiga
//
//  Created by Stuart Carnie on 9/30/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "EMUROMBrowserViewController.h"

@interface SettingsController : UIViewController<SelectRomDelegate> {

}

- (IBAction)selectDrive:(UIButton*)sender;
- (IBAction)resetAmiga:(id)sender;

@end
