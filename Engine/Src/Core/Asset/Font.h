#pragma once

#include "Resource.h"

typedef struct FONTCHAR {
	int charid = -1;
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
	int xoffset = 0;
	int yoffset = 0;
} FontChar;

typedef struct FONT {
	const char * fontname = "";
	int imagewidth = 0;
	int imageheight = 0;
	int cellwidth = 0;
	int cellheight = 0;
	int size;
	FontChar * chars;
	Resource charuv;
	Resource charobj;
} Font;