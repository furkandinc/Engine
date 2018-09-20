#pragma once

#include <Asset\Wave.h>
#include <Component\Component.h>

class Sound : public Component {
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

protected:
	Wave * wave;
	int volume;

private:
	bool isValid();
};