#ifndef __SPACESHIP_H
#define __SPACESHIP_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

// Constants for arm and leg movement states
const char BACKWARD_STATE = 0;
const char FORWARD_STATE  = 1;

// Index constants for accessing arm (red block) and leg (yellow block) array data
const char LEFT  = 0;
const char RIGHT = 1;

class Spaceship
{
private:
	char cannonStates[2];	
	char wingStates[2];

	float cannonAngles[2];
	float wingAngles[2];

	float moveFire;				// Variable used to move the thruster fire forward and back
	bool fireForward;			// Bool to check whether the thurster fire is moving forward or back

	int cycleCounter; // 0-3, first two integers (0,1) are for one movement direction last two integers (2,3) are for the other

	// Draws a unit cube
	void DrawCube(float xPos, float yPos, float zPos);

	// methods to draw the parts of the spaceship
	void DrawWing(float xPos, float yPos, float zPos);
	void DrawCockpit(float xPos, float yPos, float zPos);
	void DrawBody(float xPos, float yPos, float zPos);
	void DrawCannon(float xPos, float yPos, float zPos);
	void DrawThruster(float xPos, float yPos, float zPos);
	void DrawFire(float xPos, float yPos, float zPos);

public:

	Spaceship();
	virtual ~Spaceship();

	// Draws the entire spaceship
	void DrawSpaceship();

	// Updates the spaceship data
	void Prepare(float dt);

	// Contains functions to execute when the spaceship moves forwards or backwards
	void moving();

	// Movement cycle for the spaceship's cannons, used to animate the cannons as the spaceship moves
	void movementCycle();

	// Movement cycle for the spaceship's fire block which moves it forwards and backwards
	void fireCycle();
};

#endif