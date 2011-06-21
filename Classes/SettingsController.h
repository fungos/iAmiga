//
//  SettingsController.h
//  iAmiga
//
//  Created by Stuart Carnie on 9/30/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "EMUROMBrowserViewController.h"
#import "SelectEffectController.h"
#import "SelectHardware.h"

@interface SettingsController : UIViewController<SelectRomDelegate, SelectEffectDelegate, SelectHardwareDelegate> {
	IBOutlet UISwitch		*status;
	IBOutlet UISwitch		*displayModeNTSC;
	IBOutlet UIButton		*resetLog;
	IBOutlet UISwitch		*logging;
	IBOutlet UILabel		*loggingLabel;
	IBOutlet UIButton		*effect;
    IBOutlet UIButton       *controller;
}

- (IBAction)selectDrive:(UIButton*)sender;
- (IBAction)resetAmiga:(id)sender;
- (IBAction)toggleStatus:(id)sender;
- (IBAction)otherAction:(id)sender;
- (IBAction)toggleNTSC:(id)sender;
- (IBAction)resetLog:(id)sender;
- (IBAction)toggleLogging:(id)sender;
- (IBAction)selectEffect:(id)sender;
- (IBAction)integralSize:(id)sender;
- (IBAction)selectController:(id)sender;

@end
