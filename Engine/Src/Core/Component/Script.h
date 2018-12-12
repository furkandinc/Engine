#pragma once
#include "../dllexp.h"
#include "Component.h"
#include "../Object/Object.h"
#include "../Generable.h"

class DLLDIR Script: public Component {
public:
	virtual void onStart(void) = 0;
	virtual void onUpdate(void) = 0;
	//Generable
	virtual void * generate() = 0;
	virtual int dispose() = 0;
};