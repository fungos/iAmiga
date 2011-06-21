const char* SimpleFragmentShader = STRINGIFY(

varying mediump vec2 TextureCoordOut;
uniform sampler2D DisplayTexture;

void main(void)
{
	gl_FragColor = texture2D(DisplayTexture, TextureCoordOut);
}
);
