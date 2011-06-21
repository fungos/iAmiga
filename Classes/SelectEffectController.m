//
//  SelectEffectController.m
//  iAmiga
//
//  Created by Stuart Carnie on 1/19/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import "SelectEffectController.h"


@implementation SelectEffectController

- (void)viewDidLoad {
    [super viewDidLoad];
	
	effects = [[NSMutableArray alloc] initWithObjects:
						 @"None",
						 @"Scanline (50%)",
						 @"Scanline (100%)",
						 @"Aperture 1x2 RB",
						 @"Aperture 1x3 RB",
						 @"Aperture 2x4 RB",
						 @"Aperture 2x4 BG",
						 nil];
	lastSelectedRow = 0;
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)thePickerView {	
	return 1;
}

- (NSInteger)pickerView:(UIPickerView *)thePickerView numberOfRowsInComponent:(NSInteger)component {	
	return [effects count];
}

- (NSString *)pickerView:(UIPickerView *)thePickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component {
	return [effects objectAtIndex:row];
}

- (void)pickerView:(UIPickerView *)thePickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component {	
	lastSelectedRow = row;
}

- (IBAction)done:(id)sender {
	[delegate didSelectEffect:lastSelectedRow name:[effects objectAtIndex:lastSelectedRow]];
	[self dismissModalViewControllerAnimated:YES];
}

- (void)setDelegate:(id<SelectEffectDelegate>)aDelegate {
	delegate = aDelegate;
}

- (void)dealloc {
    [super dealloc];
}


@end
