#include <SFML/OpenGL.hpp>

#ifndef LIGHTING_H
#define LIGHTING_H

class Lighting
{
private:


public:
	Lighting();
	~Lighting();
	
	void setPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat w);		// Set the light's position
};

#endif // LIGHTING_H