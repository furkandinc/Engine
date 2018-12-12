#pragma once

#include "PointGL.h"
#include "../dllexp.h"
#include "../Generable.h"

class DLLDIR ObjectGL: public Generable {
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

	void * generate();
	int dispose();
private:
	int id;
	bool dirty, idStat;
	PointGL * points;
	int size;
};