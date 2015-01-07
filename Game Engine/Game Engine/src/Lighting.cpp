#include "Lighting.h"

Lighting::Lighting()
{
	//light 0 properties
	//  GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1.0};
	 GLfloat light_diffuse[] = {0.5, 0.5, 0.5, 1.0};
	 GLfloat light_position[] = {0, 0, 30, 1.0}; // 4th parameter is point light yes = 1 no = 0

	 // Distance attenuation needs to be added
	
	 //ambient light properties
	 // GLfloat model_ambient[] = { 0.0, 0.0, 0.0, 1.0};

	 //enable light
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// glEnable(0x4000); 0x4000 is the same as GL_LIGHT0, this can be used to iterate through lights and setup/render them

	//give light 0 properties
	// glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0f);

	// glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

}

Lighting::~Lighting()
{

}

void Lighting::setPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	GLfloat light_position[] = {x, y, z, w};
}