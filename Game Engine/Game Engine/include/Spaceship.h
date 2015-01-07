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
	char legStates[2];	
	char armStates[2];

	float legAngles[2];
	float armAngles[2];

	float moveFire;				// Variable used to move the thruster fire forward and back
	bool fireForward;			// Bool to check whether the thurster fire is moving forward or back

	int walkCounter; // 0-3, first two integers (0,1) are for one movement direction last two integers (2,3) are for the other

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

	// Movement cycle for robot arms/legs, used for a walking animation
	// Not currently used
	void moveForward();
};

#endif