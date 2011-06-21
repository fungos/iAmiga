//
//  ButtonStates.m
//  TextEditing
//
//  Created by Infinite Sands on 3/25/11.
//

#import "iControlPadReaderView.h"
#import "ButtonStates.h"

@implementation iControlPadReaderView

- (id)initWithFrame:(CGRect)frame 
{
    self = [super initWithFrame:frame];
    inputView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 1, 1)];
    
    return self;
}

- (BOOL)canBecomeFirstResponder 
{ 
    return YES; 
}

// FIX ME: Is this necessary?
-(void) touchesBegan: (NSSet *) touches withEvent: (UIEvent *) event 
{
    [self becomeFirstResponder];
} 

//- (void) drawRect:(CGRect)rect 
//{
    // This space intentionally left blank. Woot.
//}

- (UIView*) inputView
{
    return inputView;
}

#pragma mark - Keyboard stuff

- (UITextAutocorrectionType)autocorrectionType {
    return UITextAutocorrectionTypeNo;
}

- (UITextAutocapitalizationType)autocapitalizationType {
    return UITextAutocapitalizationTypeNone;
}

- (UIKeyboardType)keyboardType {
    return UIKeyboardTypeDefault;
}

- (UIKeyboardAppearance)keyboardAppearance {
    return UIKeyboardAppearanceDefault;
}

- (UIReturnKeyType)returnKeyType {
    return UIReturnKeyDone;
}

- (BOOL)isContinuousSpellCheckingEnabled {
    return NO;
}

#pragma mark -
#pragma mark UIKeyInput Protocol Methods

- (BOOL)hasText {
    return NO;
}

extern void icp_handle(char c);

- (void)insertText:(NSString *)text {
    for(int i=0; i<[text length]; i++)
    {
        icp_handle([text characterAtIndex:i]);
    }
    
    static int cycleResponder = 0;
    if (++cycleResponder > 20) {
        // necessary to clear a buffer that accumulates internally
        cycleResponder = 0;
        [self resignFirstResponder];
        [self becomeFirstResponder];
    }
}

- (void)deleteBackward {
    // This space intentionally left blank to complete protocol. Woot.
}

/*
- (BOOL)respondsToSelector:(SEL)aSelector {
    return [super respondsToSelector:aSelector];
} */

@end