/**
@file Camera.h
*/

#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Camera
{
protected:

	sf::Event Event;

	// Moving variables
	GLfloat xCameraPosition, yCameraPosition, zCameraPosition;
	GLfloat xLook, yLook, zLook;


	// Rotation Variables
	GLfloat cameraPositionIncrement;
	bool altKeyDown;
	GLfloat oldMousePosX, oldMousePosY;
	GLfloat mousePosX, mousePosY;
	GLfloat yRotate, xRotate;
	GLfloat angleIncrementX, angleIncrementY ;
	GLfloat mouseRotationX, mouseRotationY;

public:

	Camera();									// Constructor	
	void Moving();								// Move camera function
	void setInitRotate(GLfloat x, GLfloat y);	// Set initial rotation values for Glulookat
	void rotateX();								// Function to calculate x Rotation
	void rotateY();								// Function to calculate y Rotation
	void pan();
	void zoom();

	void setPosition(GLfloat xpos, GLfloat ypos, GLfloat zpos);
};


#endif