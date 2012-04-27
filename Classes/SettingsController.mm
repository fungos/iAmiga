//
//  SettingsController.m
//  iAmiga
//
//  Created by Stuart Carnie on 9/30/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import "SettingsController.h"
#import "EMUROMBrowserViewController.h"
#import "EmulationViewController.h"
#import "SelectEffectController.h"
#import "EMUFileInfo.h"
#import "sysconfig.h"
#import "sysdeps.h"
#import "options.h"
#import "SDL.h"
#import "UIKitDisplayView.h"
#import "savestate.h"

#if DISASSEMBLER
#import "DisaSupport.h"
#endif

extern int mainMenu_showStatus;
extern int mainMenu_ntsc;

@implementation SettingsController

extern int do_disa;

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
	
	status.on = mainMenu_showStatus ? YES : NO;
	displayModeNTSC.on = mainMenu_ntsc ? YES : NO;
    [controller setTitle:@"iCADE" forState:UIControlStateNormal];
	
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

- (IBAction)selectDrive:(UIButton*)sender {
	EMUROMBrowserViewController *browser = [[EMUROMBrowserViewController alloc] initWithNibName:@"EMUROMBrowserView" bundle:nil];
	browser.delegate = self;
	browser.context = sender;
	[self presentModalViewController:browser animated:YES];
	[browser release];
}

- (IBAction)selectEffect:(id)sender {
	SelectEffectController *ctl = [[SelectEffectController alloc] initWithNibName:@"SelectEffectController" bundle:nil];
	[ctl setDelegate:self];
	[self presentModalViewController:ctl animated:YES];
	[ctl release];
}

- (void)didSelectEffect:(int)aEffect name:(NSString*)name {
	SDL_Surface *video = SDL_GetVideoSurface();
	id<DisplayViewSurface> display = (id<DisplayViewSurface>)video->userdata;
	display.displayEffect = (DisplayEffect)aEffect;
	[effect setTitle:name forState:UIControlStateNormal];
}

- (IBAction)selectController:(id)sender {
    SelectHardware *ctl = [[SelectHardware alloc] initWithNibName:@"SelectHardware" bundle:nil];
	[ctl setDelegate:self];
	[self presentModalViewController:ctl animated:YES];
	[ctl release];
}

extern void switch_joystick(int joynum);

- (void)didSelectHardware:(int)joystick name:(NSString *)name {
    [controller setTitle:name forState:UIControlStateNormal];
    switch_joystick(joystick);
}

- (void)didSelectROM:(EMUFileInfo *)fileInfo withContext:(UIButton*)sender {
	NSString *path = [fileInfo path];
	int df = sender.tag;
	[sender setTitle:[fileInfo fileName] forState:UIControlStateNormal];
	[path getCString:changed_df[df] maxLength:256 encoding:[NSString defaultCStringEncoding]];
    real_changed_df[df]=1;
}

extern "C" void uae_reset();

- (void)resetAmiga:(id)sender {
	uae_reset();
}

- (IBAction)integralSize:(UISwitch*)sender {
	g_emulatorViewController.integralSize = !sender.on;
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

- (IBAction)otherAction:(UIControl*)sender {
	int tag = sender.tag;
    
    static char statefile[1024];
    NSString *stateFileString = [[NSHomeDirectory() stringByAppendingPathComponent:@"Documents"] stringByAppendingPathComponent:@"savestate.asf"];
    [stateFileString getCString:statefile maxLength:sizeof(statefile) encoding:[NSString defaultCStringEncoding]];

    
    switch (tag) {
        case 1000:  // save
            savestate_filename = statefile;
            savestate_state = STATE_DOSAVE;
            break;
            
        case 1001:  // restore
            savestate_filename = statefile;
            savestate_state = STATE_DORESTORE;            
            break;
            
        default:
            break;
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
    [controller release];
    controller = nil;
	// Release any retained subviews of the main view.
	// e.g. self.myOutlet = nil;
	[status release];
}


- (void)dealloc {
    [controller release];
    [super dealloc];
}


@end
