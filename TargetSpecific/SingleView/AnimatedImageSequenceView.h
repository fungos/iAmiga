//
//  AnimatedImageSequenceView.h
//  iAmiga
//
//  Created by Stuart Carnie on 6/23/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface FadeAction : NSObject {
    NSTimeInterval _fadeInTime;
    NSTimeInterval _holdTime;
    NSString *_imageName;
    NSTimeInterval _fadeOutTime;
    UIColor *_backgroundColor;
}

@property (nonatomic, assign) NSTimeInterval fadeInTime;
@property (nonatomic, assign) NSTimeInterval holdTime;
@property (nonatomic, retain) NSString *imageName;
@property (nonatomic, assign) NSTimeInterval fadeOutTime;
@property (nonatomic, retain) UIColor *backgroundColor;

+ (FadeAction *)actionWithFadeIn:(NSTimeInterval)fadeIn holdTime:(NSTimeInterval)holdTime fadeOut:(NSTimeInterval)fadeOut forImageNamed:(NSString *)imageName;
- (id)initWithFadeIn:(NSTimeInterval)fadeIn holdTime:(NSTimeInterval)holdTime fadeOut:(NSTimeInterval)fadeOut forImageNamed:(NSString *)imageName;

@end

@protocol AnimatedImageSequenceDelegate <NSObject>

- (void)sequenceDidFinishForView:(UIView *)view;

@end

@interface AnimatedImageSequenceView : UIView {
    NSMutableArray *_sequence;
}

@property (nonatomic, retain) NSArray *sequence;
@property (nonatomic, assign) id<AnimatedImageSequenceDelegate> delegate;

- (void)startWithSequence:(NSMutableArray *)sequence;

@end
