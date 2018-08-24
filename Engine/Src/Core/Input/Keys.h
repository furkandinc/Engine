#ifndef KEYS_H
#define KEYS_H

#include "../includes/Angel.h"

class Keys {
public:
	const static enum keys : int {
		//Ascii chars
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		KEY_NUM_0,
		KEY_NUM_1,
		KEY_NUM_2,
		KEY_NUM_3,
		KEY_NUM_4,
		KEY_NUM_5,
		KEY_NUM_6,
		KEY_NUM_7,
		KEY_NUM_8,
		KEY_NUM_9,
		KEY_SPACE,
		KEY_SINGLE_QUOTE,
		KEY_DOUBLE_QUOTE,
		KEY_TAB,
		KEY_BACKSPACE,
		KEY_ASTERIKS,
		KEY_DASH,
		KEY_PLUS,
		KEY_ESCAPE,
		KEY_SLASH,
		KEY_BACKSLASH,
		KEY_PERIOD,
		KEY_COMMA,
		KEY_COLON,
		KEY_SEMICOLON,
		KEY_ENTER,

		//Special
		KEY_CTRL_L,
		KEY_CTRL_R,
		KEY_SHIFT_L,
		KEY_SHIFT_R,
		KEY_ALT_L,
		KEY_ALT_R,
		KEY_DELETE,
		KEY_END,
		KEY_HOME,
		KEY_INSERT,
		KEY_PAGE_UP,
		KEY_PAGE_DOWN,
		KEY_NUM_LOCK,
		KEY_F1,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,
		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT,
		COUNT = KEY_RIGHT + 1 };

	const static enum status : int { STATUS_PRESSED, STATUS_PRESS, STATUS_RELEASED, STATUS_IDLE };

	const static int toKeys(unsigned int keyCode) {
		switch (keyCode) {
		case 'A': case 'a': return KEY_A;
		case 'B': case 'b': return KEY_B;
		case 'C': case 'c': return KEY_C;
		case 'D': case 'd': return KEY_D;
		case 'E': case 'e': return KEY_E;
		case 'F': case 'f': return KEY_F;
		case 'G': case 'g': return KEY_G;
		case 'H': case 'h': return KEY_H;
		case 'I': case 'i': return KEY_I;
		case 'J': case 'j': return KEY_J;
		case 'K': case 'k': return KEY_K;
		case 'L': case 'l': return KEY_L;
		case 'M': case 'm': return KEY_M;
		case 'N': case 'n': return KEY_N;
		case 'O': case 'o': return KEY_O;
		case 'P': case 'p': return KEY_P;
		case 'Q': case 'q': return KEY_Q;
		case 'R': case 'r': return KEY_R;
		case 'S': case 's': return KEY_S;
		case 'T': case 't': return KEY_T;
		case 'U': case 'u': return KEY_U;
		case 'V': case 'v': return KEY_V;
		case 'W': case 'w': return KEY_W;
		case 'X': case 'x': return KEY_X;
		case 'Y': case 'y': return KEY_Y;
		case 'Z': case 'z': return KEY_Z;
		case '0': return KEY_NUM_0;
		case '1': return KEY_NUM_1;
		case '2': return KEY_NUM_2;
		case '3': return KEY_NUM_3;
		case '4': return KEY_NUM_4;
		case '5': return KEY_NUM_5;
		case '6': return KEY_NUM_6;
		case '7': return KEY_NUM_7;
		case '8': return KEY_NUM_8;
		case '9': return KEY_NUM_9;
		case ' ': return KEY_SPACE;
		case '\'': return KEY_SINGLE_QUOTE;
		case '\"': return KEY_DOUBLE_QUOTE;
		case '\t': return KEY_TAB;
		case 8: return KEY_BACKSPACE;
		case '*': return KEY_ASTERIKS;
		case '-': return KEY_DASH; 
		case '+': return KEY_PLUS;
		case 27: return KEY_ESCAPE;
		case '/': return KEY_SLASH;
		case '\\': return KEY_BACKSLASH;
		case '.': return KEY_PERIOD;
		case ',': return KEY_COMMA;
		case ':': return KEY_COLON;
		case ';': return KEY_SEMICOLON;
		case '\n': return KEY_ENTER;
		}

		return -1;
	};

	const static int specialToKeys(int keyCode) {
		switch (keyCode) {
		case GLUT_KEY_CTRL_L: return KEY_CTRL_L;
		case GLUT_KEY_CTRL_R: return KEY_CTRL_R;
		case GLUT_KEY_SHIFT_L: return KEY_SHIFT_L;
		case GLUT_KEY_SHIFT_R: return KEY_SHIFT_R;
		case GLUT_KEY_UP: return KEY_UP;
		case GLUT_KEY_DOWN: return KEY_DOWN;
		case GLUT_KEY_LEFT: return KEY_LEFT;
		case GLUT_KEY_RIGHT: return KEY_RIGHT;
		case GLUT_KEY_ALT_L: return KEY_ALT_L;
		case GLUT_KEY_ALT_R: return KEY_ALT_R;
		case GLUT_KEY_DELETE: return KEY_DELETE;
		case GLUT_KEY_END: return KEY_END;
		case GLUT_KEY_HOME: return KEY_HOME;
		case GLUT_KEY_INSERT: return KEY_INSERT;
		case GLUT_KEY_PAGE_UP: return KEY_PAGE_UP;
		case GLUT_KEY_PAGE_DOWN: return KEY_PAGE_DOWN;
		case GLUT_KEY_NUM_LOCK: return KEY_NUM_LOCK;
		case GLUT_KEY_F1: return KEY_F1;
		case GLUT_KEY_F2: return KEY_F2;
		case GLUT_KEY_F3: return KEY_F3;
		case GLUT_KEY_F4: return KEY_F4;
		case GLUT_KEY_F5: return KEY_F5;
		case GLUT_KEY_F6: return KEY_F6;
		case GLUT_KEY_F7: return KEY_F7;
		case GLUT_KEY_F8: return KEY_F8;
		case GLUT_KEY_F9: return KEY_F9;
		case GLUT_KEY_F10: return KEY_F10;
		case GLUT_KEY_F11: return KEY_F11;
		case GLUT_KEY_F12: return KEY_F12;
		}

		return -1;
	}
};
#endif