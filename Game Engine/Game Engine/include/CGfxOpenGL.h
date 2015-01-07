#ifndef __GL_COMPONENT
#define __GL_COMPONENT

#define PI 3.14159
#define TWO_PI PI*2.0
#define HALF_PI PI/2.0

#include <glm/glm.hpp>

#include "Robot.h"

class CGfxOpenGL
{
private:
	Robot *theRobot;
	float rotationAngle;

	int m_windowWidth;
	int m_windowHeight;

	float robotX, robotY, robotZ;

public:
	CGfxOpenGL();
	virtual ~CGfxOpenGL();

	bool Init();
	bool Shutdown();
	
	void SetupProjection(int width, int height);

	void Prepare(float dt);
	void Render();

	void TurnRobotLeft(float);
	void TurnRobotRight(float);

	void WalkForward();
	void WalkBackwards();
};

#endif