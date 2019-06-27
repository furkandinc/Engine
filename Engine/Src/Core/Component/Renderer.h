#pragma once
#include <stdlib.h>

#include "Component.h"
#include "../Asset/Mesh.h"
#include "../Asset/Material.h"

class DLLDIR Renderer : public Component {
public:
	Renderer();
	void setMesh(Mesh * mesh);
	Mesh * getMesh();
	void setMaterial(Material * material);
	Material * getMaterial();

	//Generable
	void * generate();
	int dispose();
private:
	Mesh * mesh;
	Material * material;
};