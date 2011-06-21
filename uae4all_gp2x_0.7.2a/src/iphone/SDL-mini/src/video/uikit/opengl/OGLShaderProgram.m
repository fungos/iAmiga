//
//  OGLShaderProgram.m
//  iAmiga
//
//  Created by Stuart Carnie on 1/17/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import "OGLShaderProgram.h"
#import <OpenGLES/ES2/gl.h>

@interface OGLShaderProgram()

- (void)buildProgramWithVertexSource:(const char*)vertexSource andFragmentSource:(const char*)fragmentSource;

@end

@implementation OGLShaderProgram

- (id)initWithVertexShaderSource:(const char*)vertexSource andFragmentShaderSource:(const char*)fragmentSource {
	self = [super init];
	if (self == nil)
		return nil;
	
	[self buildProgramWithVertexSource:vertexSource andFragmentSource:fragmentSource];
	position = glGetAttribLocation(_shaderProgram, "Position");
	textureCoord = glGetAttribLocation(_shaderProgram, "TextureCoord");
	displayTexture = glGetUniformLocation(_shaderProgram, "DisplayTexture");
	projection = glGetUniformLocation(_shaderProgram, "Projection");
	modelView = glGetUniformLocation(_shaderProgram, "Modelview");
	
	return self;
}

- (void)dealloc {
	glDeleteProgram(_shaderProgram);
	glDeleteShader(_vertexShader);
	glDeleteShader(_fragmentShader);
	
	[super dealloc];
}

- (GLuint)getAttributeLocation:(const char*)name {
	return glGetAttribLocation(_shaderProgram, name);
}

- (void)updateCoords:(Vertex*)vertices count:(int)count viewSize:(CGSize)viewSize scale:(CGFloat)scale {}

- (void)useProgram {
	glUseProgram(_shaderProgram);
	[self setUniforms];
}

- (void)setUniforms {
}

static GLuint BuildShader(const char* source, GLenum shaderType) {
    GLuint shaderHandle = glCreateShader(shaderType);
	
#ifdef USE_GL_REPEAT
	const char* macro = "#define USE_GL_REPEAT\n";
#else
	const char* macro = "\n";
#endif
	const char* sources[]={ macro, source };
    glShaderSource(shaderHandle, 2, &sources[0], 0);
    glCompileShader(shaderHandle);
    
    GLint compileSuccess;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);
    
    if (compileSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetShaderInfoLog(shaderHandle, sizeof(messages), 0, &messages[0]);
		printf("%s", messages);
        exit(1);
    }
    
    return shaderHandle;
}

- (void)buildProgramWithVertexSource:(const char*)vertexSource andFragmentSource:(const char*)fragmentSource {
	
    _vertexShader = BuildShader(vertexSource, GL_VERTEX_SHADER);
    _fragmentShader = BuildShader(fragmentSource, GL_FRAGMENT_SHADER);
    
    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, _vertexShader);
    glAttachShader(_shaderProgram, _fragmentShader);
    glLinkProgram(_shaderProgram);
    
    GLint linkSuccess;
    glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &linkSuccess);
    if (linkSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetProgramInfoLog(_shaderProgram, sizeof(messages), 0, &messages[0]);
		printf("%s", messages);
        exit(1);
    }
}

@synthesize shaderProgram=_shaderProgram;
@synthesize position, textureCoord, displayTexture, modelView, projection;

@end
