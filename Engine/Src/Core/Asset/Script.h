#pragma once
#include "../dllexp.h"
#include "../Object/Object.h"

class DLLDIR Script {
public:
	virtual void onStart(void) = 0;
	virtual void onUpdate(void) = 0;

	Object * object;
};