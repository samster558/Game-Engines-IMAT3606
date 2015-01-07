#include "Movement.h"

Movement::Movement()
{
	cameraPositionIncrement = 0.1f;
	xLook = 0.f;
	yLook = 0.f;
	zLook = -1.f;
	yCameraPosition = yLook;
	xCameraPosition = xLook;
	zCameraPosition = 0.f;

}

void Movement::setInitRotate(GLfloat x, GLfloat y)
{
	oldMousePosX = x;
	oldMousePosY = y;
}
void Movement::Moving()
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
		gluLookAt(xCameraPosition,yCameraPosition,zCameraPosition,xLook, yLook, zLook, 0, 1, 0);
}

void Movement::rotateX()
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

void Movement::rotateY()
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