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
private:

	// Event used to check for key presses
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
	void update();								// Update camera function

	void moving();								// Move camera function
	void setInitRotate(GLfloat x, GLfloat y);	// Set initial rotation values for Glulookat
	void rotateX();								// Function to calculate x Rotation
	void rotateY();								// Function to calculate y Rotation
	void pan();									// Pan the camera function
	void zoom();								// Zoom the camera (move forward/back)

	void setPosition(GLfloat xpos, GLfloat ypos, GLfloat zpos);					// Set the camera's position
	void setTarget(GLfloat xtarget, GLfloat ytarget, GLfloat ztarget);			// Set the camera's target position
};

#endif // CAMERA_H