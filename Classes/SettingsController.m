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

extern int mainMenu_showStatus;

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
	
	status.on = mainMenu_showStatus ? YES : NO;
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
	[path getCString:changed_df[df]];
    real_changed_df[df]=1;
}

extern void uae_reset();

- (void)resetAmiga:(id)sender {
	uae_reset();
}

- (IBAction)toggleStatus:(UISwitch*)sender {
	mainMenu_showStatus = sender.on ? 1 : 0;
}

extern void DISK_motors_off();

- (IBAction)otherAction:(UIControl*)sender {
	int tag = sender.tag;
	if (tag == 1) {
		DISK_motors_off();
	}
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
