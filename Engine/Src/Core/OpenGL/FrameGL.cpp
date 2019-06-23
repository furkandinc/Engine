#include "FrameGL.h"
#include "..\includes\Angel.h"

#define HASTEXTURE 1
#define FONTTEXTURE 0
#define NOTEXTURE -1

typedef Angel::vec4 point4;

GLuint ModelView, Projection, program;
GLuint vPosition, vUv, vNormal;
GLuint Vao, Buffer;
GLuint AmbientProduct, DiffuseProduct, SpecularProduct;
GLuint Shininess;
GLuint LightPosition;
GLuint TextureMode;
GLuint TextureID;
GLuint FontUv;

vec4 light_ambient(1, 1, 1, 1);
vec4 light_diffuse(1, 1, 1, 1);
vec4 light_specular(1, 1, 1, 1);

// TODO make list
Font _font;
TextureGL * _fontTexture;
ObjectGL * _fontObj;


FrameGL * FrameGL::frameInstance = NULL;

FrameGL::FrameGL() {
	objectHandler = new ObjectHandler();
	uiObjectHandler = new ObjectHandler();
}

void debug() {
	GLenum errCode = glGetError();
	if (errCode != 0) {
		printf("Error %d %s\n", errCode, gluErrorString(errCode));
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
	glutInitWindowPosition(0, 0);
	glutCreateWindow(title);
	glewExperimental = GL_TRUE;
	glewInit();
	debug();
	printf("Opengl Version: %s\n", glGetString(GL_VERSION));

	glClearColor(0, 0, 0, 0);
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
	FontUv = glGetUniformLocation(program, "FontUv");

	//fixed light to the camera
	vec4 light_position(0, 0, 0, 1.0); //wrt camera

}

GLuint LoadTexture(TextureGL * textureGL) {
	GLuint textures;
	glGenTextures(1, &textures);

	glBindTexture(GL_TEXTURE_2D, textures);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureGL->getWidth(), textureGL->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureGL->getData());

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(TextureID, 0);
	textureGL->setDirty(false);
	textureGL->setId(textures);

	return textures;
}

GLuint LoadObject(ObjectGL * objectGL) {
	GLuint bufferid;
	glGenBuffers(1, &bufferid);
	glBindBuffer(GL_ARRAY_BUFFER, bufferid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(PointGL) * objectGL->getSize(), (PointGL *) objectGL->getData(), GL_STATIC_DRAW);
	debug();
	objectGL->setDirty(false);
	objectGL->setId(bufferid);
	refreshPointers();
	return bufferid;
}

void FrameGL::initBuffers() {
	glEnable(GL_DEPTH_TEST);
	debug();
	program = InitShader("vshader2.glsl", "fshader2.glsl");
	glUseProgram(program);
	debug();

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

	frameInstance->renderObj();
	frameInstance->renderUI();
	
	glutSwapBuffers();
}

void FrameGL::renderObj() {
	Camera * camera = frameInstance->cam;

	point4 eye = camera->getComponent<Transform>()->globalPosition();
	vec4 rotation = camera->getComponent<Transform>()->globalRotation();
	vec4 up = camera->getComponent<Transform>()->getUpVector();
	mat4 mv = Look(eye, rotation, up);

	mat4 mo;

	Object ** objectList = frameInstance->objectHandler->getList();
	int count = frameInstance->objectHandler->getSize();

	for (int i = 0; i < count; i++) {
		Object * object = objectList[i];

		Transform * transform = object->getComponent<Transform>();

		Renderer * renderer = object->getComponent<Renderer>();

		Mesh * mesh = renderer->getMesh();
		Material * material = renderer->getMaterial();
		ObjectGL * objectGL = renderer->getMesh()->getObjectGL();
		
		vec4 ambient_product = light_ambient * material->getAmbientColor();
		vec4 diffuse_product = light_diffuse * material->getDiffuseColor();
		vec4 specular_product = light_specular * material->getSpecularColor();
		float material_shininess = material->getShininess();

		if (objectGL->getDirty()) {
			LoadObject(objectGL);
		}

		glBindBuffer(GL_ARRAY_BUFFER, objectGL->getId());
		refreshPointers();

		mo = mv * transform->generateMatrix();
		glUniformMatrix4fv(ModelView, 1, GL_TRUE, mo);

		glUniform3fv(AmbientProduct, 1, ambient_product);
		glUniform3fv(DiffuseProduct, 1, diffuse_product);
		glUniform3fv(SpecularProduct, 1, specular_product);
		glUniform1f(Shininess, material_shininess);

		TextureGL * textureGL = material->getColorTexture();
		if (textureGL != nullptr) {
			if (textureGL->getDirty()) {
				LoadTexture(textureGL);
			}
			glUniform1i(TextureMode, HASTEXTURE);
			glBindTexture(GL_TEXTURE_2D, textureGL->getId());
		}
		else {
			glUniform1i(TextureMode, NOTEXTURE);
		}

		glDrawArrays(GL_TRIANGLES, 0, objectGL->getSize());
		debug();
	}
}

