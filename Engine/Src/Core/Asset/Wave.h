#pragma once

#include <SFML\Audio.hpp>
#include "../dllexp.h"

class DLLDIR Wave {
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