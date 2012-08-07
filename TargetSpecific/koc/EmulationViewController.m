//
//  EmulationViewController.m
//  iAmiga
//
//  Created by Stuart Carnie on 7/11/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import "EmulationViewController.h"
#import "LambdaAlert.h"

@interface EmulationViewController()

- (void)startIntroSequence;

@end

@implementation EmulationViewController

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsLandscape(interfaceOrientation);
}

- (void)viewWillAppear:(BOOL)animated {
    [self startIntroSequence];
}

extern void uae_reset();

- (IBAction)restart:(id)sender {
    LambdaAlert *alert = [[LambdaAlert alloc] initWithTitle:@"RESTART?" message:@"Are you sure you wish to restart?"];
    [alert addButtonWithTitle:@"No" block:nil];
    [alert addButtonWithTitle:@"YES" block:^(void) {
        uae_reset();
        [self startIntroSequence];
    }];
    [alert show];
    [alert release];
}

- (void)startIntroSequence {
    if (_introSequenceRunning) return;
    _introSequenceRunning = YES;
    
    AnimatedImageSequenceView *view = [[AnimatedImageSequenceView alloc] initWithFrame:self.view.bounds];
    view.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    [self.view addSubview:view];
    [view release];
    
    NSMutableArray *sequence = [NSMutableArray arrayWithObjects:
                                [FadeAction actionWithFadeIn:1.0f holdTime:23.0f fadeOut:1.0f forImageNamed:@"intro_1"],
//                                [FadeAction actionWithFadeIn:1.0f holdTime:3.0f fadeOut:1.0f forImageNamed:@"intro_2"],
//                                [FadeAction actionWithFadeIn:1.0f holdTime:5.5f fadeOut:1.0f forImageNamed:@"intro_3"],
                                [FadeAction actionWithFadeIn:1.0f holdTime:2.5f fadeOut:1.0f forImageNamed:@"intro_4"],
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
        _introSequenceRunning = NO;
    }];
}

- (void)webViewDidFinishLoad:(UIWebView *)webView {
    NSString *fn = [NSString stringWithFormat:@"setVersion('%@');", self.bundleVersion];
    NSString *result = [webView stringByEvaluatingJavaScriptFromString:fn];
}

@end
