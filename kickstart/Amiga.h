/*
 *  Amiga.h
 *  iAmiga
 *
 *  Created by Stuart Carnie on 5/23/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#import "Prefs.h"
#import "AmigaBase.h"

class Graphics;
class AutoConf;

class Amiga : protected AmigaBase {
public:
	Amiga();
	~Amiga();
	
	void run();
	Prefs& prefs() { return _prefs; }
	
protected:
	virtual void initialize();
	
private:
	Prefs		_prefs;
	Graphics*	_graphics;
	AutoConf*	_autoConf;
};