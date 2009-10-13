/*
 *  combined_modules.cpp
 *  iAmiga
 *
 *  Created by Stuart Carnie on 9/26/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

// combine the files to avoid multiple loads when accessing global variables

#include "custom.cpp"

#include "drawing.cpp"

#include "disk.cpp"

#include "m68k/m68k_cmn_intrf.cpp"

#include "sound_iphone.cpp"

#include "audio.cpp"