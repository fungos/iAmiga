//
//  SettingsController.m
//  iAmiga
//
//  Created by Stuart Carnie on 9/30/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import "SettingsController.h"
#import "EMUROMBrowserViewController.h"
#import "EMUFileInfo.h"
#import "sysconfig.h"
#import "sysdeps.h"
#import "options.h"

#if DISASSEMBLER
#import "DisaSupport.h"
#endif

extern int mainMenu_showStatus;
extern int mainMenu_ntsc;

@implementation SettingsController

/*
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if (self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil]) {
        // Custom initialization
    }
    return self;
}
*/

extern int do_disa;

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
	
	status.on = mainMenu_showStatus ? YES : NO;
	displayModeNTSC.on = mainMenu_ntsc ? YES : NO;
	
#if DISASSEMBLER
	resetLog.hidden = NO;
	logging.hidden = NO;
	loggingLabel.hidden = NO;
#endif
}

- (void)viewWillAppear:(BOOL)animated {
#if DISASSEMBLER
	logging.on = do_disa == 0 ? NO : YES;
#endif
}

/*
// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}
*/

- (IBAction)selectDrive:(UIButton*)sender {
	EMUROMBrowserViewController *browser = [[EMUROMBrowserViewController alloc] initWithNibName:@"EMUROMBrowserView" bundle:nil];
	browser.delegate = self;
	browser.context = sender;
	[self presentModalViewController:browser animated:YES];
	[browser release];
}

- (void)didSelectROM:(EMUFileInfo *)fileInfo withContext:(UIButton*)sender {
	NSString *path = [fileInfo path];
	int df = sender.tag;
	[sender setTitle:[fileInfo fileName] forState:UIControlStateNormal];
	[path getCString:changed_df[df] maxLength:256 encoding:[NSString defaultCStringEncoding]];
    real_changed_df[df]=1;
}

extern void uae_reset();

- (void)resetAmiga:(id)sender {
	uae_reset();
}

- (IBAction)toggleStatus:(UISwitch*)sender {
	mainMenu_showStatus = sender.on ? 1 : 0;
}

- (IBAction)resetLog:(id)sender {
#if DISASSEMBLER
	DisaCloseFile();
	DisaCreateFile(1);
#endif
}

- (IBAction)toggleLogging:(UISwitch*)sender {
#if DISASSEMBLER
	do_disa = sender.on ? 1 : 0;
#endif
}

extern void DISK_motors_off();

- (IBAction)otherAction:(UIControl*)sender {
	int tag = sender.tag;
	if (tag == 1) {
		DISK_motors_off();
	}
}

- (IBAction)toggleNTSC:(UISwitch*)sender {
	mainMenu_ntsc = sender.on ? 1 : 0;
}

- (void)didReceiveMemoryWarning {
	// Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
	
	// Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
	// Release any retained subviews of the main view.
	// e.g. self.myOutlet = nil;
	[status release];
}


- (void)dealloc {
    [super dealloc];
}


@end
