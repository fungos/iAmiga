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

@interface EmulationViewiPhone()

- (void)handleResetDown:(id)sender;
- (void)handleResetUp:(id)sender;

@end

@implementation EmulationViewiPhone

- (void)dealloc {
    [super dealloc];
}

#pragma mark - View lifecycle

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


- (IBAction)showMenu:(id)sender {
}
@end
