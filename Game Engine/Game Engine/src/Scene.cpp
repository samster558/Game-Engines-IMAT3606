#include "Scene.h"

Scene::Scene()
{
	
}

bool Scene::modelConstructor(string filename)
{
	ifstream sceneFile;
	string inputLine;
	string modelFile;
	string textureString;
	stringstream ss;

	float tx,ty,tz;
	float rx,ry,rz;
	float sx,sy,sz;

	sceneFile.open(filename);

	if(!sceneFile.is_open())
	{
		cout<<"file not found"<<endl;
		return false;
	}

	while(!sceneFile.eof())
	{
		getline(sceneFile, inputLine);
		ss.str("");
		ss.clear();
		
		
		ss.str(inputLine);
		ss>>modelFile>>tx>>ty>>tz>>rx>>ry>>rz>>sx>>sy>>sz>>textureString;

		Model m(tx,ty,tz,rx,ry,rz,sx,sy,sz);
		m.loadTexture(textureString);
		m.loadModel(modelFile);
		modelVector.push_back(m);

	} return true;
}

void Scene::drawScene()
{
	
	int vectorSize = modelVector.size();
	std::vector<Model>::iterator i;
	
	for( i = modelVector.begin(); i != modelVector.end(); ++i)
	{
		i->draw();
	}
	
}

void Scene::draw3D()
{
	int vectorSize = modelVector.size();
	std::vector<Model>::iterator i;

	//Red 
	for( i = modelVector.begin(); i != modelVector.end(); ++i)
	{
	 
	    // Set up the stereo camera system
			static StereoCamera cam(
	        2000.0f,     // Convergence
	        1.f,       // Eye Separation
			1.3333f,     // Aspect Ratio	        
			45.0f,       // FOV along Y in degrees
	        10.0f,       // Near Clipping Distance
	        20000.0f);   // Far Clipping Distance
	 
	    cam.ApplyLeftFrustum();
	    glColorMask(true, false, false, false);
		i->draw();

	}

	//Blue
	for( i = modelVector.begin(); i != modelVector.end(); ++i)
	{
		glClear(GL_DEPTH_BUFFER_BIT);

		// Set up the stereo camera system
			static StereoCamera cam(
	        2000.0f,     // Convergence
	        1.f,       // Eye Separation
			1.3333f,     // Aspect Ratio	        
			45.0f,       // FOV along Y in degrees
	        10.0f,       // Near Clipping Distance
	        20000.0f);   // Far Clipping Distance
 
	    cam.ApplyRightFrustum();
	    glColorMask(false, true, true, false);

		i->draw();

		glColorMask(true, true, true, true);
	} 

}