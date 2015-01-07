
#include <windows.h>


#include <gl/gl.h>
#include <gl/glu.h>

#include "Spaceship.h"

Spaceship::Spaceship()
{
	armAngles[LEFT] = 0.0;
	armAngles[RIGHT] = 0.0;
	legAngles[LEFT] = 0.0;
	legAngles[RIGHT] = 0.0;

	armStates[LEFT] = FORWARD_STATE;
	armStates[RIGHT] = BACKWARD_STATE;

	legStates[LEFT] = FORWARD_STATE;
	legStates[RIGHT] = BACKWARD_STATE;

	walkCounter = 0;
}

Spaceship::~Spaceship()
{
}

void Spaceship::DrawCube(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glTranslatef(xPos, yPos, zPos);
		glBegin(GL_POLYGON);
			glVertex3f(0.0f, 0.0f, 0.0f);	// top face
			glVertex3f(0.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// front face
			glVertex3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// right face
			glVertex3f(0.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, -1.0f);
			glVertex3f(0.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, 0.0f, 0.0f);	// left face
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// bottom face
			glVertex3f(0.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// back face
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(0.0f, -1.0f, -1.0f);
		glEnd();
	glPopMatrix();
}

void Spaceship::DrawArm(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);	// red
		glTranslatef(xPos, yPos, zPos);
		glScalef(1.0f, 4.0f, 1.0f);		// arm is a 1x4x1 cube
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Spaceship::DrawHead(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);	// white
		glTranslatef(xPos, yPos, zPos);
		glScalef(2.0f, 2.0f, 1.0f);		// head is a 2x2x1 cube
		DrawCube(0.0f, -1.0f, -5.0f);

	glPopMatrix();
}

void Spaceship::DrawTorso(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(0.0f, 0.0f, 1.0f);	// blue
		glTranslatef(xPos, yPos, zPos);
		glScalef(3.0f, 2.0f, 5.0f);		// torso is a 3x5x2 cube
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Spaceship::DrawLeg(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glTranslatef(xPos, yPos, zPos);

		/*
		// draw the foot
		glPushMatrix();
			glTranslatef(0.0f, -0.5f, 0.0f);
			DrawFoot(0.0f, -5.0f, 0.0f);
		glPopMatrix();		
		*/

		glScalef(1.0f, 5.0f, 1.0f);		// leg is a 1x5x1 cube
		glColor3f(1.0f, 1.0f, 0.0f);	// yellow
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Spaceship::DrawFoot(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(xPos, yPos, zPos);
		glScalef(1.0f, 0.5f, 3.0f);
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Spaceship::DrawSpaceship()
{
	glPushMatrix();	

		// draw head and torso parts
		DrawHead(1.0f, 2.0f, 0.0f);		
		DrawTorso(1.5f, 0.0f, 0.0f);

		// move the right red block
		glPushMatrix();
			glTranslatef(0.0f, -0.5f, 0.0f);
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			DrawArm(2.5f, 0.0f, -0.5f);
		glPopMatrix();

		// move the left red block
		glPushMatrix();
			glTranslatef(0.0f, -0.5f, 0.0f);
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			DrawArm(-1.5f, 0.0f, -0.5f);
		glPopMatrix();

		// move the left yellow/white block
		glPushMatrix();					
			glTranslatef(-1.5f, -2.0f, -5.0f);
			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			glScalef(1.0f, 1.0f, 0.5f);
			DrawLeg(-0.5f, 0.0f, -0.5f);
		glPopMatrix();

		// move the right yellow/white
		glPushMatrix();
			glTranslatef(1.5f, -2.0f, -5.0f);
			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
			glScalef(1.0f, 1.0f, 0.5f);
			DrawLeg(1.5f, 0.0f, -0.5f);
		glPopMatrix();

		
	glPopMatrix();	// pop back to original coordinate system

}

void Spaceship::Prepare(float dt)
{
	// if leg is moving forward, increase angle, else decrease angle
	for (char side = 0; side < 2; side++)
	{
		// arms
		if (armStates[side] == FORWARD_STATE)
			armAngles[side] += 0.0f * dt;				// 20.0f
		else
			armAngles[side] -= 0.0f * dt;				// 20.0f

		// change state if exceeding angles
		if (armAngles[side] >= 0.0f)					// 15.0f
			armStates[side] = BACKWARD_STATE;
		else if (armAngles[side] <= 0.0f)				// 0.0f
			armStates[side] = FORWARD_STATE;

		// legs
		if (legStates[side] == FORWARD_STATE)
			legAngles[side] += 0.0f * dt;				// 20.0f
		else
			legAngles[side] -= 0.0f * dt;				// 20.0f

		// change state if exceeding angles
		if (legAngles[side] >= 0.0f)					// 15.0f
			legStates[side] = BACKWARD_STATE;
		else if (legAngles[side] <= 0.0f)				// 15.0f
			legStates[side] = FORWARD_STATE;		
	}
}

void Spaceship::moveForward()
{
	if (walkCounter == 0 || walkCounter == 1 || walkCounter == 6 || walkCounter == 7)		// Move legs one way
	{
		legAngles[0] += 5.0f;
		legAngles[1] -= 5.0f;
	}

	if (walkCounter == 2 || walkCounter == 3 || walkCounter == 4 || walkCounter == 5)		// Move legs the other way
	{
		legAngles[0] -= 5.0f;
		legAngles[1] += 5.0f;
	}

	walkCounter++;			// Increment walkCounter

	if (walkCounter > 7)	// If a walk cycle is finished, reset it
	{
		walkCounter = 0;
	}
}