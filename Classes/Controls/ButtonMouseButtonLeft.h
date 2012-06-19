#import <UIKit/UIKit.h>
#import "BaseLeftRightAwareView.h"

@interface ButtonMouseButtonLeft : BaseLeftRightAwareView {
}

+ (ButtonMouseButtonLeft*)buttonWithImage:(UIImage*)image selectedImage:(UIImage*)selectedImage frame:(CGRect)frame;

@end
