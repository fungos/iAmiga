//
//  VirtualKeyboard.m
//  iAmiga
//
//  Created by Stuart Carnie on 10/22/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import "VirtualKeyboard.h"
#import "CocoaUtility.h"
#import "KeyView.h"

@implementation VirtualKeyboard

typedef struct {
	uint8_t x, y, w, h;
} MMKeyRect;

typedef struct t_vkbd_rect {
	CGRect rect;
	unsigned char up,down,left,right;
	SDLKey key;
} t_vkbd_rect;

static t_vkbd_rect vkbd_rect[]=
{
	{{  8, 3, 6, 6 },89,10, 9, 1, SDLK_F1},	// 0
	{{ 18, 3, 6, 6 },89,12, 0, 2, SDLK_F2},	// 1
	{{ 28, 3, 6, 6 },90,14, 1, 3, SDLK_F3},	// 2
	{{ 38, 3, 6, 6 },90,15, 2, 4, SDLK_F4},	// 3
	{{ 48, 3, 6, 6 },90,17, 3, 5, SDLK_F5},	// 4
	{{ 58, 3, 6, 6 },90,18, 4, 6, SDLK_F6},	// 5 
	{{ 69, 3, 6, 6 },90,20, 5, 7, SDLK_F7},	// 6
	{{ 79, 3, 6, 6 },90,22, 6, 8, SDLK_F8},	// 7 
	{{ 90, 3, 6, 6 },90,23, 7, 9, SDLK_F9},	// 8 
	{{100, 3, 6, 6 },91,24, 8, 0, SDLK_F10},// 9 
	
	{{  2,12, 6, 6 }, 0,31,30,11, SDLK_ESCAPE}, // 10 
	{{  9,12, 6, 6 }, 0,32,10,12, SDLK_1},	// 11
	{{ 16,12, 6, 6 }, 1,33,11,13, SDLK_2},	// 12
	{{ 23,12, 6, 6 }, 2,34,12,14, SDLK_3},	// 13
	{{ 29,12, 6, 6 }, 2,35,13,15, SDLK_4},	// 14
	{{ 36,12, 6, 6 }, 3,36,14,16, SDLK_5},	// 15
	{{ 42,12, 6, 6 }, 4,37,15,17, SDLK_6},	// 16
	{{ 49,12, 6, 6 }, 4,38,16,18, SDLK_7},	// 17
	{{ 56,12, 6, 6 }, 5,39,17,19, SDLK_8},	// 18
	{{ 62,12, 6, 6 }, 5,40,18,20, SDLK_9},	// 19
	{{ 69,12, 6, 6 }, 6,41,19,21, SDLK_0},	// 20
	{{ 76,12, 6, 6 }, 7,42,20,22, SDLK_UNDERSCORE},	// 21
	{{ 83,12, 6, 6 }, 7,43,21,23, SDLK_EQUALS},	// 22
	{{ 90,12, 6, 6 }, 8,64,22,24, SDLK_BACKSLASH},	// 23
	{{ 97,12, 9, 6 }, 9,44,23,25, SDLK_BACKSPACE},// 24
	{{109,12,10, 6 },66,45,24,26, SDLK_PRINT},	// 25
	{{118,12,10, 6 },68,47,25,27, SDLK_PAUSE},	// 26
	{{131,12, 6, 6 },92,48,26,28, SDLK_LEFTPAREN},	// 27
	{{138,12, 6, 6 },92,49,27,29, SDLK_RIGHTPAREN},	// 28
	{{145,12, 6, 6 },93,50,28,30, SDLK_KP_DIVIDE},	// 29
	{{152,12, 6, 6 },88,51,29,10, SDLK_KP_MULTIPLY},	// 30
	
	{{  2,17,10, 6 },10,52,51,32, SDLK_TAB},	// 31 
	{{ 12,17, 6, 6 },11,53,31,33, SDLK_q},	// 32 
	{{ 19,17, 6, 6 },12,54,32,34, SDLK_w},	// 33
	{{ 25,17, 6, 6 },13,55,33,35, SDLK_e},	// 34
	{{ 32,17, 6, 6 },14,56,34,36, SDLK_r},	// 35
	{{ 39,17, 6, 6 },15,57,35,37, SDLK_t},	// 36
	{{ 46,17, 6, 6 },16,58,36,38, SDLK_y},	// 37
	{{ 52,17, 6, 6 },17,59,37,39, SDLK_u},	// 38
	{{ 59,17, 6, 6 },18,60,38,40, SDLK_i},	// 39
	{{ 65,17, 6, 6 },19,61,39,41, SDLK_o},	// 40
	{{ 72,17, 6, 6 },20,62,40,42, SDLK_p},	// 41
	{{ 79,17, 6, 6 },21,63,41,43, SDLK_LEFTBRACKET},	// 42
	{{ 86,17, 6, 6 },22,64,42,44, SDLK_RIGHTBRACKET},	// 43
	{{100,17, 6, 6 },24,65,43,45, SDLK_DELETE},	// 44
	{{109,17, 6, 6 },25,66,44,46, SDLK_INSERT},	// 45
	{{115,17, 6, 6 },25,67,45,47, SDLK_UP},	// 46
	{{122,17, 6, 6 },26,68,46,48, SDLK_HOME},	// 47
	{{131,17, 6, 6 },27,69,47,49, SDLK_KP7},	// 48
	{{138,17, 6, 6 },28,70,48,50, SDLK_KP8},	// 49
	{{145,17, 6, 6 },29,71,49,51, SDLK_KP9},	// 50
	{{152,17, 6, 6 },30,72,50,31, SDLK_KP_MINUS},	// 51
	
	{{  2,22,12, 6 },31,73,72,53, SDLK_CAPSLOCK},	// 52
	{{ 14,22, 6, 6 },32,74,52,54, SDLK_a},	// 53
	{{ 21,22, 6, 6 },33,75,53,55, SDLK_s},	// 54
	{{ 27,22, 6, 6 },34,76,54,56, SDLK_d},	// 55
	{{ 34,22, 6, 6 },35,77,55,57, SDLK_f},	// 56
	{{ 41,22, 6, 6 },36,78,56,58, SDLK_g},	// 57
	{{ 48,22, 6, 6 },37,79,57,59, SDLK_h},	// 58
	{{ 54,22, 6, 6 },38,80,58,60, SDLK_j},	// 59
	{{ 61,22, 6, 6 },39,81,59,61, SDLK_k},	// 60
	{{ 67,22, 6, 6 },40,82,60,62, SDLK_l},	// 61
	{{ 74,22, 6, 6 },41,83,61,63, SDLK_SEMICOLON},	// 62
	{{ 81,22, 6, 6 },42,84,62,64, SDLK_COLON},	// 63
	{{ 92,18, 7,10 },23,84,63,65, SDLK_RETURN},	// 64
	{{100,22, 6, 6 },44, 9,64,66, SDLK_QUOTE},	// 65
	{{109,22, 6, 6 },45,25,65,67, SDLK_LEFT},	// 66
	{{115,22, 6, 6 },46,25,66,68, SDLK_DOWN},	// 67
	{{122,22, 6, 6 },47,26,67,69, SDLK_RIGHT},	// 68
	{{131,22, 6, 6 },48,85,68,70, SDLK_KP4},	// 69
	{{138,22, 6, 6 },49,86,69,71, SDLK_KP5},	// 70
	{{145,22, 6, 6 },50,87,70,72, SDLK_KP6},	// 71
	{{152,22, 6, 6 },51,88, 71,52, SDLK_KP_PLUS},	// 72
	
	{{  2,28,15, 6 },52,89,88,74, SDLK_RSHIFT},	// 73
	{{ 17,28, 6, 6 },53,89,73,75, SDLK_z},	// 74
	{{ 24,28, 6, 6 },54,90,74,76, SDLK_x},	// 75
	{{ 30,28, 6, 6 },55,90,75,77, SDLK_c},	// 76
	{{ 37,28, 6, 6 },56,90,76,78, SDLK_v},	// 77
	{{ 44,28, 6, 6 },57,90,77,79, SDLK_b},	// 78
	{{ 51,28, 6, 6 },58,90,78,80, SDLK_n},	// 79
	{{ 57,28, 6, 6 },59,90,79,81, SDLK_m},	// 80
	{{ 64,28, 6, 6 },60,90,80,82, SDLK_COMMA},	// 81
	{{ 70,28, 6, 6 },61,90,81,83, SDLK_PERIOD},	// 82
	{{ 77,28, 6, 6 },62,91,82,84, SDLK_COLON},	// 83
	{{ 84,28,10, 6 },63,91,83,85, SDLK_LSHIFT},	// 84
	{{131,28, 6, 6 },69,92,84,86, SDLK_KP1},	// 85
	{{138,28, 6, 6 },70,92,85,87, SDLK_KP2},	// 86
	{{145,28, 6, 6 },71,93,86,88, SDLK_KP3},	// 87
	{{152,29, 6,10 },72,30,87,73, SDLK_KP_ENTER},	// 88
	
	{{ 10,34,10, 5 },73, 1,88,90, SDLK_LCTRL},	// 89
	{{ 20,34,60, 5 },78, 4,89,91, SDLK_SPACE},	// 90
	{{ 80,34,10, 5 },84, 8,90,92, SDLK_RCTRL},	// 91
	{{131,34,12, 5 },86,28,91,93, SDLK_KP0},	// 92
	{{145,34, 6, 5 },87,29,92,88, SDLK_KP_PERIOD},	// 93
};

