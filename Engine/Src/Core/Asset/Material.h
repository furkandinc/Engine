#pragma once

#include "../dllexp.h"
#include "../OpenGL/TextureGL.h"
#include "../includes/Angel.h"
#include "../Generable.h"
class DLLDIR Material: public Generable {
public:
	Material();
	void setAmbientColor(vec3 color);
	vec3 getAmbientColor();
	void setDiffuseColor(vec3 color);
	vec3 getDiffuseColor();
	void setSpecularColor(vec3 color);
	vec3 getSpecularColor();
	void setShininess(float shininess);
	float getShininess();
	void setColorTexture(TextureGL * textureGL);
	TextureGL * getColorTexture();

	//Generable
	void * generate();
	int dispose();

private:
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
	float shininess;
	TextureGL * textureGL;
};