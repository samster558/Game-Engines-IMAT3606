#include "Camera.h"

Camera::Camera()
{
	cameraPositionIncrement = 0.1f;
	xLook = 0.f;
	yLook = 0.f;
	zLook = -50.f;

	yCameraPosition = 0.f;
	xCameraPosition = 0.f;
	zCameraPosition = 0.f;
}

void Camera::setInitRotate(GLfloat x, GLfloat y)
{
	oldMousePosX = x;
	oldMousePosY = y;
}

void Camera::Moving()
{
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			xCameraPosition +=cameraPositionIncrement;
			xLook +=cameraPositionIncrement;
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			xCameraPosition -=cameraPositionIncrement;
			xLook -=cameraPositionIncrement;
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			zCameraPosition -=cameraPositionIncrement;
			zLook -=cameraPositionIncrement;
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			zCameraPosition +=cameraPositionIncrement;
			zLook +=cameraPositionIncrement;
		}

		rotateX();
		rotateY();
		gluLookAt(xCameraPosition, yCameraPosition, zCameraPosition, xLook, yLook, zLook, 0, 1, 0);
}

void Camera::rotateX()
{
	mousePosX = sf::Mouse::getPosition().x;
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
	{
		GLfloat d;

		d = (mousePosX - oldMousePosX) / 100;
		xCameraPosition += d;
		
	}

	oldMousePosX = mousePosX;
}

void Camera::rotateY()
{
	mousePosY = sf::Mouse::getPosition().y;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
	{
		GLfloat d;
		d = (mousePosY - oldMousePosY) / 100;
		yCameraPosition += d;
	}
	oldMousePosY = mousePosY;
}

void Camera::setPosition(GLfloat xpos, GLfloat ypos, GLfloat zpos)
{
	xCameraPosition = xpos;
	yCameraPosition = ypos;
	zCameraPosition = zpos;
}