//
//  TexturedCRT2Effect.m
//  iAmiga
//
//  Created by Stuart Carnie on 1/19/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import "TexturedCRTEffect.h"

#define USE_GL_REPEAT

#import "esUtil.h"

#define STRINGIFY(A)  #A
#include "Shaders/Simple.vert"
#include "Shaders/CRT.frag"

@interface TexturedCRTEffect()

- (void)loadEffect:(const char*)effectFile;

@end

@implementation TexturedCRTEffect

- (id)init {
	self = [super initWithVertexShaderSource:SimpleVertexShader andFragmentShaderSource:CRT2FragmentShader];
	if (self == nil)
		return nil;
	
	glGenTextures(1, &_textureId);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	
	[self setDisplayEffect:kDisplayEffectScanline50];	

	glActiveTexture(GL_TEXTURE0);
	
	_fxTextureCoord = [self getAttributeLocation:"FxTextureCoord"];

	return self;
}

- (void)setDisplayEffect:(DisplayEffect)effect {
	const char *effectFile;
	switch (effect) {
		default:
		case kDisplayEffectScanline50:
			effectFile = "Scanlines (50%)";
			break;
		case kDisplayEffectScanline100:
			effectFile = "Scanlines (100%)";
			break;
		case kDisplayEffectAperture1x2RB:
			effectFile = "Aperture (1x2 RB)";
			break;
		case kDisplayEffectAperture1x3RB:
			effectFile = "Aperture (1x3 RB)";
			break;
		case kDisplayEffectAperture2x4RB:
			effectFile = "Aperture (2x4 RB)";
			break;
		case kDisplayEffectAperture2x4BG:
			effectFile = "Aperture (2x4 BG)";
			break;
	}
	[self loadEffect:effectFile];
}

- (void)setUniforms {
	GLuint effectTextureSlot = glGetUniformLocation(_shaderProgram, "EffectTexture");
	glUniform1i(effectTextureSlot, 1);
	glEnableVertexAttribArray(_fxTextureCoord);
	const GLvoid *ofsFxTexCoords = (GLvoid*)offsetof(Vertex, FxTexCoords);
	glVertexAttribPointer(_fxTextureCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), ofsFxTexCoords);
}

- (void)updateCoords:(Vertex*)vertices count:(int)count viewSize:(CGSize)viewSize scale:(CGFloat)scale {
	float w = viewSize.width / (ef_w / scale);
	float h = viewSize.height / (ef_h / scale);

	vertices[1].FxTexCoords[1] = h;
	
	vertices[2].FxTexCoords[0] = w;
	vertices[2].FxTexCoords[1] = h;
	
	vertices[3].FxTexCoords[0] = w;
}

- (void)loadEffect:(const char *)effectFile {
	glActiveTexture(GL_TEXTURE1);
	char *effect = esLoadPNG(effectFile, kRETexturePixelFormat_RGBA8888, &ef_w, &ef_h);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ef_w, ef_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, effect);	
	free(effect);
	glActiveTexture(GL_TEXTURE0);
}

@synthesize fxTextureCoord=_fxTextureCoord;
@end
