//
//  OGLDisplay.m
//  iAmiga
//
//  Created by Stuart Carnie on 1/13/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import "OGLDisplay.h"
#import <OpenGLES/ES2/gl.h>

static OGLDisplay* sharedView = NULL;
static BOOL newFrame = NO;

UIView<DisplayViewSurface>* CreateOGLDisplayView(int width, int height) {
	return [[OGLDisplay alloc] initWithFrame:CGRectMake(0, 0, width, height) displaySize:CGSizeMake(width, height)];
}

UIView* GetSharedOGLDisplayView() {
    return sharedView;
}

@interface OGLDisplay() 

- (void)drawView;

@end

@interface OGLDisplay()

- (void)drawView:(CADisplayLink*)displayLink;
- (void)createRenderBuffer;
- (void)createFrameBuffer;
- (void)bindRenderBuffer;
- (void)initializeRenderer;
- (void)glOrthoLeft:(float)left right:(float)right bottom:(float)bottom top:(float)top near:(float)near far:(float)far;
- (void)setModelView;
- (void)bindDisplayTexture;
- (void)resizeView:(CGSize)size;
- (void)setTextureScaling;

@end

void UpdateOGLScreen() {
	newFrame = YES;
}

void glCheckError() {
	GLint err = glGetError(); 
	if (err != 0) {
		printf("glError: %d", err);
	}
}

#define GL_ERROR()	glCheckError()

const GLushort Indices[] = {
	0, 1, 2, 0, 2 , 3
};

@implementation OGLDisplay

+ (Class) layerClass {
    return [CAEAGLLayer class];
}

- (id)initWithFrame:(CGRect)frame displaySize:(CGSize)displaySize {
    
    self = [super initWithFrame:frame];
    if (!self)
		return nil;
	
	sharedView = self;
	
	_displaySize[0] = displaySize.width;
	_displaySize[1] = displaySize.height;
	
	_pixels = malloc(displaySize.width * displaySize.height * 2);	// RGB565, 2 bytes
	
	CAEAGLLayer* eaglLayer = (CAEAGLLayer*) super.layer;
	eaglLayer.opaque = YES;
	NSDictionary *props = [NSDictionary dictionaryWithObjectsAndKeys:
						   kEAGLColorFormatRGB565, kEAGLDrawablePropertyColorFormat, 
						   nil];
	eaglLayer.drawableProperties = props;
	
	self.contentScaleFactor = [[UIScreen mainScreen] scale];
	
	_glContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
	
	if (!_glContext || ![EAGLContext setCurrentContext:_glContext]) {
		[self release];
		return nil;
	}
	
	[self createRenderBuffer];
	[self createFrameBuffer];
	[self bindRenderBuffer];
	[self initializeRenderer];
	[self setTextureScaling];
	[self bindDisplayTexture];

	_displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawView:)];
	[_displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];

    return self;
}

- (BOOL)paused {
	return _displayLink.paused;
}

- (void)setPaused:(BOOL)value {
	_displayLink.paused = value;
}

- (void)layoutSubviews {
	self.contentScaleFactor = self.window.screen.scale;
	[self bindRenderBuffer];
	[self setTextureScaling];
	[self resizeView:CGSizeMake(_displaySize[0], _displaySize[1])];
}

- (void)bindDisplayTexture {
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _displaySize[0], _displaySize[1], GL_RGB, GL_UNSIGNED_SHORT_5_6_5, _pixels);
}

- (void)createRenderBuffer {
	// Create & bind the color buffer so that the caller can allocate its space.
    glGenRenderbuffers(1, &m_renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderbuffer);
}

- (void)createFrameBuffer {
	// Create the framebuffer object and attach the color buffer.
    glGenFramebuffers(1, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
	
	glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                              GL_COLOR_ATTACHMENT0,
                              GL_RENDERBUFFER,
                              m_renderbuffer);
}

- (void)bindRenderBuffer {
	CAEAGLLayer* eaglLayer = (CAEAGLLayer*) super.layer;
	[_glContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:eaglLayer];
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &_renderWidth);
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &_renderHeight);
	glViewport(0, 0, _renderWidth, _renderHeight);
}

- (void)setTextureScaling {
	
	float remW = _renderWidth / (float)_displaySize[0];
	remW = remW - (int)remW;
	float remH = _renderHeight / (float)_displaySize[1];
	remH = remH - (int)remH;
	
	if (remW || remH) {
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	} else {
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );		
	}
}

