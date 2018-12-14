#pragma once

#define ResourceType int

#define NULLTYPE -1
#define BMPTYPE 100
#define OBJTYPE 101

typedef struct RESOURCE {
	int resourceid = -1;
	ResourceType resourcetype = NULLTYPE;
	size_t unitsize;
	int size;
	void * data;

	//additional
	int argc = 0;
	void * argv;
} Resource;