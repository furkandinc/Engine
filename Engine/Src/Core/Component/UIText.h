#pragma once
#include "Component.h"
#include "../Asset/Material.h"

class DLLDIR UIText : public Component {
public:
	UIText();
	void setMaterial(Material * material);
	Material * getMaterial();
	void setText(const char * str);
	const char * getText();

	//Generable
	void * generate();
	int dispose();
private:
	const char * text;
	Material * material;
};