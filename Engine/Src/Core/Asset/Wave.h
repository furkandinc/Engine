#pragma once

#include <SFML\Audio.hpp>

class Wave {
public:
	Wave();
	void readData(const char * filepath);
	sf::Sound * getData();
	bool isValid();

protected:
	sf::SoundBuffer buffer;
	sf::Sound sound;
	bool valid;
};