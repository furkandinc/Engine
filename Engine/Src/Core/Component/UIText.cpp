#include "UIText.h"

UIText::UIText() {
	this->text = nullptr;
}

void UIText::setText(const char * text) {
	this->text = text;
}

const char * UIText::getText() {
	return text;
}

void UIText::setMaterial(Material * material) {
	this->material = material;
}

Material * UIText::getMaterial() {
	return material;
}

void * UIText::generate() {
	UIText * r = new UIText();
	if (material != nullptr)
		r->material = (Material *)material->generate();
	r->text = text;
	return r;
}

int UIText::dispose() {
	if (material != nullptr)
		material->dispose();
	free(material);

	return 0;
}