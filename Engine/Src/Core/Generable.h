#pragma once

#include "dllexp.h"

class DLLDIR Generable {
public:
	virtual void * generate() = 0;
	virtual int dispose() = 0;
};