#ifndef BUFFERGL_H
#define BUFFERGL_H

#include <vector>

#include "PointGL.h"
#include "ObjectGL.h"
#include "../Object/Object.h"
#include "../includes/Angel.h"
#include "../Util/ArrayList.h"
#include "../Util/Integer.h"
#include "../Component/Transform.h"
#include "../Component/Mesh.h"

class BufferGL {
public:
	BufferGL();
	PointGL * getPoints();
	int getNumPoints();
	mat4 * getMatrices();
	Integer * getSizes();
	int getCount();
	bool getDirty();
	void setDirty(bool dirty);
	void add(Object * object);

private:

	ArrayList<PointGL> * points;
	ArrayList<mat4> * matrices;
	ArrayList<Integer> * sizes;
	ArrayList<Integer> * ids;

	int count;

	bool dirty;
	int lastGeneratedID;

	int generateID();
	mat4 generateMatris(Transform * transform);

	int indexOfId(int id);
	void addToArray(PointGL * points, int size);
};
#endif
