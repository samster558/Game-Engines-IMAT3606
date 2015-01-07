/**
@file Scene.h
*/

#ifndef SCENE_H
#define SCENE_H

#include "Model.h"
#include "StereoCamera.h"

class Scene
{
private:

	std::vector<Model> modelVector; // Vector of models


public:
	Scene();								 // Constructor
	bool modelConstructor(string filename);	 // Create all models and load them into the vector
	void drawScene();						 // Draw all the models in the vector
	void draw3D();							 // Draw all the models in 3D
};



#endif