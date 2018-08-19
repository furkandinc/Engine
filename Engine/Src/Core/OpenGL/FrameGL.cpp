#ifndef FRAMEGL_CPP
#define FRAMEGL_CPP

#include "FrameGL.h"
#include "..\includes\Angel.h"

typedef Angel::vec4 point4;

GLuint ModelView, Projection, program;
GLuint vPosition, vColor;
GLuint Vao, Buffer;

FrameGL * FrameGL::frameInstance = NULL;

FrameGL::FrameGL() {}

void debug() {
	GLenum errCode = glGetError();
	if (errCode != 0) {
		printf("Error %d\n", errCode);
	}
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

	debug();

	glClearColor(0, 0, 0, 1);

	glutDisplayFunc(displayFunc);
	glutIdleFunc(idleFunc);
	glutKeyboardFunc(keyboardDownFunc);
	glutKeyboardUpFunc(keyboardUpFunc);
	glutReshapeFunc(reshapeFunc);
	initBuffers();

}

void refreshPointers() {
	GLsizei stride = sizeof(PointGL);
	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(0));

	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(sizeof(vec4)));

	ModelView = glGetUniformLocation(program, "ModelView");
	Projection = glGetUniformLocation(program, "Projection");
}


void FrameGL::initBuffers() {
	bufferGL = new BufferGL();

	glEnable(GL_DEPTH_TEST);
	debug();
	program = InitShader("vshader1.glsl", "fshader1.glsl");
	glUseProgram(program);
	debug();
	printf("version: %s\n", glGetString(GL_VERSION));

	glGenVertexArrays(1, &Vao);
	glBindVertexArray(Vao);
	debug();
}

void FrameGL::render() {
	glutPostRedisplay();
	glutMainLoopEvent();
}

void FrameGL::displayFunc() {
	//printf("frame:display\n");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	point4 eye = point4(400, 300, 600, 1);
	point4 at = point4(400, 300, 0, 1);
	vec4 up(0, 1.0, 0, 0.0);
	mat4 mv = LookAt(eye, at, up);

	mat4 mo;
	BufferGL * buffer = frameInstance->bufferGL;

	PointGL * points = buffer->getPoints();
	int numPoints = buffer->getNumPoints();
	mat4 * mos = buffer->getMatrices();
	Integer * sizes = buffer->getSizes();
	int count = buffer->getCount();
	bool dirty = buffer->getDirty();

	/*DEBUG*/
	PointGL dbPoints[1000];
	int db;
	for (db = 0; db < numPoints && db < 1000; db++) {
		dbPoints[db] = points[db];
	}
	/*DEBUG*/

	if (dirty) {
		printf("displayfunc:dirty\n");
		glGenBuffers(1, &Buffer);
		glBindBuffer(GL_ARRAY_BUFFER, Buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(PointGL) * numPoints, points, GL_STATIC_DRAW);
		debug();
		buffer->setDirty(false);
		refreshPointers();
	}

	int i, offset = 0;
	for (i = 0; i < count; i++) {
		//printf("displayfunc:for%d\n", i);
		mo = mv * mos[i];
		glUniformMatrix4fv(ModelView, 1, GL_TRUE, mo);
		glDrawArrays(GL_TRIANGLES, offset, sizes[i].get());
		debug();
		offset += sizes[i].get();
	}

	glutSwapBuffers();
}

void FrameGL::addObject(Object * object) {
	bufferGL->add(object);
}

void FrameGL::idleFunc() {
	//TODO nothing?
}

void FrameGL::keyboardDownFunc(unsigned char key, int x, int y) {
	printf("framegl:keydownfunc key:%d\n", key);
	FrameGL * frame = getInstance();
	if (frame->keyHandler != nullptr) {
		frame->keyHandler->keyPressed(key);
	}
}

void FrameGL::keyboardUpFunc(unsigned char key, int x, int y) {
	printf("framegl:keyupfunc key:%d\n", key);
	FrameGL * frame = getInstance();
	if (frame->keyHandler != nullptr) {
		frame->keyHandler->keyReleased(key);
	}
}

void FrameGL::reshapeFunc(int w, int h) {
	printf("framegl:reshapefunc w:%d h%d\n", w, h);
	frameInstance->width = w;
	frameInstance->height = h;

	glViewport(0, 0, w, h);
	GLfloat aspect = GLfloat(w) / h;
	mat4 projection = Ortho(-w / 2, w / 2, -h / 2, h / 2, 1, 1000000);
	//3D mat4 projection = Perspective(90.0, aspect, 0.001, 10000.0);

	glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);
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

void FrameGL::setSize(int width, int height) {
	glutReshapeWindow(width, height);
}
#endif