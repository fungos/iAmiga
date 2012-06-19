//
//  EmulationView-iPhone.h
//  iAmiga
//
//  Created by Stuart Carnie on 6/23/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "EmulationViewController.h"

@class DynamicLandscapeControls;

@interface EmulationViewiPhone : EmulationViewController {
    
    UIView *menuView;
    UIWebView *webView;
    UIView *bottomBar;
    UIView *mouseHandler;
    UIButton *closeButton;
    UIButton *menuButton;
    UIButton *restartButton;
    CGFloat _menuViewStartY;
    CGFloat _bottomBarStartY;
    DynamicLandscapeControls *inputController;
}
- (IBAction)hideMenu:(id)sender;
- (IBAction)showMenu:(id)sender;

@property (nonatomic, retain) IBOutlet UIView *menuView;
@property (nonatomic, retain) IBOutlet UIWebView *webView;
@property (nonatomic, retain) IBOutlet UIView *bottomBar;
@property (nonatomic, retain) IBOutlet UIView *mouseHandler;
@property (nonatomic, retain) IBOutlet UIButton *closeButton;
@property (nonatomic, retain) IBOutlet UIButton *menuButton;
@property (nonatomic, retain) IBOutlet UIButton *restartButton;
@property (nonatomic, retain) IBOutlet DynamicLandscapeControls *inputController;

@end
