#ifndef __GL_COMPONENT
#define __GL_COMPONENT

#define PI 3.14159
#define TWO_PI PI*2.0
#define HALF_PI PI/2.0

#include <glm/glm.hpp>
#include "Spaceship.h"

class SpaceshipHandler
{
private:

	Spaceship* theSpaceship;		// Handler class contains a spaceship
	float rotationAngle;			// Rotation angle of the spaceship

	int m_windowWidth;
	int m_windowHeight;

	float spaceshipX, spaceshipY, spaceshipZ;		// Position values of the spaceship in (x,y,z)

public:

	SpaceshipHandler();
	virtual ~SpaceshipHandler();

	bool Init();			// Initialise the spaceship's variables
	bool Shutdown();		// Deletes the spaceship when it is no longer needed
	
	void SetupProjection(int width, int height);		// Setup the window and matrix for use with the spaceship

	void Prepare(float dt);
	void Render();			// Render the spaceship to the screen

	float getX();			// Get spaceshipX
	float getY();			// Get spaceshipY
	float getZ();			// Get spaceshipZ

	float getRotation();	// Get rotationAngle

	void TurnSpaceshipLeft(float);			// Turn the spaceship left about the y axis
	void TurnSpaceshipRight(float);			// Turn the spaceship right about the y axis

	void WalkForwards();					// Move the spaceship relative forward
	void WalkBackwards();					// Move the spaceship relative backwards
};

#endif	// SPACESHIPHANDLER_H