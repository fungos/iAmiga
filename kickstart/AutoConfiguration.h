/*
 *  AutoConf.h
 *  iAmiga
 *
 *  Created by Stuart Carnie on 5/23/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#import "AmigaBase.h"
class Amiga;

class AutoConf : public AmigaBase {
public:
	AutoConf(Amiga& amiga);
	virtual void initialize();
	
private:
	Amiga& _amiga;
};