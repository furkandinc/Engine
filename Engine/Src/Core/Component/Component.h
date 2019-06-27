#pragma once

#include "../dllexp.h"
#include "../Generable.h"

class Object;

class DLLDIR Component: public Generable {
public:
	virtual ~Component() = default;
	Object * object;

	//Generable
	virtual void * generate() = 0;
	virtual int dispose() = 0;
};