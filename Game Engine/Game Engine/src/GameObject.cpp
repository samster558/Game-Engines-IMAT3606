#include "GameObject.h"

GameObject::GameObject()
{
	// Components are set to null pointers by default
	m_camera = nullptr;
	m_collidable = nullptr;
	m_lighting = nullptr;
	m_mortality = nullptr;
	m_spaceshipHandler = nullptr;
	m_weapon = nullptr;
}

GameObject::~GameObject()
{

}

Camera* GameObject::getCamera()
{
	if(m_camera != nullptr)
	{
		return m_camera;
	}
}

Collidable* GameObject::getCollidable()
{
	if(m_collidable != nullptr)
	{
		return m_collidable;
	}
}

Lighting* GameObject::getLight()
{
	if(m_lighting != nullptr)
	{
		return m_lighting;
	}
}

Mortality* GameObject::getMortality()
{
	if(m_mortality != nullptr)
	{
		return m_mortality;
	}
}

SpaceshipHandler* GameObject::getSpaceshipHandler()
{
	if(m_spaceshipHandler != nullptr)
	{
		return m_spaceshipHandler;
	}
}

Weapon* GameObject::getWeapon()
{
	if(m_weapon != nullptr)
	{
		return m_weapon;
	}
}

void GameObject::setComponent(std::string componentName)
{
	if(componentName == "Camera")
	{
		m_camera = new Camera;
	}

	if(componentName == "Collidable")
	{
		m_collidable = new Collidable;
	}

	if(componentName == "Lighting")
	{
		m_lighting = new Lighting;
	}

	if(componentName == "Mortality")
	{
		m_mortality = new Mortality;
	}

	if(componentName == "SpaceshipHandler")
	{
		m_spaceshipHandler = new SpaceshipHandler;
	}

	if(componentName == "Weapon")
	{
		m_weapon = new Weapon;
	}
}

