//
//  EmulationView-iPhone.m
//  iAmiga
//
//  Created by Stuart Carnie on 6/23/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import "EmulationView-iPhone.h"
#import "TouchHandlerView.h"
#import "NSObject+Blocks.h"
#import "AnimatedImageSequenceView.h"

@interface EmulationViewiPhone()

- (void)handleResetDown:(id)sender;
- (void)handleResetUp:(id)sender;

@end

@implementation EmulationViewiPhone
@synthesize menuView;
@synthesize webView;
@synthesize bottomBar;
@synthesize mouseHandler;
@synthesize closeButton;
@synthesize menuButton;

#pragma mark - View lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
    [webView setBackgroundColor:[UIColor clearColor]];
    [webView setOpaque:NO];
}

- (void)viewWillAppear:(BOOL)animated {
    AnimatedImageSequenceView *view = [[AnimatedImageSequenceView alloc] initWithFrame:self.view.frame];
    view.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    [self.view addSubview:view];
    [view release];
    
    NSMutableArray *sequence = [NSMutableArray arrayWithObjects:
                                [FadeAction actionWithFadeIn:1.0f holdTime:4.0f fadeOut:1.0f forImageNamed:@"intro_1"],
                                [FadeAction actionWithFadeIn:1.0f holdTime:2.0f fadeOut:1.0f forImageNamed:@"intro_2"],
                                [FadeAction actionWithFadeIn:1.0f holdTime:5.0f fadeOut:1.0f forImageNamed:@"intro_3"],
                                nil
                                ];
    view.delegate = self;
    [view startWithSequence:sequence];    
}

- (void)sequenceDidFinishForView:(UIView *)view {
    [UIView animateWithDuration:1.0f animations:^(void) {
        view.alpha = 0.0f;
    } completion:^(BOOL finished) {
        [view removeFromSuperview];
    }];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsLandscape(interfaceOrientation);
}

- (void)handleResetDown:(id)sender {
    SDLKey keys[] = { SDLK_LCTRL, SDLK_PAGEUP, SDLK_PAGEDOWN };
    [self sendKeys:keys count:3 keyState:SDL_KEYDOWN afterDelay:0.0f];
}
- (void)handleResetUp:(id)sender {
    SDLKey keys[] = { SDLK_LCTRL, SDLK_PAGEUP, SDLK_PAGEDOWN };
    [self sendKeys:keys count:3 keyState:SDL_KEYUP afterDelay:0.0f];
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
                     }];
}

- (IBAction)showMenu:(UIView *)sender {
    [self pauseEmulator];
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

- (void)dealloc {
    [menuView release];
    [webView release];
    [bottomBar release];
    [mouseHandler release];
    [closeButton release];
    [menuButton release];
    [super dealloc];
}

- (void)viewDidUnload {
    [self setMenuView:nil];
    [self setWebView:nil];
    [self setBottomBar:nil];
    [self setMouseHandler:nil];
    [self setCloseButton:nil];
    [self setMenuButton:nil];
    [super viewDidUnload];
}
@end
