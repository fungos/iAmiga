//
//  TexturedCRT2Effect.h
//  iAmiga
//
//  Created by Stuart Carnie on 1/19/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "OGLShaderProgram.h"

@interface TexturedCRTEffect : OGLShaderProgram {
	GLint				ef_w, ef_h;
	GLuint				_textureId;
	GLuint				_fxTextureCoord;
}

@property (nonatomic, readonly) GLuint fxTextureCoord;
- (void)setDisplayEffect:(DisplayEffect)effect;

@end
