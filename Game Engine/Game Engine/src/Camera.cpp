#include "Camera.h"

Camera::Camera()
{
	cameraPositionIncrement = 0.1f;
	xLook = 0.f;
	yLook = 0.f;
	zLook = -30.0f;

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
		
	// Pan won't work if rotateX and rotateY come before it for some reason

	mousePosX = sf::Mouse::getPosition().x;
	mousePosY = sf::Mouse::getPosition().y;
	
		if(!(oldMousePosX == mousePosX))
		{
			rotateX();
		}
		if(!(oldMousePosY == mousePosY))
		{
			rotateY();
		}
		
		if(!(oldMousePosX == mousePosX))
		{
				if(!(oldMousePosY == mousePosY))
				{
					pan();	// Move around the scene in X and Y
				}
		}

		if(Event.KeyPressed)
		{
			zoom(); // Go forward and back in Z
		}

		gluLookAt(xCameraPosition, yCameraPosition, zCameraPosition, xLook, yLook, zLook, 0, 1, 0);

	oldMousePosX = mousePosX;
	oldMousePosY = mousePosY;


}

void Camera::rotateX()
{
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		float delta = (mousePosX - oldMousePosX) / 20;

		glm::vec3 target = glm::vec3 (xLook, yLook, zLook);

		glm::vec3 position = glm::vec3 (xCameraPosition, yCameraPosition, zCameraPosition);


		glm::mat4 t1 = glm::translate(glm::mat4(1.0),-target);
		glm::mat4 t2 = glm::translate(glm::mat4(1.0),target);

		glm::mat4 rotateAroundY = glm::rotate(glm::mat4 (1.0f), delta, glm::vec3(0.0f, 1.0f, 0.0f));

		position = glm::vec3(t2 * rotateAroundY * t1 * glm::vec4(position,1.0));

		xCameraPosition = position.x;
		yCameraPosition = position.y;
		zCameraPosition = position.z;
	}
}

void Camera::rotateY()
{
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
	float delta = (mousePosY - oldMousePosY) / 20;

		glm::vec3 target = glm::vec3 (xLook, yLook, zLook);

		glm::vec3 position = glm::vec3 (xCameraPosition, yCameraPosition, zCameraPosition);

		glm::mat4 t1 = glm::translate(glm::mat4(1.0),-target);
		glm::mat4 t2 = glm::translate(glm::mat4(1.0),target);

		glm::mat4 rotateAroundX = glm::rotate(glm::mat4 (1.0f), delta, glm::vec3(1.0f, 0.0f, 0.0f));

		position = glm::vec3(t2 * rotateAroundX * t1 * glm::vec4(position,1.0));

		xCameraPosition = position.x;
		yCameraPosition = position.y;
		zCameraPosition = position.z;
	}
}

void Camera::pan()
{
	mousePosX = sf::Mouse::getPosition().x;
	mousePosY = sf::Mouse::getPosition().y;

	if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		// difference in mouse position

		float deltaX = (mousePosX - oldMousePosX) / 30;
		float deltaY = (mousePosY - oldMousePosY) / 30;
		
		// create vectors for where the camera is and where it is looking

		glm::vec3 target = glm::vec3 (xLook, yLook, zLook);
		glm::vec3 position = glm::vec3 (xCameraPosition, yCameraPosition, zCameraPosition);

		// calculate forward and right vectors, then normalise them

		glm::vec3 forward = target - position;

		forward = glm::normalize(forward);

		glm::vec3 right = glm::cross(forward, glm::vec3(0.0,1.0,0.0));

		right = glm::normalize(right);

		// update the position and target vectors for X

		position = position + (right*deltaX);
		target = target + (right*deltaX);
		
		// calculate the up vector from the forward and right vectors

		glm::vec3 up = glm::cross(forward, right);

		// update the position and target vectors for Y

		position = position + (up*deltaY);
		target = target + (up*deltaY);

		// set the camera's position and look at point to these new calculated values

		xCameraPosition = position.x;
		yCameraPosition = position.y;
		zCameraPosition = position.z;

		xLook = target.x;
		yLook = target.y;
		zLook = target.z;

	}
}

void Camera::zoom()
{
		float deltaZ;

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			deltaZ = 0.075;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			deltaZ = -0.075;
		}
		else
		{
			deltaZ = 0;
		}

			// create vectors for where the camera is and where it is looking

			glm::vec3 target = glm::vec3 (xLook, yLook, zLook);
			glm::vec3 position = glm::vec3 (xCameraPosition, yCameraPosition, zCameraPosition);

			// calculate forward vector and normalise it

			glm::vec3 forward = target - position;

			forward = glm::normalize(forward);

			// update the position and target vectors for Z

			position = position + (forward*deltaZ);

			target = target + (forward*deltaZ);
		
			// set the camera's position and look at point to these new calculated values

			xCameraPosition = position.x;
			yCameraPosition = position.y;
			zCameraPosition = position.z;

			xLook = target.x;
			yLook = target.y;
			zLook = target.z;
}

void Camera::setPosition(GLfloat xpos, GLfloat ypos, GLfloat zpos)
{
	xCameraPosition = xpos;
	yCameraPosition = ypos;
	zCameraPosition = zpos;
}