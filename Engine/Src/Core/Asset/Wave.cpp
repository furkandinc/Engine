#include "Wave.h"

Wave::Wave() {
	valid = false;
}

void Wave::readData(const char * filepath) {
	if (buffer.loadFromFile(filepath)) {
		valid = true;
	}
	else {
		valid = false;
	}

	sound.setBuffer(buffer);
}

sf::Sound * Wave::getData() {
	return &sound;
}

bool Wave::isValid() {
	return valid;
}