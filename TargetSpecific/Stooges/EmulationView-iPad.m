//
//  EmulationViewiPad.m
//  iAmiga
//
//  Created by Stuart Carnie on 6/23/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import "EmulationView-iPad.h"
#import "sysconfig.h"
#import "sysdeps.h"
#import "options.h"
#import "DynamicLandscapeControls.h"
#import "JSON.h"
//#import "UIKeyboardController.h"

@implementation EmulationViewiPad
@synthesize menuView;
@synthesize webView;
@synthesize menuButton;
@synthesize closeButton;
@synthesize mouseHandler;
@synthesize restartButton;
@synthesize inputController;

#pragma mark - View lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
    [webView setBackgroundColor:[UIColor clearColor]];
    [webView setOpaque:NO];
    webView.delegate = self;
#ifdef USE_JOYSTICK
    mouseHandler.hidden = YES;
    
    NSString *controlLayout = [[NSBundle mainBundle] pathForResource:@"control-layout" ofType:@"json"];
    inputController.layoutName = (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) ? @"iphone" : @"ipad";
    [inputController updateLayout:[[NSString stringWithContentsOfFile:controlLayout usedEncoding:NULL error:NULL] JSONValue]];
    
    // iCADE mode
    //SDL_JoystickOpen(3);
    
//    keyboardController = [[UIKeyboardController alloc] initWithNibName:@"UIKeyboardController" bundle:nil];
//    [self.view addSubview:keyboardController.view];
//    CGRect keyboardFrame = keyboardController.view.frame;
//    keyboardFrame.origin.y = 768.0f;
//    keyboardController.view.frame = keyboardFrame;
//    keyboardController.view.alpha = 0.5;
    
#else
    inputController.hidden = YES;
#endif
}

- (void)dealloc {
    [menuButton release];
    [closeButton release];
    [menuView release];
    [mouseHandler release];
    [webView release];
    [restartButton release];
    [inputController release];
    //[keyboardController release];
    [super dealloc];
}

- (void)viewDidUnload {
    [self setMenuButton:nil];
    [self setCloseButton:nil];
    [self setMenuView:nil];
    [self setMouseHandler:nil];
    [self setWebView:nil];
    [self setRestartButton:nil];
    [self setInputController:nil];
    [super viewDidUnload];
}

- (IBAction)hideMenu:(id)sender {
    menuButton.hidden = NO;
    closeButton.hidden = YES;
    [UIView animateWithDuration:0.500f 
                     animations:^(void) {
                         CGRect frame = menuView.frame;
                         frame.origin.y = -frame.size.height;
                         menuView.frame = frame;                         
                     } completion:^(BOOL finished) {
                         [self resumeEmulator];
                         mouseHandler.userInteractionEnabled = YES;
                         restartButton.enabled = YES;
                     }];

}

- (IBAction)showMenu:(id)sender {
    [self pauseEmulator];
    restartButton.enabled = NO;

    menuButton.hidden = YES;
    closeButton.hidden = NO;
    menuView.hidden = NO;
    mouseHandler.userInteractionEnabled = NO;
    
    NSString *userGuidePath = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents/UserGuide~ipad.html"];
    if (![[NSFileManager defaultManager] fileExistsAtPath:userGuidePath]) {
        userGuidePath = [[NSBundle mainBundle] pathForResource:@"UserGuide~ipad" ofType:@"html"];
    }
    
    NSURLRequest *req = [NSURLRequest requestWithURL:[NSURL fileURLWithPath:userGuidePath]];
	[webView loadRequest:req];
    
    [UIView animateWithDuration:0.500f animations:^(void) {
        CGRect frame = menuView.frame;
        frame.origin.y = 0 + self.displayTop - 2;
        menuView.frame = frame;
    }];
}

//- (IBAction)toggleKeyboard:(id)sender {
//    static BOOL isVisible = NO;
//    CGRect frame = keyboardController.view.frame;
//    if (isVisible) {
//        frame.origin.y = 768.0f;
//    } else {
//        frame.origin.y = 768.0f - frame.size.height;        
//    }
//    
//    [UIView animateWithDuration:0.500f animations:^(void) {
//        keyboardController.view.frame = frame;
//        isVisible = !isVisible;
//    }];    
//}

- (CGFloat)displayTop {
    return 59.0f;
}

@end