void FrameGL::renderUI() {
	Camera * camera = frameInstance->cam;

	point4 eye = camera->getComponent<Transform>()->globalPosition();
	vec4 rotation = camera->getComponent<Transform>()->globalRotation();
	vec4 up = camera->getComponent<Transform>()->getUpVector();
	mat4 mv = Look(eye, rotation, up);

	mat4 mo;

	Object ** objectList = frameInstance->uiObjectHandler->getList();
	int count = frameInstance->uiObjectHandler->getSize();

	for (int i = 0; i < count; i++) {
		Object * object = objectList[i];

		Transform * transform = object->getComponent<Transform>();
		UIText * uitext = object->getComponent<UIText>();

		Material * material = uitext->getMaterial();;
		ObjectGL * objectGL = _fontObj;
		TextureGL * textureGL = _fontTexture;

		vec4 ambient_product = light_ambient * material->getAmbientColor();
		vec4 diffuse_product = light_diffuse * material->getDiffuseColor();
		vec4 specular_product = light_specular * material->getSpecularColor();
		float material_shininess = material->getShininess();

		if (objectGL->getDirty()) {
			LoadObject(objectGL);
		}

		glBindBuffer(GL_ARRAY_BUFFER, objectGL->getId());
		refreshPointers();

		glUniform3fv(AmbientProduct, 1, ambient_product);
		glUniform3fv(DiffuseProduct, 1, diffuse_product);
		glUniform3fv(SpecularProduct, 1, specular_product);
		glUniform1f(Shininess, material_shininess);

		glUniform1i(TextureMode, FONTTEXTURE);
		glBindTexture(GL_TEXTURE_2D, textureGL->getId());

		int len = strlen(uitext->getText());
		int row = 0;
		int col = 0;
		for (int i = 0; i < len; i++) {
			mo = mv * transform->generateMatrix() * Translate(col, 0, -row);
			glUniformMatrix4fv(ModelView, 1, GL_TRUE, mo);
			FontChar fchar = _font.chars[uitext->getText()[i]];
			switch (fchar.charid) {
			case '\n':
				col = 0;
				row++;
				continue;
			case '\t':
				col += 4;
				continue;
			default:
				col++;
			}
		
			vec2 fontOffset;
			fontOffset.x = (float)fchar.x / _font.imagewidth;
			fontOffset.y = 1 - ((float)fchar.y / _font.imageheight);
			glUniform2fv(FontUv, 1, fontOffset);

			glDrawArrays(GL_TRIANGLES, 0, objectGL->getSize());
			debug();
		}
	}
}

void FrameGL::addObject(Object * object) {
	objectHandler->add(object);
}

void FrameGL::removeObject(Object * object) {
	objectHandler->remove(object);
}

void FrameGL::addUIObject(Object * object) {
	uiObjectHandler->add(object);
}

void FrameGL::removeUIObject(Object * object) {
	uiObjectHandler->remove(object);
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

void FrameGL::loadFont(Font font) {
	_font = font;
	_fontTexture = new TextureGL(font.charuv);
	_fontObj = new ObjectGL(font.charobj);
	LoadTexture(_fontTexture);
	LoadObject(_fontObj);
}