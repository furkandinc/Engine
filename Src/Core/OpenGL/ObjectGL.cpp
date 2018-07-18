#ifndef OBJECTGL_H
#define OBJECTGL_H

#include "PointGL.cpp"

#endif

class ObjectGL{
public:
	ObjectGL() {
		this->hasId = false;
	}

	void setId(int id) {
		this->id = id;
	}

	bool hasId() {
		return hasId;
	}

	int getId() {
		return this->id;
	}

	PointGL ** getPoints() {
		return points;
	}

	void setDirty(bool dirty) {
		this->dirty = dirty;
	}

	bool isDirty() {
		return this->dirty;
	}

	int getPointsSize() {
		return this->size;
	}

	void setPoints(PointGL ** points, int size) {
		this->points = points;
		this->size = size;
	}
private:
	int id;
	bool dirty, hasId;
	PointGL ** points;
	int size;
};