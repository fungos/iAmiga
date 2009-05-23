/*
 *  Graphics.h
 *  iAmiga
 *
 *  Created by Stuart Carnie on 5/23/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#import "AmigaBase.h"

class Amiga;

class Graphics : public AmigaBase {
public:
	Graphics(Amiga& amiga);
	
	virtual void initialize();
	
private:
	Amiga& _amiga;
};