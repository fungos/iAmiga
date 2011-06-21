/*
 *  UIKitDisplayView.h
 *  iAmiga
 *
 *  Created by Stuart Carnie on 1/14/11.
 *  Copyright 2011 Manomio LLC. All rights reserved.
 *
 */

#include <Foundation/Foundation.h>
#include "OGLTypes.h"

@protocol DisplayViewSurface

@property (nonatomic)			BOOL			paused;
@property (nonatomic, readonly) void			*pixels;
@property (nonatomic)			DisplayEffect	displayEffect;

@end
