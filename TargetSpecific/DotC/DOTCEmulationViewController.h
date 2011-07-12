//
//  DOTCEmulationViewController.h
//  iAmiga
//
//  Created by Stuart Carnie on 7/11/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BaseEmulationViewController.h"
#import "AnimatedImageSequenceView.h"


@interface DOTCEmulationViewController : BaseEmulationViewController<AnimatedImageSequenceDelegate> {
    BOOL _introSequenceRunning;
}

- (IBAction)restart:(id)sender;

@end
