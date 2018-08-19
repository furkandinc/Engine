#ifndef OBJECTGL_H
#define OBJECTGL_H

#include "PointGL.h"

class ObjectGL {
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

#endif