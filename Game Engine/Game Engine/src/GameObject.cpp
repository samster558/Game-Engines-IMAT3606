#include "GameObject.h"

GameObject::GameObject()
{
	m_animatable = nullptr;
	m_collidable = nullptr;
	m_controllable = nullptr;
	m_mortality = nullptr;
	m_movable = nullptr;
	m_renderable = nullptr;
	m_weapon = nullptr;

	m_lighting = nullptr;

	// Transform contains the x and y co-ordinates that will be used by other components
	// It will need to be set for almost everything

	m_transform = nullptr;	

	// First and third person camera
	
}

GameObject::~GameObject()
{

}