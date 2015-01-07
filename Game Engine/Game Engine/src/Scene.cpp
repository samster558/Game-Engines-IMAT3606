#include "Scene.h"

Scene::Scene()
{
	
}

bool Scene::modelConstructor(string filename)
{
	ifstream sceneFile;

	sceneFile.open(filename);

	if(!sceneFile.is_open())
	{
		cout<<"file not found"<<endl<<endl;
		return false;
	}


	if(!doc.LoadFile("src/test.xml"))
	{
		cerr << doc.ErrorDesc() << endl;
		return EXIT_FAILURE;	// 1
	}

	root = doc.FirstChildElement();
	if(root == NULL)
	{
		cerr << "Failed to load file: No root element."
				<< endl;
		doc.Clear();
		return 2;
	}

	for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		loadAttributesFromElement(elem);
	}

}

void Scene::loadAttributesFromElement(TiXmlElement* element)
{
	string modelFile;
	string textureString = "default no texture";

	float tx,ty,tz = 0;				// create translate x,y,z variables and set their default values
	float rx,ry,rz = 0;				// create rotate x,y,z variables and set their default values
	float sx,sy,sz = 1;				// create scale x,y,z variables and set their default values

	string elemName = element->Value();

	const char* attr;

	// Set each attribute from the XML file to a specific variable

	attr = element->Attribute("modelFileLocation");
	if(attr != NULL)
	{
		cout << elemName << " modelFileLocation is " << attr << endl;

		modelFile = attr;
	}
	else         // If there is no model file location then exit the function
	{
		cout << elemName << " no model found" << endl << endl;
		return;
	}

	attr = element->Attribute("xTranslate");
	if(attr != NULL)
	{
		cout << elemName << " xTranslate is " << attr << endl;

		double temp;

		attr = element->Attribute("xTranslate", &temp);

		tx = temp;
	}
				

	attr = element->Attribute("yTranslate");
	if(attr != NULL)
	{
		cout << elemName << " yTranslate " << attr << endl;

		double temp;

		attr = element->Attribute("yTranslate", &temp);

		ty = temp;
	}
				

	attr = element->Attribute("zTranslate");
	if(attr != NULL)
	{
		cout << elemName << " zTranslate is " << attr << endl;

		double temp;

		attr = element->Attribute("zTranslate", &temp);

		tz = temp;
	}
				

	attr = element->Attribute("xRotate");
	if(attr != NULL)
	{
		cout << elemName << " xRotate is " << attr << endl;

		double temp;

		attr = element->Attribute("xRotate", &temp);

		rx = temp;
	}
				

	attr = element->Attribute("yRotate");
	if(attr != NULL)
	{
		cout << elemName << " yRotate is " << attr << endl;

		double temp;

		attr = element->Attribute("yRotate", &temp);

		ry = temp;
	}
				

	attr = element->Attribute("zRotate");
	if(attr != NULL)
	{
		cout << elemName << " zRotate is " << attr << endl;

		double temp;

		attr = element->Attribute("zRotate", &temp);

		rz = temp;
	}
				

	attr = element->Attribute("xScale");
	if(attr != NULL)
	{
		cout << elemName << " xScale is " << attr << endl;

		double temp;

		attr = element->Attribute("xScale", &temp);

		sx = temp;
	}
				

	attr = element->Attribute("yScale");
	if(attr != NULL)
	{
		cout << elemName << " yScale is " << attr << endl;

		double temp;

		attr = element->Attribute("yScale", &temp);

		sy = temp;
	}
				
	attr = element->Attribute("zScale");
	if(attr != NULL)
	{
		cout << elemName << " zScale is " << attr << endl;

		double temp;

		attr = element->Attribute("zScale", &temp);

		sz = temp;
	}
				

	attr = element->Attribute("textureFileLocation");
	if(attr != NULL)
	{
		cout << elemName << " textureFileLocation is " << attr << endl << endl;

		textureString = attr;
	}

	// Using the variables from the XML file,
	// or the defaults if attributes are missing,
	// create a model

	Model m(tx,ty,tz,rx,ry,rz,sx,sy,sz);

	// Load the model's obj and texture file, and push it onto the modelVector

	m.loadTexture(textureString);
	// m.loadModel(modelFile);

	// If the model loading succeeded, then push the model onto the model vector;
	if(m.loadModel(modelFile))
	{
	modelVector.push_back(m);
	}
			
}

void Scene::drawScene()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	int vectorSize = modelVector.size();
	std::vector<Model>::iterator i;
	
	for( i = modelVector.begin(); i != modelVector.end(); ++i)
	{
		i->draw();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);

}