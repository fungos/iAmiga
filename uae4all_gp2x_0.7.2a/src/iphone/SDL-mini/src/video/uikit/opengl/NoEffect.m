//
//  ScanlinesEffect.m
//  iAmiga
//
//  Created by Stuart Carnie on 1/17/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import "NoEffect.h"

#define STRINGIFY(A)  #A
#include "Shaders/Simple.vert"
#include "Shaders/Simple.frag"

@implementation NoEffect

- (id)init {
	self = [super initWithVertexShaderSource:SimpleVertexShader andFragmentShaderSource:SimpleFragmentShader];
	if (self == nil)
		return nil;
		
	return self;
}

@end
