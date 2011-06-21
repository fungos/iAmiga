/*
 *  OGLTypes.h
 *  iAmiga
 *
 *  Created by Stuart Carnie on 1/19/11.
 *  Copyright 2011 Manomio LLC. All rights reserved.
 *
 */

typedef struct tagVertex {
    float Position[2];
	float TexCoords[2];
	float FxTexCoords[2];
} Vertex;

typedef enum tagDisplayEffect {
	kDisplayEffectNone,
	kDisplayEffectScanline50,
	kDisplayEffectScanline100,
	kDisplayEffectAperture1x2RB,
	kDisplayEffectAperture1x3RB,
	kDisplayEffectAperture2x4RB,
	kDisplayEffectAperture2x4BG,
} DisplayEffect;