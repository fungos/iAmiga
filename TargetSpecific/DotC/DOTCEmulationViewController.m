//
//  DOTCEmulationViewController.m
//  iAmiga
//
//  Created by Stuart Carnie on 7/11/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import "DOTCEmulationViewController.h"
#import "LambdaAlert.h"

@interface DOTCEmulationViewController()

- (void)startIntroSequence;

@end

@implementation DOTCEmulationViewController

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
        _introSequenceRunning = NO;
    }];
}

@end
