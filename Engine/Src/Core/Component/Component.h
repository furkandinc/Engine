#pragma once

#include "../dllexp.h"

class Object;

class DLLDIR Component {
public:
	virtual ~Component() = default;
	Object * object;
};