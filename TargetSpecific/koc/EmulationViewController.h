//
//  EmulationViewController.h
//  iAmiga
//
//  Created by Stuart Carnie on 7/11/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BaseEmulationViewController.h"
#import "AnimatedImageSequenceView.h"


@interface EmulationViewController : BaseEmulationViewController<AnimatedImageSequenceDelegate, UIWebViewDelegate> {
    BOOL _introSequenceRunning;
}

- (IBAction)restart:(id)sender;

@end
