/**
@file Scene.h
*/

#ifndef SCENE_H
#define SCENE_H

#include "Model.h"
#include "StereoCamera.h"

#include "tinyxml.h"

class Scene
{
private:
	std::vector<Model> modelVector; // Vector of models
	TiXmlDocument doc;
	TiXmlElement* root;

public:
	Scene();								 // Constructor
	bool modelConstructor(string filename);	 // Create all models and load them into the vector
	void loadAttributesFromElement(TiXmlElement* element);
	void drawScene();						 // Draw all the models in the vector
};



#endif