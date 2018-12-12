#include "Material.h"

Material::Material() {
	setAmbientColor(vec4( 0.1, 0.1, 0.1, 1 ));
	setDiffuseColor(vec4( 0.6, 0.6, 0.6, 1 ));
	setSpecularColor(vec4(0.5, 0.5, 0.5, 1));
	setShininess(400);
}

void Material::setAmbientColor(vec4 color){
	ambientColor = color;
}

vec4 Material::getAmbientColor(){
	return ambientColor;
}

void Material::setDiffuseColor(vec4 color){
	diffuseColor = color;
}

vec4 Material::getDiffuseColor(){
	return diffuseColor;
}

void Material::setSpecularColor(vec4 color){
	specularColor = color;
}

vec4 Material::getSpecularColor(){
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
	m->ambientColor = vec4(ambientColor);
	m->diffuseColor = vec4(diffuseColor);
	m->specularColor = vec4(specularColor);
	m->shininess = shininess;
	if (textureGL != nullptr)
		m->textureGL = (TextureGL *)textureGL->generate();
	printf("diffuse %f %f %f %f\n", m->diffuseColor.x, m->diffuseColor.y, m->diffuseColor.z, m->diffuseColor.w);
	return (void *) m;
}

int Material::dispose() {
	if(textureGL != nullptr)
		textureGL->dispose();
	free(textureGL);

	return 0;
}