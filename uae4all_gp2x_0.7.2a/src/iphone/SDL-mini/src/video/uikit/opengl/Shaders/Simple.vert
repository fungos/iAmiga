static const char* SimpleVertexShader = STRINGIFY(

attribute vec4 Position;
attribute vec2 TextureCoord;

varying vec2 TextureCoordOut;

#ifdef USE_GL_REPEAT
attribute vec2 FxTextureCoord;
varying vec2 FxTextureCoordOut;
#endif

uniform mat4 Projection;
uniform mat4 Modelview;

void main(void)
{
    gl_Position = Projection * Modelview * Position;
	TextureCoordOut = TextureCoord;
#ifdef USE_GL_REPEAT
	FxTextureCoordOut = FxTextureCoord;
#endif
}
);
