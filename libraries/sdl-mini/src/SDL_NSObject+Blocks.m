//
//  SDL_NSObject+Blocks.m
//  iAmiga
//
//  Created by Stuart Carnie on 7/22/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import "SDL_NSObject+Blocks.h"

@implementation NSObject(SDL_Blocks)

- (void)performBlock:(void (^)(void))block afterDelay:(NSTimeInterval)delayInSeconds {
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, delayInSeconds * NSEC_PER_SEC);
    dispatch_after(popTime, dispatch_get_main_queue(), block);
}

@end
