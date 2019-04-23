#include "Material.h"

Material::Material() {
	textureGL = nullptr;
	setAmbientColor(vec3( 0.1, 0.1, 0.1));
	setDiffuseColor(vec3( 0.6, 0.6, 0.6));
	setSpecularColor(vec3(0.5, 0.5, 0.5));
	setShininess(400);
}

void Material::setAmbientColor(vec3 color){
	ambientColor = color;
}

vec3 Material::getAmbientColor(){
	return ambientColor;
}

void Material::setDiffuseColor(vec3 color){
	diffuseColor = color;
}

vec3 Material::getDiffuseColor(){
	return diffuseColor;
}

void Material::setSpecularColor(vec3 color){
	specularColor = color;
}

vec3 Material::getSpecularColor(){
	return specularColor;
}

void Material::setShininess(float shininess){
	this->shininess = shininess;
}

float Material::getShininess() {
	return shininess;
}

void Material::setColorTexture(TextureGL * textureGL) {
	this->textureGL = textureGL;
}

TextureGL * Material::getColorTexture() {
	return textureGL;
}

void * Material::generate() {
	Material * m = new Material();
	m->ambientColor = vec3(ambientColor);
	m->diffuseColor = vec3(diffuseColor);
	m->specularColor = vec3(specularColor);
	m->shininess = shininess;
	if (textureGL != nullptr)
		m->textureGL = (TextureGL *)textureGL->generate();
	return (void *) m;
}

int Material::dispose() {
	if(textureGL != nullptr)
		textureGL->dispose();
	free(textureGL);

	return 0;
}