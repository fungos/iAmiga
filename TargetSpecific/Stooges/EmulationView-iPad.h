//
//  EmulationViewiPad.h
//  iAmiga
//
//  Created by Stuart Carnie on 6/23/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "StoogesEmulationViewController.h"

@class DynamicLandscapeControls;
//@class UIKeyboardController;

@interface EmulationViewiPad : StoogesEmulationViewController {
    
    UIButton *menuButton;
    UIButton *closeButton;
    UIView *mouseHandler;
    UIButton *restartButton;
    DynamicLandscapeControls *inputController;
    UIView *menuView;
    UIWebView *webView;
    //UIKeyboardController *keyboardController;
}
- (IBAction)hideMenu:(id)sender;
- (IBAction)showMenu:(id)sender;
//- (IBAction)toggleKeyboard:(id)sender;

@property (nonatomic, retain) IBOutlet UIView *menuView;
@property (nonatomic, retain) IBOutlet UIWebView *webView;
@property (nonatomic, retain) IBOutlet UIButton *menuButton;
@property (nonatomic, retain) IBOutlet UIButton *closeButton;
@property (nonatomic, retain) IBOutlet UIView *mouseHandler;
@property (nonatomic, retain) IBOutlet UIButton *restartButton;
@property (nonatomic, retain) IBOutlet DynamicLandscapeControls *inputController;
- (IBAction)loadState:(id)sender;

@end
