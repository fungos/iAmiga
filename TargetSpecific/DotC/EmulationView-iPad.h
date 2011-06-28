//
//  EmulationViewiPad.h
//  iAmiga
//
//  Created by Stuart Carnie on 6/23/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BaseEmulationViewController.h"

@interface EmulationViewiPad : BaseEmulationViewController {
    
    UIButton *menuButton;
    UIButton *closeButton;
    UIView *mouseHandler;
    UIView *menuView;
}
- (IBAction)hideMenu:(id)sender;
- (IBAction)showMenu:(id)sender;
@property (nonatomic, retain) IBOutlet UIView *menuView;
@property (nonatomic, retain) IBOutlet UIButton *menuButton;
@property (nonatomic, retain) IBOutlet UIButton *closeButton;
@property (nonatomic, retain) IBOutlet UIView *mouseHandler;

@end
