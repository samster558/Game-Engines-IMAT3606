#include "Lighting.h"

Lighting::Lighting()
{
	// Set the default light values

	light_ambient[0] = 0.3f;
	light_ambient[1] = 0.3f;
	light_ambient[2] = 0.3f;
	light_ambient[3] = 1.0f;

	light_diffuse[0] = 0.5f;
	light_diffuse[1] = 0.5f;
	light_diffuse[2] = 0.5f;
	light_diffuse[3] = 1.0f;

	light_specular[0] = 0.0f;
	light_specular[1] = 0.0f;
	light_specular[2] = 0.0f;
	light_specular[3] = 1.0f;

	light_position[0] = 0.0f;
	light_position[1] = 0.0f;
	light_position[2] = 0.0f;
	light_position[3] = 1.0f;

	/*
	glEnable(lightNumber);
	glLightfv(lightNumber, GL_AMBIENT, light_ambient);
	glLightfv(lightNumber, GL_DIFFUSE, light_diffuse);
	glLightfv(lightNumber, GL_SPECULAR, light_specular);
	glLightfv(lightNumber, GL_POSITION, light_position);
	glLightf(lightNumber, GL_CONSTANT_ATTENUATION,  0.8f);
	*/

}

Lighting::~Lighting()
{

}

GLenum Lighting::getLightNumber()
{
	return lightNumber;
}

void Lighting::setPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	light_position[0] = x;
	light_position[1] = y;
	light_position[2] = z;
	light_position[3] = w;
}

void Lighting::setLight(GLenum lightName)
{
	lightNumber = lightName;
}

void Lighting::setAmbient(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	light_ambient[0] = x;
	light_ambient[1] = y;
	light_ambient[2] = z;
	light_ambient[3] = w;
}

void Lighting::setDiffuse(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	light_diffuse[0] = x;
	light_diffuse[1] = y;
	light_diffuse[2] = z;
	light_diffuse[3] = w;
}

void Lighting::setSpecular(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	light_specular[0] = x;
	light_specular[1] = y;
	light_specular[2] = z;
	light_specular[3] = w;
}