#pragma

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include "Camera.h"
#include "Collidable.h"
#include "Lighting.h"
#include "Mortality.h"
#include "SpaceshipHandler.h"
#include "Weapon.h"

class GameObject
{
private:

	Camera* m_camera;							// Add a camera component to the GameObject
	Collidable* m_collidable;					// Add a collidable component to the GameObject
	Lighting* m_lighting;						// Add a lighting component to the GameObject
	Mortality* m_mortality;						// Add a mortality component to the GameObject (i.e life/death)
	SpaceshipHandler* m_spaceshipHandler;		// Add a spaceshipHandler component to the GameObject (contains a spaceship)
	Weapon* m_weapon;							// Add a weapon component to the GameObject

public:

	GameObject();
	~GameObject();

	// Getter functions to access components
	Camera* getCamera();
	Collidable* getCollidable();
	Lighting* getLight();
	Mortality* getMortality();
	SpaceshipHandler* getSpaceshipHandler();
	Weapon* getWeapon();
	

	// Setter function to set components
	void setComponent(std::string componentName);
};

#endif // GAMEOBJECT_H