//
//  UIKeyboardController.m
//  iAmiga
//
//  Created by Stuart Carnie on 12/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "UIKeyboardController.h"
#import "SDL.h"

@implementation UIKeyboardController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        
        for (UIButton *btn in self.view.subviews) {
            [btn addTarget:self action:@selector(keyDown:) forControlEvents:UIControlEventTouchDown];
            [btn addTarget:self action:@selector(keyUp:) forControlEvents:UIControlEventTouchUpInside | UIControlEventTouchUpOutside];
        }
        
        UIImage *light = [[UIImage imageNamed:@"amiga-beige-light"] stretchableImageWithLeftCapWidth:46.0f topCapHeight:0.0f];
        UIButton *btn = (UIButton *)[self.view viewWithTag:32];     // SPACE        
        [btn setBackgroundImage:light forState:UIControlStateNormal];
        
        UIImage *dark = [[UIImage imageNamed:@"amiga-beige-dark"] stretchableImageWithLeftCapWidth:46.0f topCapHeight:0.0f];
        btn = (UIButton *)[self.view viewWithTag:13];               // ENTER
        [btn setBackgroundImage:dark forState:UIControlStateNormal];
        btn = (UIButton *)[self.view viewWithTag:27];               // ESC
        [btn setBackgroundImage:dark forState:UIControlStateNormal];
        btn = (UIButton *)[self.view viewWithTag:304];              // LSHIFT
        [btn setBackgroundImage:dark forState:UIControlStateNormal];
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

SDLKey toKey(UIButton *sender) {
    SDLKey key;
    if (sender.tag > 0)
        key = sender.tag;
    else {
        key = [sender.titleLabel.text characterAtIndex:0];
        if (key >= 65 && key < 91)
            key += 32;
    }
    return key;
}

- (IBAction)keyDown:(UIButton *)sender {
    SDL_Event evt;
    evt.type = SDL_KEYDOWN;
    SDLKey key = toKey(sender);
    evt.key.keysym.sym = key;
    SDL_PushEvent(&evt);
}

- (IBAction)keyUp:(UIButton *)sender {
    SDL_Event evt;
    evt.type = SDL_KEYUP;
    SDLKey key = toKey(sender);
    evt.key.keysym.sym = key;
    SDL_PushEvent(&evt);    
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
	return YES;
}

@end
