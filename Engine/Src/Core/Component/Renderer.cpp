#include <stdlib.h>
#include <stdio.h>
#include "Renderer.h"

Renderer::Renderer() {
	
}

void Renderer::setMesh(Mesh * mesh) {
	this->mesh = mesh;
}

Mesh * Renderer::getMesh() {
	return this->mesh;
}

void Renderer::setMaterial(Material * material){
	this->material = material;
}

Material * Renderer::getMaterial() {
	return material;
}

void * Renderer::generate() {
	Renderer * r = new Renderer();
	if(mesh != nullptr)
		r->mesh = (Mesh *)mesh->generate();
	if(material != nullptr)
		r->material = (Material *)material->generate();

	return r;
}

int Renderer::dispose() {
	if (mesh != nullptr)
		mesh->dispose();
	if (material != nullptr)
		material->dispose();
	free(mesh);
	free(material);

	return 0;
}