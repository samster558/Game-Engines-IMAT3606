
#include <windows.h>


#include <gl/gl.h>
#include <gl/glu.h>

#include "Spaceship.h"

Spaceship::Spaceship()
{
	wingAngles[LEFT] = 0.0;
	wingAngles[RIGHT] = 0.0;
	cannonAngles[LEFT] = 0.0;
	cannonAngles[RIGHT] = 0.0;

	wingStates[LEFT] = FORWARD_STATE;
	wingStates[RIGHT] = BACKWARD_STATE;

	cannonStates[LEFT] = FORWARD_STATE;
	cannonStates[RIGHT] = BACKWARD_STATE;

	moveFire = 0;
	fireForward = true;

	cycleCounter = 0;
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

void Spaceship::DrawCockpit(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(0.8f, 0.8f, 0.8f);	
		glTranslatef(xPos, yPos, zPos);
		glScalef(2.0f, 2.0f, 1.0f);		// Cockpit is a 2x2x1 cube
		DrawCube(0.0f, -1.0f, -5.0f);
	glPopMatrix();
}

void Spaceship::DrawBody(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(0.8f, 0.8f, 0.8f);	
		glTranslatef(xPos, yPos, zPos);
		glScalef(3.0f, 2.0f, 5.0f);		// Body is a 3x2x5 cube
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Spaceship::DrawWing(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(0.3f, 0.3f, 0.3f);	
		glTranslatef(xPos, yPos, zPos);
		glScalef(1.0f, 4.0f, 1.0f);		// Arm is a 1x4x1 cube
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Spaceship::DrawCannon(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glTranslatef(xPos, yPos, zPos);
		glScalef(1.0f, 5.0f, 1.0f);		// Leg is a 1x5x1 cube
		glColor3f(1.0f, 0.1f, 0.1f);	
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Spaceship::DrawThruster(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glTranslatef(xPos, yPos, zPos);
		glScalef(1.0f, 0.5f, 2.5f);		// Thurster is a 1x0.5x2.5 cube
		glColor3f(0.2f, 0.2f, 0.2f);
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Spaceship::DrawFire(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glTranslatef(xPos, yPos, zPos);
		glScalef(1.0f, 0.5f, 2.5f);		// Fire is a 1x0.5x2.5 cube
		glColor3f(1.0f, 0.5f, 0.0f);
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Spaceship::DrawSpaceship()
{
	glPushMatrix();	

		// Draw Cockpit and Body parts
		DrawCockpit(1.0f, 2.0f, 0.0f);		
		DrawBody(1.5f, 0.0f, 0.0f);

		// Move the right wing block
		glPushMatrix();
			glTranslatef(-4.3f, -0.4f, -0.5f);
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			glScalef(3.0f, 1.0f, 1.0f);
			DrawWing(2.5f, 0.0f, -0.5f);
		glPopMatrix();

		// Move the left wing block
		glPushMatrix();
			glTranslatef(4.3f, -0.4f, -0.5f);
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			glScalef(3.0f, 1.0f, 1.0f);
			DrawWing(-1.5f, 0.0f, -0.5f);
		glPopMatrix();

		// Move the left cannon block
		glPushMatrix();					
			glTranslatef(-1.5f, -2.0f, -5.0f);
			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			// Rotation placeholder for left cannon
			// glRotatef(cannonAngles[LEFT], 0.0f, 0.0f, 1.0f);
			glScalef(1.0f, 1.0f, 0.5f);
			DrawCannon(-0.5f, 0.0f, -0.5f);
		glPopMatrix();

		// Move the right cannon block
		glPushMatrix();
			glTranslatef(1.5f, -2.0f, -5.0f);
			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
			// Rotation placeholder for right cannon
			// glRotatef(cannonAngles[RIGHT], 0.0f, 0.0f, 1.0f);
			glScalef(1.0f, 1.0f, 0.5f);
			DrawCannon(1.5f, 0.0f, -0.5f);
		glPopMatrix();

		// Move the thruster
		glPushMatrix();
			glTranslatef(1.5f, -0.5f, 1.3f);
			glScalef(3.0f, 2.0f, 0.5f);
			DrawThruster(0.0f, 0.0f, 0.0f);
		glPopMatrix();

		// MMve the fire block
		glPushMatrix();
			glTranslatef(1.5f, -0.5f, 2.8f);
			glTranslatef(0.0f, 0.0f, (-moveFire)/100.0f);
			glScalef(3.0f, 2.0f, 0.5f);
			DrawFire(0.0f, 0.0f, 0.0f);
		glPopMatrix();

	glPopMatrix();	// Pop back to original coordinate system
}

void Spaceship::Prepare(float dt)
{
	// If cannon/wing is moving forward, increase angle, else decrease angle
	for (char side = 0; side < 2; side++)
	{
		// Cannons
		if (wingStates[side] == FORWARD_STATE)
			wingAngles[side] += 0.0f * dt;				// 20.0f
		else
			wingAngles[side] -= 0.0f * dt;				// 20.0f

		// Change state if exceeding angles
		if (wingAngles[side] >= 0.0f)					// 15.0f
			wingStates[side] = BACKWARD_STATE;
		else if (wingAngles[side] <= 0.0f)				// 0.0f
			wingStates[side] = FORWARD_STATE;

		// Wings
		if (cannonStates[side] == FORWARD_STATE)
			cannonAngles[side] += 0.0f * dt;				// 20.0f
		else
			cannonAngles[side] -= 0.0f * dt;				// 20.0f

		// Change state if exceeding angles
		if (cannonAngles[side] >= 20.0f)					// 15.0f
			cannonStates[side] = BACKWARD_STATE;
		else if (cannonAngles[side] <= -20.0f)				// 15.0f
			cannonStates[side] = FORWARD_STATE;		
	}
}

void Spaceship::moving()
{
	movementCycle();
	fireCycle();
}

void Spaceship::fireCycle()
{
	// These if statements control the thruster fire moving forward and backwards in a pattern

	if(moveFire>20)
	{
		fireForward = false;
	}
	else if(moveFire<1)
	{
		fireForward = true;
	}

	if(fireForward == true)
	{
		moveFire++;
	}
	else
	{
		moveFire--;
	}
}

	
void Spaceship::movementCycle()
{
	if (cycleCounter == 0 || cycleCounter == 1 || cycleCounter == 6 || cycleCounter == 7)		// Move cannons one way
	{
		cannonAngles[0] += 5.0f;
		cannonAngles[1] -= 5.0f;
	}

	if (cycleCounter == 2 || cycleCounter == 3 || cycleCounter == 4 || cycleCounter == 5)		// Move cannons the other way
	{
		cannonAngles[0] -= 5.0f;
		cannonAngles[1] += 5.0f;
	}

	cycleCounter++;			// Increment cycleCounter

	if (cycleCounter > 7)	// If a cycle is finished, reset it
	{
		cycleCounter = 0;
	}
}