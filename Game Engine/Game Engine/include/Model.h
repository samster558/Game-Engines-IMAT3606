/**
@file Model.h
*/

#ifndef MODEL_H
#define MODEL_H

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Model
{
	friend class Scene;
protected:

	// vectors to store all information from the obj files

	vector<GLfloat> vertices; // v
	vector<GLfloat> normals; // n
	vector<GLfloat> textures; // t
	vector<GLushort> indices; // f
	vector<GLfloat> vertexNormalsFile; // vn in file order
	vector<GLfloat> vertexTexturesFile; // vt in file order
	vector<GLushort> fNormal; // f line - vn
	vector<GLushort> fTexture;// f line - vt
	vector<GLfloat> verticesFile; // v in file order
	//Movement M;

	// translate, rotate and scale properties 
	float xTranslate, xRotate, xScale;
	float yTranslate, yRotate, yScale;
	float zTranslate, zRotate, zScale;

	// array to store texture data
	char textureData[256*256*3];
	GLuint textureID[1];

public:

	Model(float tx, float ty, float tz, float rx, float ry, float rz, float sx, float sy, float sz); // Create a model with all parameters from a file
	bool loadModel(string fileName);																 // Loads a model from an obj file
	virtual void draw();																			 // Handles all the openGL draw stuff
	bool loadTexture(string fileName);																 // load the texture for the model
};

#endif