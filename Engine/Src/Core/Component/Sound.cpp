#include "Sound.h"

Sound::Sound() {
	wave = nullptr;
}

void Sound::setWave(Wave * wave) {
	this->wave = wave;
}

void Sound::play() {
	if (!isValid())
		return;


	printf("Hitt\n");
	wave->getData()->play();
}

void Sound::pause() {
	if (!isValid())
		return;

	wave->getData()->pause();
}

bool Sound::isPlaying() {
	if (!isValid())
		return false;

	return wave->getData()->getStatus() == sf::Sound::Playing;
}

void Sound::setVolume(int volume) {
	if (volume > 100)
		this->volume = 100;
	else if (volume < 0)
		this->volume = 0;
	else
		this->volume = volume;

	if (!isValid())
		return;

	wave->getData()->setVolume(this->volume);
}

int Sound::getVolume() {
	return volume;
}

void Sound::setLoop(bool loop) {
	if (!isValid())
		return;

	wave->getData()->setLoop(loop);
}

bool Sound::getLoop() {
	if (!isValid())
		return false;

	wave->getData()->getLoop();
}

void Sound::set3D(bool is3D) {
	if (!isValid())
		return;
	//TODO
}

bool Sound::get3D() {
	//TODO
	return false;
}

bool inline Sound::isValid() {
	if (wave == nullptr)
		return false;
	if (!wave->isValid())
		return false;
	return true;
}