
#include <windows.h>


#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include "SpaceshipHandler.h"
#include "Spaceship.h"

// disable implicit float-double casting
#pragma warning(disable:4305)

SpaceshipHandler::SpaceshipHandler()
{
}

SpaceshipHandler::~SpaceshipHandler()
{
}

bool SpaceshipHandler::Init()
{	
	theSpaceship = new Spaceship;

	spaceshipX = 0.0f;
	spaceshipY = 0.0f;
	spaceshipZ = -10.0f;

	rotationAngle = 0.0f;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	return true;
}

bool SpaceshipHandler::Shutdown()
{
	delete theSpaceship;

	return true;
}

void SpaceshipHandler::SetupProjection(int width, int height)
{
	if (height == 0)					// Don't want a divide by zero
	{
		height = 1;					
	}

	glViewport(0, 0, width, height);		// Reset the viewport to new dimensions
	glMatrixMode(GL_PROJECTION);			// Set projection matrix current matrix
	glLoadIdentity();						// Reset projection matrix

	// Calculate aspect ratio of window
	gluPerspective(52.0f,(GLfloat)width/(GLfloat)height,1.0f,1000.0f);

	glMatrixMode(GL_MODELVIEW);				// Set modelview matrix
	glLoadIdentity();						// Reset modelview matrix

	m_windowWidth = width;
	m_windowHeight = height;
}

void SpaceshipHandler::Prepare(float dt)
{
	rotationAngle += 0.0f * dt;				// increase our rotation angle counter
	if (rotationAngle >= 360.0f)			// if we've gone in a circle, reset counter
		rotationAngle = 0.0f;

	theSpaceship->Prepare(dt);
}

void SpaceshipHandler::Render()
{
	glPushMatrix();							// Put current matrix on stack
		// glLoadIdentity();				// Reset matrix
		glTranslatef(spaceshipX, spaceshipY, spaceshipZ);	// Move to (0, 0, -30) starting point

		
		glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);	// Rotate the spaceship on its y-axis

		theSpaceship->DrawSpaceship();	// Draw the spaceship
		
		// Render code changed so that it does translate then rotate
		// rather than translate then rotate then translate again (bad idea)


		// Change the screen back to white for rendering other models in the scene
		glColor3f(1.0f, 1.0f, 1.0f);

	glPopMatrix();
}

float SpaceshipHandler::getX()
{
	return spaceshipX;
}

float SpaceshipHandler::getY()
{
	return spaceshipY;
}

float SpaceshipHandler::getZ()
{
	return spaceshipZ;
}

float SpaceshipHandler::getRotation()
{
	return rotationAngle;
}


void SpaceshipHandler::TurnSpaceshipLeft(float angle)
{
	rotationAngle += angle;
}


void SpaceshipHandler::TurnSpaceshipRight(float angle)
{
	rotationAngle -= angle;
}

void SpaceshipHandler::WalkForward()
{
	theSpaceship->moveForward();

	float speedScaler;

	speedScaler = 0.6;		// Used to set the speed of movement

	spaceshipZ = spaceshipZ - ((cos(rotationAngle * PI / 180)) * speedScaler);

	spaceshipX = spaceshipX - ((sin(rotationAngle * PI / 180)) * speedScaler);
}

void SpaceshipHandler::WalkBackwards()
{
	theSpaceship->moveForward();

	float speedScaler;

	speedScaler = 0.6;		// Used to set the speed of movement

	spaceshipZ = spaceshipZ + ((cos(rotationAngle * PI / 180)) * speedScaler);

	spaceshipX = spaceshipX + ((sin(rotationAngle * PI / 180)) * speedScaler);
}