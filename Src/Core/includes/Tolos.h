#ifndef TOLOS_H
#define TOLOS_H
#include <stdio.h>
#include <vector>
#include "Angel.h"
typedef Angel::vec4 point4;
typedef Angel::vec4 color4;
bool readBMP(const char* filename, int * w, int * h, GLubyte ** image)
{
	int i;
	FILE* f = fopen(filename, "rb");
	if (!f) {
		printf("file %s not found\n", filename);
		return false;
	}
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header
											   // extract image height and width from header
	int width = *(int*)&info[18];
	int height = *(int*)&info[22];
	printf("size: %d, %d\n", width, height);
	int size = 3 * width * height;

	GLubyte * data = (GLubyte *)malloc(3 * sizeof(GLubyte) * width * height);
	fread(data, sizeof(unsigned char), 3 * width * height, f);

	//unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
	//fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
	fclose(f);

	for (i = 0; i < size; i += 3)
	{
		GLubyte tmp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = tmp;
	}

	*w = width;
	*h = height;
	*image = data;
	return true;
}

GLubyte *  readPPM(const char * filename, int * w, int * h)
{
	int i, n, m;
	char dummy[200];
	FILE *fp;
	int r;
	fp = fopen(filename, "r");
	// fgets(dummy,200,fp);
	fgets(dummy, 200, fp);
	fgets(dummy, 200, fp);
	fgets(dummy, 200, fp);
	fgets(dummy, 200, fp);
	fgets(dummy, 200, fp);
	fscanf(fp, "%d %d\n", &n, &m);
	fscanf(fp, "%d\n", &r);

	GLubyte * data = (GLubyte *)malloc(3 * sizeof(GLubyte) * n * m);
	fread(data, 1, 3 * n * m, fp);

	fclose(fp);

	*w = n;
	*h = m;
	return data;
}

bool readOBJ(const char * filename, point4 ** points, vec2 ** uvs, vec3 ** normals, int * numVertex) {
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< point4 > temp_vertices;
	std::vector< vec2 > temp_uvs;
	std::vector< vec3 > temp_normals;
	int fCount=0;
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("File %s cant open\n", filename);
		return false;
	}

	while (1) {
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		//printf("%s", lineHeader);
		if (res == EOF)
			break;

		if (strcmp(lineHeader, "v") == 0) {
			float x, y, z;
			fscanf(file, "%f %f %f\n", &x, &y, &z);
			//printf(" %f %f %f ", x, y, z);
			point4 vertex(x, y, z, 1);
			temp_vertices.push_back(vertex);
		}

		else if (strcmp(lineHeader, "vt") == 0) {
			float x, y;
			fscanf(file, "%f %f\n", &x, &y);
			//printf(" %f %f ", x, y);
			temp_uvs.push_back(vec2(x, y));
		}

		else if (strcmp(lineHeader, "vn") == 0) {
			float x, y, z;
			fscanf(file, "%f %f %f\n", &x, &y, &z);
			//printf(" %f %f %f", x, y, z);
			temp_normals.push_back(vec3(x, y, z));
		}

		else if (strcmp(lineHeader, "f") == 0) {
			fCount++;
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
			//printf(" %d/%d/%d %d/%d/%d %d/%d/%d ", vertexIndex[0], uvIndex[0], normalIndex[0], vertexIndex[1], uvIndex[1], normalIndex[1], vertexIndex[2], uvIndex[2], normalIndex[2]);
		}
		//printf("\n");
	}
	int a = vertexIndices.size();
	point4 * outVertex = (point4 *)malloc(sizeof(point4) * a);
	vec2 * outUv = (vec2 *)malloc(sizeof(vec2) * a);
	vec3 * outNormal = (vec3 *)malloc(sizeof(vec3) * a);
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int index = vertexIndices[i];
		outVertex[i] = temp_vertices[index - 1];
		//printf("%d %f,%f,%f\n", index, outVertex[i].x, outVertex[i].y, outVertex[i].z);
	}

	for (unsigned int i = 0; i < uvIndices.size(); i++) {
		unsigned int index = uvIndices[i];
		outUv[i] = temp_uvs[index - 1];
	}

	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int index = normalIndices[i];
		outNormal[i] = temp_normals[index - 1];
	}

	*points = outVertex;
	*uvs = outUv;
	*normals = outNormal;
	*numVertex = fCount;
	return true;
}

bool readOBJTEX(const char * objFileName, point4 ** points, vec2 ** uvs, vec3 ** normals, int * numVertex, const char* bmpFileName, int * w, int * h, GLubyte ** image) {

	return true;
}
#endif //TOLOS_H