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
