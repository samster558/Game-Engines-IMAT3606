#include <SFML/OpenGL.hpp>

#ifndef LIGHTING_H
#define LIGHTING_H

class Lighting
{
private:
	GLfloat light_ambient[4];
	GLfloat light_diffuse[4];
	GLfloat light_specular[4];
	GLfloat light_position[4];

	GLenum lightNumber;

	int currentLight;

public:
	Lighting();
	~Lighting();
	
	void setPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat w);		// Set the light's position

	void setLight(GLenum lightName);
	void setAmbient(GLfloat x, GLfloat y, GLfloat z, GLfloat w);		// Set the light's ambient values
	void setDiffuse(GLfloat x, GLfloat y, GLfloat z, GLfloat w);		// Set the light's diffuse values
	void setSpecular(GLfloat x, GLfloat y, GLfloat z, GLfloat w);		// Set the light's specular values

	GLenum getLightNumber();
	int getCurrentLight();
};

#endif // LIGHTING_H