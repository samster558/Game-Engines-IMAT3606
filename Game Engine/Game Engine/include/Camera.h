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

	// Position variables
	GLfloat xCameraPosition, yCameraPosition, zCameraPosition;
	GLfloat xLook, yLook, zLook;


	// Rotation Variables
	bool altKeyDown;
	GLfloat mousePosX, mousePosY;
	GLfloat oldMousePosX, oldMousePosY;
	GLfloat yRotate, xRotate;

public:

	Camera();									// Constructor
	~Camera();									// Destructor
	void Moving();								// Move camera function
	void setInitRotate(GLfloat x, GLfloat y);	// Set initial rotation values for Glulookat
	void rotateX();								// Function to calculate x Rotation
	void rotateY();								// Function to calculate y Rotation
	void pan();
	void zoom();

	void setPosition(GLfloat xpos, GLfloat ypos, GLfloat zpos);
};


#endif