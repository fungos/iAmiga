/*
 Frodo, Commodore 64 emulator for the iPhone
 Copyright (C) 2007-2010 Stuart Carnie
 See gpl.txt for license information.
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

typedef struct {
	TouchStickDPadState dPadState;
	TouchStickDPadState joystickState;
} tagDPadState;

typedef struct {
	float min, max;
	tagDPadState state;
} tagDPadMap;

#define kDegrees 22.5
#define kEmptyStick { -1, 999, DPadCenter }

static tagDPadMap joydirs_8way[] = {
	{   0+kDegrees, 360-kDegrees, {DPadRight, DPadRight} },
	{  45+kDegrees,  45-kDegrees, {DPadDownRight, DPadDownRight} },
	{  90+kDegrees,  90-kDegrees, {DPadDown, DPadDown} },
	{ 135+kDegrees, 135-kDegrees, {DPadDownLeft, DPadDownLeft} },
	{ 180+kDegrees, 180-kDegrees, {DPadLeft, DPadLeft} },
	{ 225+kDegrees, 225-kDegrees, {DPadUpLeft, DPadUpLeft} },
	{ 270+kDegrees, 270-kDegrees, {DPadUp, DPadUp} },
	{ 315+kDegrees, 315-kDegrees, {DPadUpRight, DPadUpRight} },
	nil
};

#undef kDegrees
#define kDegrees 90

static tagDPadMap joydirs_2wayH[] = {
	{   0+kDegrees, 360-kDegrees, {DPadRight, DPadRight} },
	{ 180+kDegrees, 180-kDegrees, {DPadLeft, DPadLeft} },
	nil
};

static tagDPadMap joydirs_2wayV[] = {
	kEmptyStick,
	{  90+kDegrees,  90-kDegrees, {DPadDown, DPadDown} },
	{ 270+kDegrees, 270-kDegrees, {DPadUp, DPadUp} },
	nil
};

#undef kDegrees
#define kDegrees 45

static tagDPadMap joydirs_4way[] = {
	{   0+kDegrees, 360-kDegrees, {DPadRight, DPadRight} },
	{  90+kDegrees,  90-kDegrees, {DPadDown, DPadDown} },
	{ 180+kDegrees, 180-kDegrees, {DPadLeft, DPadLeft} },
	{ 270+kDegrees, 270-kDegrees, {DPadUp, DPadUp} },
	nil
};

static tagDPadMap joydirs_4way_X1[] = {
	kEmptyStick,
	{  45+kDegrees,  45-kDegrees, {DPadRight, DPadDownRight} },
	{ 135+kDegrees, 135-kDegrees, {DPadDown, DPadDownLeft} },
	{ 225+kDegrees, 225-kDegrees, {DPadLeft, DPadUpLeft} },
	{ 315+kDegrees, 315-kDegrees, {DPadUp, DPadUpRight} },
	nil
};

static tagDPadMap *dirs[] = {
	joydirs_8way,
	joydirs_4way,
	joydirs_2wayH,
	joydirs_2wayV,
	joydirs_4way_X1
};
