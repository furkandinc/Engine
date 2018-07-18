#ifndef FRAME_H
#define FRAME_H

#endif

class Frame {
public:
	Frame(char * title, int width, int height);
	int getWidth();
	int getHeight();
private:
	char * title;
	int width;
	int height;
};

Frame::Frame(char * title, int width, int height) {
	this->title = title;
	this->width = width;
	this->height = height;
}

int Frame::getWidth() {
	return this->width;
}

int Frame::getHeight() {
	return this->height;
}