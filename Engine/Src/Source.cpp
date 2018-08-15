// rotating cube with two texture objects
// change textures with 1 and 2 keys
// Self Destruction 9
/*
#include "Core\includes\Angel.h"
#include "Core\includes\Tolos.h"
typedef Angel::vec4 point4;
typedef Angel::vec4 color4;

int liste[100];
float objX[100];
float objTheta[100];

GLubyte * image3;
GLuint vao, texture, ModelView, Projection, ModelObj, program;
GLuint vPosition, vColor, vTexCoord, vNormal;
float camX = 0, camY = -2, camZ = 0;
float camP = 0, camD = 0;
int width, height;
float mSens = 0.3;
float lightX=0;
int numpoints=0;
int Index = 0;
float theta = 0;

void
init()
{
	point4 * points; vec3 * normals; vec2 * tex_coords;
	readOBJ("Assets/maymun.obj", &points, &tex_coords, &normals, &numpoints);
	int imgW, imgH;
	readBMP("Assets/maymun.bmp", &imgW, &imgH, &image3);
	printf("pixel %d %d\n", imgW, imgH);
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgW, imgH, 0, GL_RGB, GL_UNSIGNED_BYTE, image3);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glActiveTexture(GL_TEXTURE0);

	// Create a vertex array object
	vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create and initialize a buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER,
		((sizeof(point4) + sizeof(vec2) + sizeof(vec3)) * numpoints * 3) * 10,
		NULL, GL_STATIC_DRAW);

	// Specify an offset to keep track of where we're placing data in our
	//   vertex array buffer.  We'll use the same technique when we
	//   associate the offsets with vertex attribute pointers.
	GLintptr offset = 0;
	for (int i = 0; i < 1; i++) {
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(point4)*numpoints * 3, points);
		offset += sizeof(point4)*numpoints * 3;
	}

	for (int i = 0; i < 1; i++) {
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vec2)*numpoints * 3, tex_coords);
		offset += sizeof(vec2)*numpoints * 3;
	}

	for (int i = 0; i < 1; i++) {
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vec3)*numpoints * 3, normals);
		offset += sizeof(point4)*numpoints * 3;
	}
	// Load shaders and use the resulting shader program
	program = InitShader("vshaderAssg4.glsl", "fshaderAssg4.glsl");
	glUseProgram(program);

	// set up vertex arrays
	offset = 0;
	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(offset));
	offset += sizeof(point4)*numpoints * 3;

	vTexCoord = glGetAttribLocation(program, "vTexCoord");
	glEnableVertexAttribArray(vTexCoord);
	glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(offset));
	offset += sizeof(vec2)*numpoints * 3;

	vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_TRUE, 0, BUFFER_OFFSET(offset));

	glUniform1i(glGetUniformLocation(program, "texturename"), 0);

	
	color4 light_diffuse(1, 1, 1, 1);
	color4 light_ambient(0.5, 0.5, 0.5, 1.0);
	color4 light_specular(0.5, 0.5, 0.5, 1.0);
	color4 material_specular(1, 1, 1, 1.0);
	float  material_shininess = 500;

	color4 ambient_product = light_ambient;
	color4 diffuse_product = light_diffuse;
	color4 specular_product = light_specular * material_specular;

	glUniform4fv(glGetUniformLocation(program, "AmbientProduct"), 1, ambient_product);
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniform4fv(glGetUniformLocation(program, "SpecularProduct"), 1, specular_product);
	
	glUniform1f(glGetUniformLocation(program, "Shininess"), material_shininess);

	// Retrieve transformation uniform variable locations
	ModelView = glGetUniformLocation(program, "ModelView");
	ModelObj = glGetUniformLocation(program, "ModelObj");
	Projection = glGetUniformLocation(program, "Projection");


	glEnable(GL_DEPTH_TEST);

	glClearColor(0.1, 0.1, 0.1, 1.0);
}

void
display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//look from cam coords to origin of island
	point4 eye = point4(camX, camY, camZ, 1);
	point4 at = Translate(camX,camY,camZ)*RotateZ(camD)*RotateX(camP)*point4(0, 1, 0, 1);
	vec4    up(0.0, 0.0, 1.0, 0.0);
	mat4  mv =LookAt(eye, at, up);
	glUniformMatrix4fv(ModelView, 1, GL_TRUE, mv);
	point4 light_position(lightX, -1, 0, 1.0);
	glUniform4fv(glGetUniformLocation(program, "LightPosition"), 1, light_position);
	mat4 mo;
	int offset = 0;
	for (int i = 0; i < 50; i++) {
		mo = Translate(objX[i]*2, 0, 0)*RotateZ(objTheta[i]);
		glUniformMatrix4fv(ModelObj, 1, GL_TRUE, mo);
		glDrawArrays(GL_TRIANGLES, 0, numpoints * 3);
		offset += numpoints * 3;
	}
	glutSwapBuffers();
}


void
keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case 'q': case 'Q':
			exit(EXIT_SUCCESS);
			break;
		case 'x': camX += 0.5; break;
		case 'X': camX -= 0.5; break;
		case 'y': camY += 0.5; break;
		case 'Y': camY -= 0.5; break;
		case 'z': camZ += 0.5; break;
		case 'Z': camZ -= 0.5; break;
		case 'o': numpoints++; break;
		case 'p': theta += 10; break;
		case '4': lightX -= 0.1; break;
		case '6': lightX += 0.1; break;
	}
}

void
idle(void)
{
	
	for (int i = 0; i < 100; i++) {
		objX[i] = i;
		objTheta[i] += 0.01*i;
		if (objTheta[i] > 360) objTheta[i] = 0;
	}
	glutWarpPointer(width/2, height/2);
	glutPostRedisplay();
	
}

void
reshape(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, width, height);

	GLfloat aspect = GLfloat(width) / height;
	mat4  projection = Perspective(90.0, aspect, 0.1, 300.0);

	glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);
}

void mouse(int x, int y) {
	float d = -(x - width / 2)*mSens;
	float p = -(y - height / 2)*mSens;
	if (p + camP<80 && p + camP>-80) {
		camP += p;
	}
	camD += d;
}

int mani(int argc, char **argv)
{
	glutInit(&argc, argv);

#ifdef __APPLE__
	glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
#else
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
#endif


	glutInitWindowSize(1280, 720);
	//    glutInitContextVersion( 3, 2 );
	// glutInitContextProfile( GLUT_CORE_PROFILE );
	glutCreateWindow("Textured Cube");
	glewExperimental = GL_TRUE;
	glewInit();
	init();

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(mouse);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}
*/