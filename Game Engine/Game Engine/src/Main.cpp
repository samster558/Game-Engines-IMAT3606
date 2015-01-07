#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Model.h"
#include "Scene.h"
#include "Camera.h"
#include "Lighting.h"
#include "GameObject.h"

#include "SpaceshipHandler.h"
#include "Spaceship.h"

#include <vector>
#include <math.h>
#include <string>

#define SC_WIDTH 800
#define SC_HEIGHT 800
#define REFRESH_RATE 0.005f
using namespace std;

SpaceshipHandler *g_glRender = NULL;

int main()
{
	//************************************************************
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
    //Create the main window
	sf::RenderWindow App(sf::VideoMode(SC_WIDTH, SC_HEIGHT, 32), "Game Engine");    
	//sf::RenderWindow window(sf::VideoMode(SC_WIDTH, SC_HEIGHT), "Dave The Plumber"); // Open main window 

	// Create a clock for measuring time elapsed
    sf::Clock Clock;
	
	const float rotateIncrement = 0.1f;

	//output version of OpenGL to the console
	 cout<<"OpenGL version: "<<glGetString(GL_VERSION)<<endl;
	//************************************************************

	 enum States {mainMenu, playingLevel, pause};
	 int gameState = mainMenu;

	//************************************************************
	Scene scene;
	scene.modelConstructor("scene/XML/level1.xml");

	GameObject lightZero;
	//	lightZero.m_lighting->setPosition(0,0,0,0);

	// Camera cameraTwo;
	 
	 //material properties
	 GLfloat mat_diffuse[4] = {0.75, 0.75, 0.75, 1.0};
	 GLfloat mat_specular[] = {0.6, 0.6, 0.6, 1.0 };
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
	// SpaceshipSetup

	g_glRender = new SpaceshipHandler;

	g_glRender->SetupProjection(SC_WIDTH, SC_HEIGHT);

	g_glRender->Init();

	//*************************************************************
    //Set color and depth clear value
    glClearDepth(1.f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
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

	std::string stringOfMessages[4]; // Array to hold the string messages seen on the screen
	sf::Font gameFont; // The font used for the game
	sf::Text message[4]; // The text messages used for the game

	int score = 0;
	int lives = 3;

	 // Initialise the messages

	stringOfMessages[0] = "Space Shooter";
	stringOfMessages[1] = "Score: " +std::to_string(score);
	stringOfMessages[2] = "Lives: " +std::to_string(lives);
	stringOfMessages[3] = "Paused";

	// Load the font for the text

	gameFont.loadFromFile("./fonts/Acknowtt.ttf");

	// Set the font and character size of the messages

	for (int i=0; i<4; i++)
	{
		 message[i].setFont(gameFont);
		 message[i].setCharacterSize(30);
		 message[i].setString(stringOfMessages[i]);
	}

	// Set the positions of the messages

	message[0].setPosition(10,5);
	message[1].setPosition(10,75);
	message[2].setPosition(10,40);
	message[3].setPosition(350,350);

	//************************************************************

	// Output to console the software controls
	cout << endl << "Space Shooter" << endl;
	cout << endl << "Press G to start" << endl << endl;
	cout << "Use Q and E to turn the spaceship" << endl;
	cout << "Use W and S to move the spaceship forward and back" << endl;
	cout << "Use C and V to switch between camera one and two" << endl;
	cout << "Use P and O to pause and unpause the game" << endl << endl;
	cout << "To rotate the camera, hold down the left mouse button and move the mouse" << endl;
	cout << "To pan the camera, hold down the right mouse button and move the mouse" << endl;
	cout << "To zoom the camera, use the up and down keys" << endl;
	cout << "To toggle lights on and off, use Z and X" << endl;

	//************************************************************
	// Start game loop
    while (App.isOpen())
    {
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

		if(gameState == mainMenu)
		{
			// push GL States to preserve them
			App.pushGLStates();

			App.draw(message[0]);
			
			// pop GL States when we have finished drawing the messages
			App.popGLStates();

			  // Finally, display rendered frame on screen
			App.display();

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))		// Start the game
			{
				gameState = playingLevel;
			}
		}

		if(gameState == pause)
		{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// push GL States to preserve them
			App.pushGLStates();

			// display pause message
			App.draw(message[3]);
			
			// pop GL States when we have finished drawing the messages
			App.popGLStates();

			App.display();

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))		// Unpause
			{
				gameState = playingLevel;
			}
		}
	
	 if(gameState == playingLevel)
	 {
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))		// Move forward
		{
			g_glRender->WalkForward();
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))		// Move backwards
		{
			g_glRender->WalkBackwards();
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))		// Turn left
		{
			g_glRender->TurnSpaceshipLeft(0.2);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))		// Turn right
		{
			g_glRender->TurnSpaceshipRight(0.2);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))		// Pause the game
		{
			gameState = pause;
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))		// Switch to the second camera
		{
			if(activeCamera == 1)
			{
				activeCamera = 2;
			}
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::V))		// Switch to the first camera
		{
			if(activeCamera == 2)
			{
				activeCamera = 1;
			}	
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))		// Enable light zero
		{
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))		// Disable light zero
		{
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
		}

        // Set the active window before using OpenGL commands
        App.setActive();
		
		if((float)Clock.getElapsedTime().asSeconds()>REFRESH_RATE){
			// Clear colour and depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
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
			
			// Draw Scene of object models
			 scene.drawScene();

			// Draw Spaceship
			g_glRender->Render();

			// push GL States to preserve them
			App.pushGLStates();

			// Draw the UI messages
			for(int i=0; i<3; i++)
			{
				App.draw(message[i]);
			}
			
			// pop GL States when we have finished drawing the messages
			App.popGLStates();

			// Restart the clock
			Clock.restart();
		}

        // Finally, display rendered frame on screen
        App.display();
    }

   }
	delete g_glRender;

    return EXIT_SUCCESS;
}
