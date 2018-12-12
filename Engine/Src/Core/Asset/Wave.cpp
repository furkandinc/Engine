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

void * Wave::generate() {
	Wave * wave = new Wave();
	//wave->buffer.loadFromSamples(buffer.getSamples(), buffer.getSampleCount(), buffer.getChannelCount(), buffer.getSampleRate());
	wave->valid = valid;
	if (valid) {
		wave->buffer = this->buffer;
		wave->sound.setBuffer(wave->buffer);
	}
	
	return (void *)wave;
}

int Wave::dispose() {
	/*/
	delete &buffer;
	delete &sound;
	*/
	return 0;
}