#pragma once

#include "Component.h"
#include "..\Asset\Wave.h"

class DLLDIR Sound : public Component {
public:
	Sound();
	
	void setWave(Wave * wave);
	void play();
	void pause();
	bool isPlaying();
	
	void setVolume(int volume);
	int getVolume();

	void setLoop(bool isLoop);
	bool getLoop();

	void set3D(bool is3D);
	bool get3D();

	//Generable
	void * generate();
	int dispose();

protected:
	Wave * wave;
	int volume;

private:
	bool isValid();
};