#import "ButtonMouseButtonLeft.h"
#import "SDL_events.h"
#import "SDL_mouse_c.h"
#import "CocoaUtility.h"

@implementation ButtonMouseButtonLeft

#pragma mark - Instance methods

- (void)touchDown:(id)sender {
    SDL_SendMouseButton(NULL, SDL_PRESSED, SDL_BUTTON_LEFT);
}

- (void)touchUp:(id)sender {
    SDL_SendMouseButton(NULL, SDL_RELEASED, SDL_BUTTON_LEFT);
}

- (void)dealloc {
    [super dealloc];
}

#pragma mark -
#pragma mark Class methods

+ (ButtonMouseButtonLeft*)buttonWithImage:(UIImage*)image selectedImage:(UIImage*)selectedImage frame:(CGRect)frame {
	ButtonMouseButtonLeft *b = [[ButtonMouseButtonLeft alloc] initWithFrame:frame];
	
	UIButton* btn = [UIButton buttonWithImage:image andSelectedImage:selectedImage];
	btn.frame = CGRectMake(0, 0, frame.size.width, frame.size.height);
	[btn addTarget:b action:@selector(touchDown:) forControlEvents:UIControlEventTouchDown];
	[btn addTarget:b action:@selector(touchUp:) forControlEvents:UIControlEventTouchUpInside | UIControlEventTouchUpOutside];
	[b addSubview:btn];
	
	return [b autorelease];
}

@end
