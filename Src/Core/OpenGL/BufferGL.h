#ifndef BUFFERGL_H
#define BUFFERGL_H

#include <vector>

#include "PointGL.h"
#include "../Object/Object.h"
#include "../includes/Angel.h"

class BufferGL {
public:
	BufferGL();
	PointGL * getPoints();
	int getNumPoints();
	mat4 * getMatrices();
	int * getSizes();
	int getCount();
	bool getDirty();
	void setDirty(bool dirty);
	void add(Object * object);

private:
	
	std::vector<PointGL> points;

	std::vector<mat4> matrices;
	std::vector<int> sizes;
	std::vector<int> ids;
	int count;

	bool dirty;
	int lastGeneratedID;

	int generateID();
	mat4 generateMatris(Transform * transform);

	int indexOfId(int id);
	void addToArray(PointGL * points, int size);
};
#endif
