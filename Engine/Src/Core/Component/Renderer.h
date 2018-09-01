#ifndef RENDERER_H
#define RENDERER_H

#include <stdlib.h>

#include "Component.h"
#include "../Asset/Mesh.h"
#include "../Asset/Material.h"

class Renderer : public Component{
public:
	Renderer();
	void setMesh(Mesh * mesh);
	Mesh * getMesh();
	void setMaterial(Material * material);
	Material * getMaterial();
private:
	Mesh * mesh;
	Material * material;
};

#endif