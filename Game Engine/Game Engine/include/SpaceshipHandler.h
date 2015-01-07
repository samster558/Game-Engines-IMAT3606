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
	Spaceship* theSpaceship;
	float rotationAngle;

	int m_windowWidth;
	int m_windowHeight;

	float spaceshipX, spaceshipY, spaceshipZ;

public:
	SpaceshipHandler();
	virtual ~SpaceshipHandler();

	bool Init();
	bool Shutdown();
	
	void SetupProjection(int width, int height);

	void Prepare(float dt);
	void Render();

	void TurnSpaceshipLeft(float);
	void TurnSpaceshipRight(float);

	void WalkForward();
	void WalkBackwards();
};

#endif