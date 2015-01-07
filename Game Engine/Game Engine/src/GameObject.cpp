#include "GameObject.h"

GameObject::GameObject()
{
	m_camera = nullptr;
	m_lighting = nullptr;
	m_mortality = nullptr;
	m_spaceshipHandler = nullptr;
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


void GameObject::setComponent(std::string componentName)
{
	
	if(componentName == "Camera")
	{
		m_camera = new Camera;
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
}

