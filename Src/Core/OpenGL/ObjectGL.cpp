#ifndef OBJECTGL_H
#define OBJECTGL_H

#include "PointGL.cpp"

class ObjectGL {
public:
	ObjectGL() {
		this->idStat = false;
	}

	void setId(int id) {
		this->id = id;
		this->idStat;
	}

	bool hasId() {
		return idStat;
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
	bool dirty, idStat;
	PointGL ** points;
	int size;
};

#endif

