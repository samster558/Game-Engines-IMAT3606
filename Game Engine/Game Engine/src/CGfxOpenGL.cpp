
#include <windows.h>


#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include "CGfxOpenGL.h"
#include "Robot.h"

// disable implicit float-double casting
#pragma warning(disable:4305)

CGfxOpenGL::CGfxOpenGL()
{
}

CGfxOpenGL::~CGfxOpenGL()
{
}

bool CGfxOpenGL::Init()
{	
	theRobot = new Robot;

	robotX = 0.0f;
	robotY = 0.0f;
	robotZ = -30.0f;

	rotationAngle = 0.0f;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	return true;
}

bool CGfxOpenGL::Shutdown()
{
	delete theRobot;

	return true;
}

void CGfxOpenGL::SetupProjection(int width, int height)
{
	if (height == 0)					// don't want a divide by zero
	{
		height = 1;					
	}

	glViewport(0, 0, width, height);		// reset the viewport to new dimensions
	glMatrixMode(GL_PROJECTION);			// set projection matrix current matrix
	glLoadIdentity();						// reset projection matrix

	// calculate aspect ratio of window
	gluPerspective(52.0f,(GLfloat)width/(GLfloat)height,1.0f,1000.0f);

	glMatrixMode(GL_MODELVIEW);				// set modelview matrix
	glLoadIdentity();						// reset modelview matrix

	m_windowWidth = width;
	m_windowHeight = height;
}

void CGfxOpenGL::Prepare(float dt)
{
	rotationAngle += 0.0f * dt;					// increase our rotation angle counter
	if (rotationAngle >= 360.0f)					// if we've gone in a circle, reset counter
		rotationAngle = 0.0f;

	theRobot->Prepare(dt);
}

void CGfxOpenGL::Render()
{
	glPushMatrix();							// Put current matrix on stack
		// glLoadIdentity();					// Reset matrix
		glTranslatef(robotX, robotY, robotZ);	// Move to (0, 0, -30) starting point

		
		glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);	// Rotate the robot on its y-axis

		theRobot->DrawRobot();	// Draw the robot
		
		// Render code changed so that it does translate then rotate
		// rather than translate then rotate then translate again (bad idea)


		// Change the screen back to white for rendering other models in the scene
		glColor3f(1.0f, 1.0f, 1.0f);

	glPopMatrix();
}


void CGfxOpenGL::TurnRobotLeft(float angle)
{
	rotationAngle += angle;
}


void CGfxOpenGL::TurnRobotRight(float angle)
{
	rotationAngle -= angle;
}

void CGfxOpenGL::WalkForward()
{
	theRobot->moveForward();

	float speedScaler;

	speedScaler = 0.02;		// Used to set the speed of movement

	robotZ = robotZ - ((cos(rotationAngle * PI / 180)) * speedScaler);

	robotX = robotX - ((sin(rotationAngle * PI / 180)) * speedScaler);
}

void CGfxOpenGL::WalkBackwards()
{
	theRobot->moveForward();

	float speedScaler;

	speedScaler = 0.02;		// Used to set the speed of movement

	robotZ = robotZ + ((cos(rotationAngle * PI / 180)) * speedScaler);

	robotX = robotX + ((sin(rotationAngle * PI / 180)) * speedScaler);
}