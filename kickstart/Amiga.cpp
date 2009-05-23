/*
 *  Amiga.cpp
 *  iAmiga
 *
 *  Created by Stuart Carnie on 5/23/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Amiga.h"
#include "Prefs.h"
#import "SDL.h"
#import "Graphics.h"
#import "AutoConfiguration.h"

Amiga::Amiga()
:_graphics(new Graphics(*this)),
 _autoConf(new AutoConf(*this))
{}

Amiga::~Amiga() {
	delete _graphics;
}

void Amiga::run() {
	initialize();
	
	SDL_Init(0);
}

void Amiga::initialize() {
	_graphics->initialize();
}