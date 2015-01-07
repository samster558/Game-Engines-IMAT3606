///////////////////////////////////////////////////////////
// openGL object model loader
// Load a scene of obj files into openGL
// Campus assignment
// Kevin Iseborn P12201712
// Sam Lighton
///////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Model.h"
#include "Scene.h"
#include "Movement.h"
#include <vector>
#include <math.h>
#include <string>


#define SC_WIDTH 800
#define SC_HEIGHT 800
#define REFRESH_RATE 0.005f
using namespace std;

int main()
{
	//************************************************************
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
    //Create the main window
	sf::Window App(sf::VideoMode(SC_WIDTH, SC_HEIGHT, 32), "SFML OpenGL");    // Create a clock for measuring time elapsed
	
    sf::Clock Clock;
	
	const float rotateIncrement = 0.1f;

	//output version of OpenGL to the console
	 cout<<"OpenGL version: "<<glGetString(GL_VERSION)<<endl;
	//************************************************************
	
	Scene scene;
	scene.modelConstructor("Campus/Scene.txt");
	 
	 //light 0 properties
	 GLfloat light_ambient[] = {0.3, 0.3, 0.3, 0.3};
	 GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
	 GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
	
	 //ambient light properties
	 GLfloat model_ambient[] = { 0.2, 0.2, 0.2, 1.0};

	 //material properties
	 GLfloat mat_specular[] = {0.8, 0.6, 0.6, 1.0 };
	 GLfloat mat_shininess[] = { 100.0 };
	 glShadeModel (GL_SMOOTH);

	//Camera Properties
	GLfloat zCameraPosition = 0;
	GLfloat xCameraPosition = 0;
	GLfloat yCameraPosition = 0;

	//create movement controls
	Movement movement;
	//set initial rotate value for gluLookAt
	movement.setInitRotate(0.f,0.f);
	//*************************************************************
    //Set color and depth clear value
    glClearDepth(1.f);
    glClearColor(0.5f, 0.9f, 1.f, 1.f);
	
	//enable material
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	
	//enable light
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//give light 0 properties
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(105.f, 1.f, 1.f, 500.f);
	glEnable(GL_DEPTH_TEST);
	//************************************************************

	//Output to consol the software controls
	cout<<"DMU Campus"<<endl;
	cout<<"To Move around the scene, use W,A,S,D"<<endl;
	cout<<"To rotate the camera, hold down alt and move the mouse"<<endl;
	cout<<"To toggle between 3D and normal, press Q to activate and E to turn off"<<endl;
	cout<<"To toggle lights on and off, use Z and X"<<endl;


    // set up a bool to toggle between 3d and non
	bool threeDActive = false;

	//************************************************************
	// Start game loop
    while (App.isOpen())
    {

		//toggle 3D mode
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			if(threeDActive == false){threeDActive = true;}
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			if(threeDActive == true){threeDActive = false;}
		}


		//enable light by pressing z
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			glEnable(GL_LIGHT0);
		}
		//disable light by pressing z
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			glDisable(GL_LIGHT0);
		}

        // Process events
        sf::Event Event;
        while (App.pollEvent(Event))
        {
            // Close window : exit
            if (Event.type == sf::Event::Closed)
                App.close();

            // Escape key : exit
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
                App.close();

            // Resize event : adjust viewport
            if (Event.type == sf::Event::Resized)
                glViewport(0, 0, Event.size.width, Event.size.height);
	
        }

        // Set the active window before using OpenGL commands
        App.setActive();
		
    
		if((float)Clock.getElapsedTime().asSeconds()>REFRESH_RATE){
			// Clear colour and depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//scene.moveObjects();
			
			// Apply some transformations
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			movement.Moving();

			//Drawing Scene of object models
			if(threeDActive == false)scene.drawScene();
			if(threeDActive == true)scene.draw3D();
			
			Clock.restart();
		}

       
        // Finally, display rendered frame on screen
        App.display();
    }

    return EXIT_SUCCESS;
}
