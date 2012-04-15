//
//  SDL_NSObject+Blocks.h
//  iAmiga
//
//  Created by Stuart Carnie on 7/22/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSObject(SDL_Blocks)

- (void)performBlock:(void (^)(void))block afterDelay:(NSTimeInterval)delayInSeconds;

@end
