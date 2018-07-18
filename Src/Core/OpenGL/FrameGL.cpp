#ifndef FRAMEGL_H
#define FRAMEGL_H

#endif

class FrameGL {
public:
	FrameGL(int argc, char ** argv, char * title, int width, int height);
	int getWidth();
	int getHeight();
private:
	char * title;
	int width;
	int height;
};

FrameGL::FrameGL(int argc, char ** argv, char * title, int width, int height) {
	this->title = title;
	this->width = width;
	this->height = height;
}

int FrameGL::getWidth() {
	return this->width;
}

int FrameGL::getHeight() {
	return this->height;
}