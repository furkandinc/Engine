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
#include "../Component/Renderer.h"

class BufferGL {
public:
	BufferGL();
	PointGL * getPoints();
	int getNumPoints();
	mat4 * getMatrices();
	Integer * getSizes();
	Integer * getIDs();
	Material * getMaterials();
	int getCount();
	bool getDirty();
	void setDirty(bool dirty);
	void add(Object * object);
	void remove(Object * object);

private:

	ArrayList<PointGL> * points;
	ArrayList<mat4> * matrices;
	ArrayList<Integer> * sizes;
	ArrayList<Integer> * ids;
	ArrayList<Material> * materials;
	int count;

	bool dirty;
	int lastGeneratedID;

	int generateID();

	int indexOfId(int id);
	void addToArray(PointGL * points, int size);
};
#endif