int keys = sizeof(vkbd_rect) / sizeof(vkbd_rect[0]);

typedef struct t_foundKey {
	t_vkbd_rect* key;
	int i;
	int x,w;
} t_foundKey;

t_foundKey* findKey(CGPoint p) {
	int i =0;
	for (; i<keys; i++) {
		if (CGRectContainsPoint(vkbd_rect[i].rect, p)) {
			int x = 0, w = 0;
			for(int j = 0;j < i;j++)
			{
				switch(j)
				{
					case 25:
					case 26:
					case 89:
					case 91:
					case 92:
						x+= 41;
						break;
					case 31:			
					case 64:	
					case 73:
					case 84:
					case 88:
					case 90:
					case 98:
						x+= 49;
						break;
					default:
						x+= 32;
						break;
				}
			}
			
			switch(i)
			{
				case 25:
				case 26:
				case 89:
				case 91:
				case 92:
					w = 41;
					break;
				case 31:
				case 64:
				case 73:
				case 84:
				case 88:
				case 90:
				case 98:
					w = 49;
					break;
				default:
					w = 32;
					break;
			}
			
			static struct t_foundKey res;
			res.key = &vkbd_rect[i];
			res.i = i;
			res.x=x;
			res.w=w;
			
			return &res;
		}
	}
	
	return NULL;
}

- (id)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        UIImageView *keyboard = [UIImageView newViewFromImageResource:@"VKBD.PNG"];
		keyboard.alpha = 0.5;
		[self addSubview:keyboard];
		keyView = [[KeyView alloc] initWithFrame:CGRectMake(165, 0, 32, 32)];
		keyView.alpha = 0.5;
		[self addSubview:keyView];
    }
    return self;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
	tracking = YES;
	UITouch *touch = [touches anyObject];
	CGPoint loc = [touch locationInView:self];
	currentKey = findKey(loc);
	if (currentKey)
		[keyView showKey:currentKey->x width:currentKey->w key:currentKey->key->key];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {	
	UITouch *touch = [touches anyObject];
	CGPoint loc = [touch locationInView:self];
	if (currentKey && CGRectContainsPoint(currentKey->key->rect, loc))
		return;
	currentKey = findKey(loc);
	if (currentKey)
		[keyView showKey:currentKey->x width:currentKey->w key:currentKey->key->key];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
	tracking = NO;
}

- (void)dealloc {
	[keyView release];
    [super dealloc];
}


@end
