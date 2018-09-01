#ifndef RENDERER_CPP
#define RENDERER_CPP

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
#endif