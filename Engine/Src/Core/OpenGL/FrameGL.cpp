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
	glutPassiveMotionFunc(passiveMouseFunc);
	glutReshapeFunc(reshapeFunc);
	// TODO glutMouseFunc(clickMouseFunc);
	initBuffers();

}

void FrameGL::initBuffers() {
	bufferGL = new BufferGL();

	program = InitShader("vshader1.glsl", "fshader1.glsl");
	glUseProgram(program);

	GLsizei stride = PointGL::size();

	glGenVertexArrays(1, &Vao);
	glBindVertexArray(Vao);

	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(0));

	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(4 * sizeof(float)));

	ModelView = glGetUniformLocation(program, "ModelView");
	Projection = glGetUniformLocation(program, "Projection");
}

void FrameGL::render() {
	glutPostRedisplay();
	glutMainLoopEvent();
}

void FrameGL::displayFunc() {
	//printf("frame:display\n");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	point4 eye = point4(400, 300, 100, 1);
	point4 at = point4(400, 300, 0, 1);
	vec4 up(0.0, 1.0, 0.0, 0.0);
	mat4 mv = LookAt(eye, at, up);
	glUniformMatrix4fv(ModelView, 1, GL_TRUE, mv);
	
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
		GLuint bfId;
		glGenBuffers(1, &bfId);
		glBindBuffer(GL_ARRAY_BUFFER, bfId);
		glBufferData(GL_ARRAY_BUFFER, PointGL::size() * numPoints, points, GL_STATIC_DRAW);
		buffer->setDirty(false);
	}

	int i, offset = 0;
	for (i = 0; i < count; i++) {
		//printf("displayfunc:for%d\n", i);
		mo = mv * mos[i];
		glUniformMatrix4fv(ModelView, 1, GL_TRUE, mo);
		glDrawArrays(GL_TRIANGLES, offset, sizes[i].get());
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
	mat4 projection = Ortho(0, w, 0, h, -1, 1);

	glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);
}

void FrameGL::passiveMouseFunc(int x, int y) {
	// printf("framegl::passiveMouseFunc x:%d y:%d\n", x, y);
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