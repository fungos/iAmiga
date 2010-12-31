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
	IBOutlet UISwitch		*status;
	IBOutlet UISwitch		*displayModeNTSC;
	IBOutlet UIButton		*resetLog;
	IBOutlet UISwitch		*logging;
	IBOutlet UILabel		*loggingLabel;
}

- (IBAction)selectDrive:(UIButton*)sender;
- (IBAction)resetAmiga:(id)sender;
- (IBAction)toggleStatus:(id)sender;
- (IBAction)otherAction:(id)sender;
- (IBAction)toggleNTSC:(id)sender;
- (IBAction)resetLog:(id)sender;
- (IBAction)toggleLogging:(id)sender;

@end
