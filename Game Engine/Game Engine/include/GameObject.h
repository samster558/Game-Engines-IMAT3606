#pragma

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>

#include "Animatable.h"
#include "Camera.h"
#include "Collidable.h"
#include "Controllable.h"
#include "Mortality.h"
#include "Movable.h"
#include "Renderable.h"
#include "Transform.h"
#include "Weapon.h"
#include "Lighting.h"
#include "SpaceshipHandler.h"



class GameObject
{
protected:

	Camera* m_camera;							// Add a camera to the GameObject
	Lighting* m_lighting;						// Add a light to the GameObject
	Mortality* m_mortality;						// Add mortality to the GameObject (i.e life/death)
	SpaceshipHandler* m_spaceshipHandler;		// The handler class has a robot

public:
	GameObject();
	~GameObject();

	// Getter functions to access components

	Lighting* getLight();
	Camera* getCamera();
	SpaceshipHandler* getSpaceshipHandler();
	Mortality* getMortality();

	// Setter functions to set components

	void setComponent(std::string componentName);
	void setLightingComponent();
};

#endif // GAMEOBJECT_H