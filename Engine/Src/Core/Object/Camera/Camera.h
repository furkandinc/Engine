#pragma once

#include "../Object.h"
#include "../../dllexp.h"
#include "../../includes/Angel.h"

class DLLDIR Camera: public Object {
public:
	virtual mat4 getProjection() = 0;
};