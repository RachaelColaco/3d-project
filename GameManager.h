#pragma once
//
// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand
//
// (c) 2020 Media Design School
//
// File Name: GameManager.h
// Description: Game Manager declaration file
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
#include <vector>

//Local Includes
#include "ShaderLoader.h" 
#include "Camera.h"
#include "TextLabel.h"
#include "Utils.h"
#include "Tank.h"
#include "GameManager.h"
#include "Input.h"
#include "Audio.h"
#include "Enemy.h"

class GameManager
{
public:
	GameManager();
	~GameManager();
	void MainSetup();
	void Render();
	void Update();

	void ProcessInput();
	void KeyboardDown(unsigned char key, int x, int y);
	void KeyboardUP(unsigned char key, int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void ModelREF(glm::vec3 objPosition, glm::vec3 rotationAxis, glm::vec3 objScale, float rotationAngle);


private:
	Camera* CameraObject;
	Sphere* Spheremesh;
	Input* InputKey; //Inputs 
	CubeMap* cubeMap;
	Tank* TankObject;
	Enemy* Pug;
	TextLabel* label;
	Audio* Audiosystem;
};