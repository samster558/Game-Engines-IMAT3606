#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Model.h"
#include "Scene.h"
#include "Camera.h"
#include "Lighting.h"

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

	// Lighting lightZero; // Setup in constructor


	// Camera cameraTwo;
	 
	 //material properties
	 GLfloat mat_diffuse[4] = {0.75, 0.75, 0.75, 1.0};
	 GLfloat mat_specular[] = {0.8, 0.6, 0.6, 1.0 };
	 GLfloat mat_shininess[] = { 100.0 };

	 glShadeModel (GL_SMOOTH); // Smooth or flat

	//create a camera with movement controls 
	Camera cameraOne;
	cameraOne.setPosition(0,0,-20);

	Camera cameraTwo;
	cameraTwo.setPosition(20,30,-20);

	//set initial rotate value for gluLookAt	
	cameraOne.setInitRotate(0.f,0.f);
	cameraTwo.setInitRotate(0.f,0.f);

	int activeCamera;
	activeCamera = 1;

	

	//*************************************************************
    //Set color and depth clear value
    glClearDepth(1.f);
    glClearColor(0.5f, 0.9f, 1.f, 1.f);
	
	//enable material
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

	// Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(105.f, 1.f, 1.f, 500.f);
	glEnable(GL_DEPTH_TEST);

	//************************************************************

	//Output to console the software controls
	cout<<"DMU Campus"<<endl;
	cout<<"To Move around the scene, use W,A,S,D"<<endl;
	cout<<"To rotate the camera, hold down alt and move the mouse"<<endl;
	cout<<"To toggle lights on and off, use Z and X"<<endl;

	//************************************************************
	// Start game loop
    while (App.isOpen())
    {
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			if(activeCamera == 1)
			{
				activeCamera = 2;
			}
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::V))
		{
			if(activeCamera == 2)
			{
				activeCamera = 1;
			}	
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
			if(activeCamera == 1)
			{
				cameraOne.Moving();
			}
			else if(activeCamera == 2)
			{
				cameraTwo.Moving();
			}
			else
			{
				std::cout << "no active camera detected" << endl;
			}

			//Drawing Scene of object models
			scene.drawScene();
			
			
			Clock.restart();
		}

       
        // Finally, display rendered frame on screen
        App.display();
    }

    return EXIT_SUCCESS;
}
