static const char* CRT2FragmentShader = STRINGIFY(

varying mediump vec2 TextureCoordOut;
varying mediump vec2 FxTextureCoordOut;

uniform sampler2D DisplayTexture;
uniform sampler2D EffectTexture;

void main(void)
{
	lowp vec4 displayColor = texture2D(DisplayTexture, TextureCoordOut);
	mediump vec4 effectCol = texture2D(EffectTexture, FxTextureCoordOut);
	
	gl_FragColor = displayColor * effectCol;
}
);
