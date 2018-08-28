#ifndef RENDERER_H
#define RENDERER_H

#include <stdlib.h>

#include "Component.h"
#include "../Asset/Mesh.h"

class Renderer : public Component{
public:
	Renderer();
	void setMesh(Mesh * mesh);
	Mesh * getMesh();
private:
	Mesh * mesh;
};

#endif