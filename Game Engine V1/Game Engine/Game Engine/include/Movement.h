/**
@file Movement.h
*/

#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

using namespace std;

class Movement
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

	Movement();									// Constructor	
	void Moving();								// Move camera function
	void setInitRotate(GLfloat x, GLfloat y);	// Set initial rotation values for Glulookat
	void rotateX();								// Function to calculate x Rotation
	void rotateY();								// Function to calculate y Rotation
};


#endif