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
private:

	// Vectors to store all information from the obj files
	vector<GLfloat> vertices; // v
	vector<GLfloat> normals; // n
	vector<GLfloat> textures; // t
	vector<GLushort> indices; // f
	vector<GLfloat> vertexNormalsFile; // vn in file order
	vector<GLfloat> vertexTexturesFile; // vt in file order
	vector<GLushort> fNormal; // f line - vn
	vector<GLushort> fTexture;// f line - vt
	vector<GLfloat> verticesFile; // v in file order

	// Translate, rotate and scale properties 
	float xTranslate, xRotate, xScale;
	float yTranslate, yRotate, yScale;
	float zTranslate, zRotate, zScale;

	// Used to rotate the model as the program runs
	float angleIncrementX, angleIncrementY, angleIncrementZ;
	float totalAngleIncrementX, totalAngleIncrementY, totalAngleIncrementZ;

	// Array to store texture data
	char textureData[256*256*3];
	GLuint textureID[1];

public:

	// Create a model with all parameters from a file
	Model(float tx, float ty, float tz, float rx, float ry, float rz, float sx, float sy, float sz, float aix, float aiy, float aiz); 
	bool loadModel(string fileName);					// Loads a model from an obj file
	virtual void draw();								// Handles all the openGL draw stuff
	bool loadTexture(string fileName);					// Load the texture for the model
};

#endif	// MODEL_H