#pragma once

#include <SFML\Audio.hpp>
#include "..\dllexp.h"
#include "..\Generable.h"

class DLLDIR Wave: public Generable {
public:
	Wave();
	void readData(const char * filepath);
	sf::Sound * getData();
	bool isValid();

	//Generable
	void * generate();
	int dispose();
protected:
	sf::SoundBuffer buffer;
	sf::Sound sound;
	bool valid;
};