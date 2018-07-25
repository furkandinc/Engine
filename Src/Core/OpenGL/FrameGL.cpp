#ifndef FRAMEGL_CPP
#define FRAMEGL_CPP

#include "FrameGL.h"
#include "..\includes\Angel.h"

typedef Angel::vec4 point4;

GLuint ModelView, Projection, ModelOBJ, program;
GLuint vPosition, vColor, VTextCoord, vNormal; // FIXME are theese necessary

FrameGL * FrameGL::frameInstance = NULL;

FrameGL::FrameGL() {

}

FrameGL * FrameGL::getInstance() {
	if (frameInstance == nullptr) {
		frameInstance = new FrameGL();
	}
	return frameInstance;
}

void FrameGL::init(int argc, char ** argv, const char * title, int width, int height) {
	this->width = width;
	this->height = height;

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow(title);
	glewExperimental = GL_TRUE;
	glewInit();

	glutDisplayFunc(displayFunc);
	glutIdleFunc(idleFunc);
	glutKeyboardFunc(keyboardDownFunc);
	glutKeyboardUpFunc(keyboardUpFunc);
	//glutPassiveMotionFunc(this->mouseFunc);
	glutReshapeFunc(reshapeFunc);

	initBuffers();
}

void FrameGL::displayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	point4 eye = point4(400, 300, 100, 1);
	point4 at = point4(400, 300, 0, 1);
	vec4 up(0.0, 1.0, 0.0, 0.0);
	mat4 mv = LookAt(eye, at, up);
	glUniformMatrix4fv(ModelView, 1, GL_TRUE, mv);
	
	// mat4 mo;
	// ObjectGL ** objects bufferGL->
	glutSwapBuffers();
}

void FrameGL::idleFunc() {
	//TODO
}

void FrameGL::keyboardDownFunc(unsigned char key, int x, int y) {
	FrameGL * frame = getInstance();
	if (frame->keyHandler != nullptr) {
		frame->keyHandler->keyPressed(key);
	}
}

void FrameGL::keyboardUpFunc(unsigned char key, int x, int y) {
	FrameGL * frame = getInstance();
	if (frame->keyHandler != nullptr) {
		frame->keyHandler->keyReleased(key);
	}
}

void FrameGL::reshapeFunc(int w, int h) {
	//TODO
}

int FrameGL::getWidth() {
	return this->width;
}

int FrameGL::getHeight() {
	return this->height;
}

void FrameGL::setKeyHandler(KeyHandler * keyHandler) {
	this->keyHandler = keyHandler;
}
#endif