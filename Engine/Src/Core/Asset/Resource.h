#pragma once

#include "../dllexp.h"

#define ResourceType int

#define NULLTYPE -1
#define BMPTYPE 100
#define OBJTYPE 101
#define PNGTYPE 102

typedef struct DLLDIR RESOURCE {
	int resourceid = -1;
	ResourceType resourcetype = NULLTYPE;
	size_t unitsize;
	int size;
	void * data;

	//additional
	int argc = 0;
	void * argv;
} Resource;