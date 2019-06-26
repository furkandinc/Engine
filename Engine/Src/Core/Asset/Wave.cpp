#include "Wave.h"

Wave::Wave(Resource resource) {
	sound = new sf::Sound();
	sf::SoundBuffer * soundBuffer = (sf::SoundBuffer *) resource.data;
	sound->setBuffer(*(soundBuffer));
	this->resource = resource;
}

sf::Sound * Wave::getData() {
	return sound;
}

void * Wave::generate() {
	Wave * wave = new Wave(resource);
	return (void *)wave;
}

int Wave::dispose() {
	free(sound);
	return 0;
}