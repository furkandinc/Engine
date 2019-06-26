#pragma once

#include <SFML\Audio.hpp>
#include "..\dllexp.h"
#include "..\Generable.h"
#include "Resource.h"

class DLLDIR Wave: public Generable {
public:
	Wave(Resource resource);
	sf::Sound * getData();

	//Generable
	void * generate();
	int dispose();
protected:
	sf::Sound * sound;
	Resource resource;
};