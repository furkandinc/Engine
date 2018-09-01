#ifndef FRAMEGL_CPP
#define FRAMEGL_CPP

#define HASTEXTURE 1
#define NOTEXTURE -1

#include "FrameGL.h"
#include "..\includes\Angel.h"

typedef Angel::vec4 point4;

GLuint ModelView, Projection, program;
GLuint vPosition, vUv, vNormal;
GLuint Vao, Buffer;
GLuint AmbientProduct, DiffuseProduct, SpecularProduct;
GLuint Shininess;
GLuint LightPosition;
GLuint TextureMode;
GLuint TextureID;

vec4 light_ambient(1, 1, 1, 1.0);
vec4 light_diffuse(1.0, 1.0, 1.0, 1.0);
vec4 light_specular(1.0, 1.0, 1.0, 1.0);

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
	glutSpecialFunc(specialDownFunc);
	glutSpecialUpFunc(specialUpFunc);
	glutReshapeFunc(reshapeFunc);
	initBuffers();

}

void refreshPointers() {
	GLsizei stride = sizeof(PointGL);
	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(0));
	debug();

	vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(sizeof(vec4)));
	debug();

	vUv = glGetAttribLocation(program, "vUv");
	glEnableVertexAttribArray(vUv);
	glVertexAttribPointer(vUv, 2, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(sizeof(vec4) + sizeof(vec3)));
	debug();

	ModelView = glGetUniformLocation(program, "ModelView");
	Projection = glGetUniformLocation(program, "Projection");

	AmbientProduct = glGetUniformLocation(program, "AmbientProduct");
	DiffuseProduct = glGetUniformLocation(program, "DiffuseProduct");
	SpecularProduct = glGetUniformLocation(program, "SpecularProduct");
	Shininess = glGetUniformLocation(program, "Shininess");
	LightPosition = glGetUniformLocation(program, "LightPosition");
	TextureMode = glGetUniformLocation(program, "TextureMode");
	TextureID = glGetUniformLocation(program, "TextureID");

	//fixed light to the camera
	vec4 light_position(0, 0, 0, 1.0); //wrt camera

}


void FrameGL::initBuffers() {
	bufferGL = new BufferGL();

	glEnable(GL_DEPTH_TEST);
	debug();
	program = InitShader("vshader2.glsl", "fshader2.glsl");
	glUseProgram(program);
	debug();
	printf("Opengl Version: %s\n", glGetString(GL_VERSION));

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

	Camera * camera = frameInstance->cam;
	if (camera == nullptr) {
		glutSwapBuffers();
		return;
	}

	point4 eye = camera->getComponent<Transform>()->getPosition();
	vec4 rotation = camera->getComponent<Transform>()->getRotation();
	vec4 up = camera->getUpVector();
	mat4 mv = Look(eye, rotation, up);

	mat4 mo;
	BufferGL * buffer = frameInstance->bufferGL;

	PointGL * points = buffer->getPoints();
	int numPoints = buffer->getNumPoints();
	mat4 * mos = buffer->getMatrices();
	Integer * sizes = buffer->getSizes();
	int count = buffer->getCount();
	bool dirty = buffer->getDirty();
	Material * materials = buffer->getMaterials();

	/*DEBUG*/
	PointGL dbPoints[1000];
	int db;
	for (db = 0; db < numPoints && db < 1000; db++) {
		dbPoints[db] = points[db];
	}
	/*DEBUG*/

	if (dirty) {
		//printf("displayfunc:dirty\n");
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
		Material material = materials[i];

		vec4 ambient_product = light_ambient * material.getAmbientColor();
		vec4 diffuse_product = light_diffuse * material.getDiffuseColor();
		vec4 specular_product = light_specular * material.getSpecularColor();

		float material_shininess = material.getShininess();

		glUniform4fv(AmbientProduct, 1, ambient_product);
		glUniform4fv(DiffuseProduct, 1, diffuse_product);
		glUniform4fv(SpecularProduct, 1, specular_product);
		glUniform1f(Shininess, material_shininess);

		TextureGL * texture = material.getColorTexture();
		if (texture != nullptr && texture->getData() != nullptr) {
			if (texture->getDirty()) {
				// Initialize texture objects
				GLuint textures;
				glGenTextures(1, &textures);

				glBindTexture(GL_TEXTURE_2D, textures);

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->getWidth(), texture->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, texture->getData());

				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glActiveTexture(GL_TEXTURE0);
				glUniform1i(TextureID, 0);
				texture->setDirty(false);
				texture->setId(textures);
			}
			glUniform1i(TextureMode, HASTEXTURE);
			glBindTexture(GL_TEXTURE_2D, texture->getId());
		}
		else {
			glUniform1i(TextureMode, NOTEXTURE);
		}
		
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
	//printf("framegl:keydownfunc key:%d\n", key);
	FrameGL * frame = getInstance();
	if (frame->keyHandler != nullptr) {
		frame->keyHandler->keyPressed(key);
	}
}

void FrameGL::keyboardUpFunc(unsigned char key, int x, int y) {
	//printf("framegl:keyupfunc key:%d\n", key);
	FrameGL * frame = getInstance();
	if (frame->keyHandler != nullptr) {
		frame->keyHandler->keyReleased(key);
	}
}

void FrameGL::specialDownFunc(int key, int x, int y) {
	FrameGL * frame = getInstance();
	if (frame->keyHandler != nullptr) {
		frame->keyHandler->specialPressed(key);
	}
}

void FrameGL::specialUpFunc(int key, int x, int y) {
	FrameGL * frame = getInstance();
	if (frame->keyHandler != nullptr) {
		frame->keyHandler->specialReleased(key);
	}
}

void FrameGL::reshapeFunc(int w, int h) {
	//printf("framegl:reshapefunc w:%d h%d\n", w, h);
	frameInstance->width = w;
	frameInstance->height = h;

	glViewport(0, 0, w, h);
	if (frameInstance->cam != nullptr) {
		
		mat4 projection = frameInstance->cam->getProjection();

		glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);
	}
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

void FrameGL::setCamera(Camera * camera) {
	cam = camera;
	mat4 projection = camera->getProjection();

	glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);
}
#endif