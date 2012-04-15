/*
 *  esUtil.h
 *  OGLDisplay
 *
 *  Created by Stuart Carnie on 12/29/10.
 *  Copyright 2010 Manomio LLC. All rights reserved.
 *
 */

#if __cplusplus
extern "C" {
#endif
	
	enum tagRETexturePixelFormat {
		kRETexturePixelFormat_RGBA8888,
		kRETexturePixelFormat_RGBA4444,
		kRETexturePixelFormat_RGB565,
		kRETexturePixelFormat_RGB5A1,
	};
	
	typedef enum tagRETexturePixelFormat kRETexturePixelFormat;
	
	char*  esLoadPNG ( const char *fileName, kRETexturePixelFormat desiredFormat, int *width, int *height );

#if __cplusplus
}
#endif