//
//  EmulationViewiPad.m
//  iAmiga
//
//  Created by Stuart Carnie on 6/23/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import "EmulationView-iPad.h"

@implementation EmulationViewiPad
@synthesize menuView;
@synthesize webView;
@synthesize menuButton;
@synthesize closeButton;
@synthesize mouseHandler;
@synthesize restartButton;

#pragma mark - View lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
    [webView setBackgroundColor:[UIColor clearColor]];
    [webView setOpaque:NO];
    webView.delegate = self;
}

- (void)dealloc {
    [menuButton release];
    [closeButton release];
    [menuView release];
    [mouseHandler release];
    [webView release];
    [restartButton release];
    [super dealloc];
}

- (void)viewDidUnload {
    [self setMenuButton:nil];
    [self setCloseButton:nil];
    [self setMenuView:nil];
    [self setMouseHandler:nil];
    [self setWebView:nil];
    [self setRestartButton:nil];
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

- (CGFloat)displayTop {
    return 59.0f;
}

@end