- (void)initializeRenderer {
	_noEffect = [NoEffect new];
	_texturedEffect = [TexturedCRTEffect new];
	_shaderEffect = _noEffect;
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glClearColor(0.f, 0.f, 0.f, 1);
	
	[_shaderEffect useProgram];

	GL_ERROR();
	
	// Initialize the projection matrix.
	CGSize size = CGSizeMake(_displaySize[0], _displaySize[1]);
	[self glOrthoLeft:0 right:size.width bottom:0 top:size.height near:-1 far:1];
	[self setModelView];
	
	// bind textures
	glGenTextures(1, &_texture);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _displaySize[0], _displaySize[1], 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, _pixels);
	
	// bind diplay vertices
	glGenBuffers(2, _displayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, _displayBuffers[0]);
	//[self resizeView:size];
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _displayBuffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
	
	// setup program attributes and uniforms
	
	// vertex shader
	glEnableVertexAttribArray(_shaderEffect.position);
	glEnableVertexAttribArray(_shaderEffect.textureCoord);
	
    GLsizei stride = sizeof(Vertex);
	const GLvoid *ofsCoords = offsetof(Vertex, Position);
	const GLvoid *ofsTexCoords = (GLvoid*)offsetof(Vertex, TexCoords);	
    glVertexAttribPointer(_shaderEffect.position, 2, GL_FLOAT, GL_FALSE, stride, ofsCoords);
	glVertexAttribPointer(_shaderEffect.textureCoord, 2, GL_FLOAT, GL_FALSE, stride, ofsTexCoords);	
		
	// fragment shader
	glUniform1i(_shaderEffect.displayTexture, 0);
}

- (void)resizeView:(CGSize)size  {
	Vertex Vertices[] = {
		{{0, size.height}, {0, 0}, {0, 0}},
		{{0, 0}, {0, 1}, {0, 1}},
		{{size.width, 0}, {1, 1}, {1, 1}},
		{{size.width, size.height}, {1, 0}, {1, 0}},
	};
	float scale = self.contentScaleFactor;
	CGSize texSize = CGSizeMake(_renderWidth / scale, _renderHeight / scale);
	[_shaderEffect updateCoords:Vertices count:sizeof(Vertices) viewSize:texSize scale:scale];
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

- (void)setDisplayEffect:(DisplayEffect)value {
	if (_displayEffect == value) return;
	
	_displayEffect = value;
	if (value == kDisplayEffectNone) {
		_shaderEffect = _noEffect;
		glDisableVertexAttribArray(_texturedEffect.fxTextureCoord);
	} else {
		_shaderEffect = _texturedEffect;
		[_texturedEffect setDisplayEffect:value];
	}
	
	[_shaderEffect useProgram];

	CGSize size = CGSizeMake(_displaySize[0], _displaySize[1]);
	[self glOrthoLeft:0 right:size.width bottom:0 top:size.height near:-1 far:1];
	[self setModelView];
	
	glEnableVertexAttribArray(_shaderEffect.position);
	glEnableVertexAttribArray(_shaderEffect.textureCoord);
	
    GLsizei stride = sizeof(Vertex);
	const GLvoid *ofsCoords = offsetof(Vertex, Position);
	const GLvoid *ofsTexCoords = (GLvoid*)offsetof(Vertex, TexCoords);	
    glVertexAttribPointer(_shaderEffect.position, 2, GL_FLOAT, GL_FALSE, stride, ofsCoords);
	glVertexAttribPointer(_shaderEffect.textureCoord, 2, GL_FLOAT, GL_FALSE, stride, ofsTexCoords);	
	
	// fragment shader
	glUniform1i(_shaderEffect.displayTexture, 0);
	
	[self resizeView:CGSizeMake(_displaySize[0], _displaySize[1])];
}

- (void)drawView {
	if (newFrame) {
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _displaySize[0], _displaySize[1], GL_RGB, GL_UNSIGNED_SHORT_5_6_5, _pixels);
		newFrame = NO;
	}
	
    glClear(GL_COLOR_BUFFER_BIT);
	GLsizei count = sizeof(Indices) / sizeof(Indices[0]);
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT, 0);
	
	[_glContext presentRenderbuffer:GL_RENDERBUFFER];
}

- (void)drawView:(CADisplayLink*)displayLink; {
	[self drawView];
}

- (void)glOrthoLeft:(float)left right:(float)right bottom:(float)bottom top:(float)top near:(float)near far:(float)far {
    float a = 2.0f / (right - left);
    float b = 2.0f / (top - bottom);
	float c = -2.0f / (far - near);
	
	float tx = -(right + left) / (right - left);
	float ty = -(top + bottom) / (top - bottom);
	float tz = -(far + near) / (far - near);
	
    float ortho[16] = {
        a, 0,  0, 0,
        0, b,  0, 0,
        0, 0,  c, 0,
        tx, ty,tz, 1
    };

    glUniformMatrix4fv(_shaderEffect.projection, 1, GL_FALSE, &ortho[0]);
}

- (void)setModelView {
	float identity[16] = {
        1, 0, 0, 0,
		0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
	
    glUniformMatrix4fv(_shaderEffect.modelView, 1, 0, &identity[0]);
}

- (void)dealloc {
	[_shaderEffect release];
	free(_pixels);
    [super dealloc];
}

@synthesize pixels=_pixels, displayEffect=_displayEffect;

@end
