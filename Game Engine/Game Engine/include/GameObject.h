#pragma

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Animatable.h"
#include "Collidable.h"
#include "Controllable.h"
#include "Mortality.h"
#include "Movable.h"
#include "Renderable.h"
#include "Transform.h"
#include "Weapon.h"
#include "Lighting.h"


class GameObject
{
protected:

	Animatable* m_animatable;
	Collidable* m_collidable;
	Controllable* m_controllable;
	Mortality* m_mortality;
	Movable* m_movable;
	Renderable* m_renderable;
	Transform* m_transform;
	Weapon* m_weapon;
	
	Lighting* m_lighting;

public:
	GameObject();
	~GameObject();

	// Getter functions to access components

	// Setter functions to set components

	void setLightingComponent();

	// Initalise functions set the default component pointers for entities in the game

	void initPlayer();
	void initEnemyAlpha();
	void initEnemyBeta();
	void initRock();

};

#endif // GAMEOBJECT_H