//
//  OGLShaderProgram.h
//  iAmiga
//
//  Created by Stuart Carnie on 1/17/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <OpenGLES/ES2/gl.h>
#import "OGLTypes.h"

@interface OGLShaderProgram : NSObject {
	GLuint		_vertexShader;
	GLuint		_fragmentShader;
	GLuint		_shaderProgram;
	
	GLuint		position, textureCoord;
	GLuint		displayTexture, modelView, projection;
}

- (id)initWithVertexShaderSource:(const char*)vertexSource andFragmentShaderSource:(const char*)fragmentSource;
- (void)useProgram;
- (GLuint)getAttributeLocation:(const char*)name;
- (void)updateCoords:(Vertex*)vertices count:(int)count viewSize:(CGSize)viewSize scale:(CGFloat)scale;
- (void)setUniforms;

@property (nonatomic, readonly) GLuint shaderProgram;
@property (nonatomic, readonly) GLuint position;
@property (nonatomic, readonly) GLuint textureCoord;
@property (nonatomic, readonly) GLuint displayTexture;
@property (nonatomic, readonly) GLuint modelView;
@property (nonatomic, readonly) GLuint projection;

@end
