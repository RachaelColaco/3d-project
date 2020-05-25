//
// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand
//
// (c) 2020 Media Design School
//
// File Name: main.cpp
// Description: main implementation file
// Author: Rachael Colaco 
// Mail: Rachael.Col8495@mediadesign.school.nz 
//

// Dependency Includes
#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include "glm.hpp" 
#include "gtc/matrix_transform.hpp" 
#include "gtc/type_ptr.hpp" 
#include <fmod.hpp>


//Library Includes
#include <iostream>

//Local Includes
#include "ShaderLoader.h" 
#include "Camera.h"
#include "TextLabel.h"
#include "Utils.h"
#include "Sphere.h"
#include "CubeMap.h"
#include "Model.h"
#include "GameManager.h"

GameManager gameManager;

void MouseClick(int button, int state, int x, int y)
{
	gameManager.MouseClick(button, state, x,  y);
}
void KeyboardDown(unsigned char key, int x, int y)
{
	gameManager.KeyboardDown(key, x, y);
}
void KeyboardUP(unsigned char key, int x, int y)
{
	gameManager.KeyboardUP(key, x, y);
}
void Render();
void Update();

int main(int argc, char** argv) {


	//SetUp and create at glut controlled window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL First Window");

	//Sets up all gl function callbacks based on pc hardware
	if (glewInit() != GLEW_OK)
	{
		//If glew set up failed then application will not run graphics correctly
		std::cout << "Glew Initialization failed. Aborting Application." << std::endl;
		system("pause");
	}
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//Sets the clear color when calling glClear()
	glClearColor(1.0, 0.0, 1.0, 1.0);//canvas will be pink



	gameManager.MainSetup();
	//Register callbacks
	glutDisplayFunc(Render);
	glutIdleFunc(Update);
	glutKeyboardFunc(KeyboardDown);
	glutKeyboardUpFunc(KeyboardUP);
	glutMouseFunc(MouseClick);


	//fxThump->release(); //For close class
	//audioSystem->release();//for close class
	glutMainLoop();//Ensure this is the last glut line called 
	return 0;
}
void Update()
{
	//updates the game manager
	gameManager.Update();
}

void Render()
{
	//render the game manager
	gameManager.Render();
}
