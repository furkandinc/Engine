#ifndef BUFFERGL_H
#define BUFFERGL_H

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
	int numPoints;
	PointGL * 
	int totalBufferSize;
	bool dirty;
	mat4 * matrices;
	int * sizes;
};

#endif