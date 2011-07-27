//
//  EmulationView-iPhone.m
//  iAmiga
//
//  Created by Stuart Carnie on 6/23/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import "EmulationView-iPhone.h"

@implementation EmulationViewiPhone
@synthesize menuView;
@synthesize webView;
@synthesize bottomBar;
@synthesize mouseHandler;
@synthesize closeButton;
@synthesize menuButton;
@synthesize restartButton;

#pragma mark - View lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
    [webView setBackgroundColor:[UIColor clearColor]];
    [webView setOpaque:NO];
    webView.delegate = self;
}

- (void)dealloc {
    [menuView release];
    [webView release];
    [bottomBar release];
    [mouseHandler release];
    [closeButton release];
    [menuButton release];
    [restartButton release];
    [super dealloc];
}

- (void)viewDidUnload {
    [self setMenuView:nil];
    [self setWebView:nil];
    [self setBottomBar:nil];
    [self setMouseHandler:nil];
    [self setCloseButton:nil];
    [self setMenuButton:nil];
    [self setRestartButton:nil];
    [super viewDidUnload];
}

- (IBAction)hideMenu:(UIView *)sender {
    menuButton.hidden = NO;
    closeButton.hidden = YES;
    [UIView animateWithDuration:0.500f 
                     animations:^(void) {
                         CGRect frame = menuView.frame;
                         frame.origin.y = _menuViewStartY;
                         menuView.frame = frame;
                         
                         frame = bottomBar.frame;
                         frame.origin.y = _bottomBarStartY;
                         bottomBar.frame = frame;

                     } completion:^(BOOL finished) {
                         [self resumeEmulator];
                         mouseHandler.userInteractionEnabled = YES;
                         restartButton.enabled = YES;
                     }];
}

- (IBAction)showMenu:(UIView *)sender {
    [self pauseEmulator];
    restartButton.enabled = NO;
    menuButton.hidden = YES;
    closeButton.hidden = NO;
    menuView.hidden = NO;
    mouseHandler.userInteractionEnabled = NO;

    _menuViewStartY = menuView.frame.origin.y;
    _bottomBarStartY = bottomBar.frame.origin.y;
    
    NSString *userGuidePath = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents/UserGuide.html"];
    if (![[NSFileManager defaultManager] fileExistsAtPath:userGuidePath]) {
        userGuidePath = [[NSBundle mainBundle] pathForResource:@"UserGuide" ofType:@"html"];
    }
    
    NSURLRequest *req = [NSURLRequest requestWithURL:[NSURL fileURLWithPath:userGuidePath]];
	[webView loadRequest:req];
    
    [UIView animateWithDuration:0.500f animations:^(void) {
        CGRect frame = menuView.frame;
        frame.origin.y = 0;
        menuView.frame = frame;
        
        frame = bottomBar.frame;
        frame.origin.y = -10;
        bottomBar.frame = frame;
    }];
}

@end
