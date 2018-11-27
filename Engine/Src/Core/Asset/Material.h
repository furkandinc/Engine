#pragma once

#include "../dllexp.h"
#include "../OpenGL/TextureGL.h"
#include "../includes/Angel.h"

class DLLDIR Material {
public:
	Material();
	void setAmbientColor(vec4 color);
	vec4 getAmbientColor();
	void setDiffuseColor(vec4 color);
	vec4 getDiffuseColor();
	void setSpecularColor(vec4 color);
	vec4 getSpecularColor();
	void setShininess(float shininess);
	float getShininess();
	void setColorTexture(TextureGL * textureGL);
	TextureGL * getColorTexture();
private:
	vec4 ambientColor;
	vec4 diffuseColor;
	vec4 specularColor;
	float shininess;
	TextureGL * textureGL;
};