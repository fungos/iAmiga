#import <UIKit/UIKit.h>
#import "BaseLeftRightAwareView.h"

@interface ButtonMouseButtonRight : BaseLeftRightAwareView {
}

+ (ButtonMouseButtonRight*)buttonWithImage:(UIImage*)image selectedImage:(UIImage*)selectedImage frame:(CGRect)frame;

@end
