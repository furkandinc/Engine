#pragma once

#include "PointGL.h"
#include "../dllexp.h"

class DLLDIR ObjectGL {
public:
	ObjectGL();

	void setId(int id);

	bool hasId();

	int getId();

	PointGL * getPoints();

	void setDirty(bool dirty);

	bool isDirty();

	int getPointsSize();

	void setPoints(PointGL * points, int size);
private:
	int id;
	bool dirty, idStat;
	PointGL * points;
	int size;
};