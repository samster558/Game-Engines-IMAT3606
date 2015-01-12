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

int main()
{
	//************************************************************
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
    // Create the main window
	sf::RenderWindow App(sf::VideoMode(SC_WIDTH, SC_HEIGHT, 32), "Game Engine");    

	App.setFramerateLimit(60);

	// Create a clock for measuring time elapsed
    sf::Clock Clock;
	
	const float rotateIncrement = 0.1f;

	// Output version of OpenGL to the console
	 cout<<"OpenGL version: "<<glGetString(GL_VERSION)<<endl;

	//************************************************************
	
	// Create a Scene and load in the models from the XML file
	Scene scene;
	scene.modelConstructor("scene/XML/level1.xml");

	// Create some strings to make using the getComponent functions quicker and clearer
	std::string camera = "Camera";
	std::string collidable= "Collidable";
	std::string light = "Lighting";
	std::string mortality = "Mortality";
	std::string spaceshipHandler = "SpaceshipHandler";
	std::string weapon = "Weapon";

	// Create an enum of states for switching between menus and levels
	enum States {mainMenu, splashScreen, playingLevel, pause};
	int gameState = mainMenu;

	//*************************************************************

	// Lighting
	
	GameObject lightZero;
	lightZero.setComponent(light);
	lightZero.getLight()->setLight(GL_LIGHT0);
	lightZero.getLight()->setPosition(10.0f, 0.0f, -50.0f, 1.0f);
	lightZero.getLight()->setAmbient(1.0f, 0.0f, 0.0f, 1.0f);
	lightZero.getLight()->setDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
	
	GameObject lightOne;
	lightOne.setComponent(light);
	lightOne.getLight()->setLight(GL_LIGHT1);
	lightOne.getLight()->setPosition(-10.0f, 0.0f, -50.0f, 1.0f);
	lightOne.getLight()->setAmbient(0.0f, 1.0f, 0.0f, 1.0f);
	lightOne.getLight()->setDiffuse(0.0f, 1.0f, 0.0f, 1.0f);
	
	//*************************************************************

	// Splashscreen

	sf::Sprite splashSprite;
	sf::Image splashImage;
	sf::Texture splashTexture;

	splashImage.loadFromFile("graphics/Space Shooter Logo.png");
	splashImage.createMaskFromColor(sf::Color(255,255,255,255));
	 
	splashTexture.loadFromImage(splashImage);
	splashSprite.setTexture(splashTexture);
	splashSprite.setPosition(150,300);

	bool alphaGoingUp;			// Bool for whether the alpha value is increasing or decreasing
	alphaGoingUp = false;		// Set alpha to be decreasing at first
	int i;						// Used as a variable for the blackRectangle's alpha value
	i=245;						// Set the alpha high at first to cover the splashscreen

	sf::RectangleShape blackRectangle;		// Used for fading splashscreen in and out
	blackRectangle.setSize(sf::Vector2f(700,700));
	blackRectangle.setFillColor(sf::Color(255,0,0,i));
	blackRectangle.setPosition(0,0);

	//*************************************************************

	// Camera Setup
	
	// Create three different cameras and initialise their position and rotation
	GameObject firstPersonCamera;
	firstPersonCamera.setComponent(camera);
	firstPersonCamera.getCamera()->setPosition(0,0,0);
	firstPersonCamera.getCamera()->setInitRotate(0.f,0.f);

	GameObject thirdPersonCamera;
	thirdPersonCamera.setComponent(camera);
	thirdPersonCamera.getCamera()->setPosition(0,0,-20);
	thirdPersonCamera.getCamera()->setInitRotate(0.f,0.f);

	GameObject freeCamera;
	freeCamera.setComponent(camera);
	freeCamera.getCamera()->setPosition(20,30,-20);
	freeCamera.getCamera()->setInitRotate(0.f,0.f);

	// Variable to store which camera is currently being used
	int activeCamera;
	activeCamera = 1;

	//*************************************************************

	// Spaceship setup

	GameObject player;

	player.setComponent(mortality);						// Give the player a mortality component
	player.getMortality()->setHealth(100);				// Set the player's health to 100

	player.setComponent(spaceshipHandler);				// Give the player a spaceshipHandler component
	player.getSpaceshipHandler()->SetupProjection(SC_WIDTH, SC_HEIGHT);		// Setup the viewing projection
	player.getSpaceshipHandler()->Init();				// Initialise the player's spaceship and associated variables

	//*************************************************************

	// Material setup

    // Set color and depth clear value
    glClearDepth(1.f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	 // Material properties
	 GLfloat mat_diffuse[] = {0.75, 0.75, 0.75, 1.0};
	 GLfloat mat_specular[] = {0.6, 0.6, 0.6, 1.0 };
	 GLfloat mat_shininess[] = { 100.0 };

	 glShadeModel (GL_SMOOTH); // Smooth or flat
	
	// Enable material
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);
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

	// Text Messages/UI setup

	std::string stringOfMessages[5]; // Array to hold the string messages seen on the screen
	sf::Font gameFont; // The font used for the game
	sf::Text message[5]; // The text messages used for the game

	int score = 0;
	int lives = 3;

	 // Initialise the messages
	stringOfMessages[0] = "Space Shooter";
	stringOfMessages[1] = "Score: " +std::to_string(score);
	stringOfMessages[2] = "Lives: " +std::to_string(lives);
	stringOfMessages[3] = "Paused";
	stringOfMessages[4] = "Press G to play";

	// Load the font for the text
	gameFont.loadFromFile("./fonts/Acknowtt.ttf");

	// Set the font and character size of the messages
	for (int i=0; i<5; i++)
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
	message[4].setPosition(10,40);

	//************************************************************

	// Output to console the software controls
	cout << endl << "Space Shooter" << endl;
	cout << endl << "Press G to start" << endl << endl;
	cout << "Use Q and E to turn the spaceship" << endl;
	cout << "Use W and S to move the spaceship forward and back" << endl;
	cout << "Use C, V and B to switch between the three cameras" << endl;
	cout << "Use P and O to pause and unpause the game" << endl << endl;
	cout << "To rotate the free camera, hold down the left mouse button and move the mouse" << endl;
	cout << "To pan the free camera, hold down the right mouse button and move the mouse" << endl;
	cout << "To zoom the free camera, use the up and down keys" << endl;
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
			// Push GL States to preserve them
			App.pushGLStates();

			// Display title message
			App.draw(message[0]);
			App.draw(message[4]);

			// Pop GL States when we have finished drawing the messages
			App.popGLStates();

			// Finally, display rendered frame on screen
			App.display();

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))		// Start the game from the menu
			{
				gameState = splashScreen;		
			}
		}

		if(gameState == splashScreen)
		{
			// Clear the screen
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// If statements used to make the splashscreen fade in and out
			if(i>245)
			{
				Sleep(500);
				gameState = playingLevel;
			}
			if(i<1)
			{
				Sleep(1500);
				alphaGoingUp = true;
			}
			if(alphaGoingUp == false)
			{
				i--;
			}
			else
			{
				i++;
			}

			// Push GL States to preserve them
			App.pushGLStates();

			// Draw the splashscreen
			App.draw(splashSprite);

			// Set the transparency of the blackRectangle to be variable
			blackRectangle.setFillColor(sf::Color(0,0,0,i));

			// Draw the blackRectangle that initially covers the splashscreen
			App.draw(blackRectangle);

			// Pop GL States when we have finished drawing the messages
			App.popGLStates();

			// Finally, display rendered frame on screen
			App.display();
		}

		if(gameState == pause)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// Push GL States to preserve them
			App.pushGLStates();

			// Draw the pause message
			App.draw(message[3]);
			
			// Pop GL States when we have finished drawing the messages
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
			player.getSpaceshipHandler()->WalkForwards();
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))		// Move backwards
		{
			player.getSpaceshipHandler()->WalkBackwards();
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))		// Turn left
		{
			player.getSpaceshipHandler()->TurnSpaceshipLeft(2.5);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))		// Turn right
		{
			player.getSpaceshipHandler()->TurnSpaceshipRight(2.5);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))		// Pause the game
		{
			gameState = pause;
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))		// Switch to the first camera
		{
			if(activeCamera == 2 || activeCamera == 3)
			{
				activeCamera = 1;
			}
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::V))		// Switch to the second camera
		{
			if(activeCamera == 1 || activeCamera == 3)
			{
				activeCamera = 2;
			}	
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))		// Switch to the third (free) camera
		{
			if(activeCamera == 1 || activeCamera == 2)
			{
				activeCamera = 3;
			}	
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))		// Enable lighting
		{
			glEnable(GL_LIGHTING);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))		// Disable lighting
		{
			glDisable(GL_LIGHTING);
		}

        // Set the active window before using OpenGL commands
        App.setActive();
		
		if((float)Clock.getElapsedTime().asSeconds()>REFRESH_RATE){

			// Clear colour and depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			// Apply some transformations
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			// If the third person camera is the active camera, set its position and target to follow the player's spaceship
			if(activeCamera == 1)
			{
				thirdPersonCamera.getCamera()->setPosition(player.getSpaceshipHandler()->getX(), player.getSpaceshipHandler()->getY()+10, player.getSpaceshipHandler()->getZ()+15);
				thirdPersonCamera.getCamera()->setTarget(player.getSpaceshipHandler()->getX(), player.getSpaceshipHandler()->getY(), player.getSpaceshipHandler()->getZ());
				thirdPersonCamera.getCamera()->update();
			}
			// If the first person camera is the active camera, set its position and target at the front of the player's spaceship
			else if(activeCamera == 2)
			{
				firstPersonCamera.getCamera()->setPosition(player.getSpaceshipHandler()->getX(), player.getSpaceshipHandler()->getY()+5, player.getSpaceshipHandler()->getZ());
				firstPersonCamera.getCamera()->setTarget(player.getSpaceshipHandler()->getX(), player.getSpaceshipHandler()->getY(), player.getSpaceshipHandler()->getZ()-25);
				firstPersonCamera.getCamera()->update();
			}
			// If the free camera is the active camera, check for any movement controls that have been input and update the camera
			else if(activeCamera == 3)
			{
				freeCamera.getCamera()->moving();
				freeCamera.getCamera()->update();
			}
			else
			{
				std::cout << "no active camera detected" << endl;
			}

			// Draw the stars in the background
			glBegin(GL_POINTS);
			glColor3f(1.0f, 1.0f, 1.0f);
			for(int a = -650; a < 650; a+=80)
			{
				for(int b = -500; b < 300; b+=80)
				{
				glVertex3f(a, b, -500);
				}
			}
			glEnd();
			
			// Draw Scene of object models
			scene.drawScene();

			// Draw Spaceship
			player.getSpaceshipHandler()->Render();

			// Push GL States to preserve them
			App.pushGLStates();

			// Draw the UI messages
			for(int i=0; i<3; i++)
			{
				App.draw(message[i]);
			}
			
			// Pop GL States when we have finished drawing the messages
			App.popGLStates();

			// Restart the clock
			Clock.restart();
		}

        // Finally, display rendered frame on screen
        App.display();
    }

   }

   	// Delete the SpaceshipHandler component
	delete player.getSpaceshipHandler();

    return EXIT_SUCCESS;
}
