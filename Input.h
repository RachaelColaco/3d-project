
#pragma once
//
// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand
//
// (c) 2020 Media Design School
//
// File Name: Input.h
// Description: Input declaration file
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

enum InputState
{
	INPUT_UP,
	INPUT_DOWN,
	INPUT_UP_FIRST,
	INPUT_DOWN_FIRST,
};


class Input
{
public:


	Input() {};
	~Input() {};
	void KeyDown(unsigned char key, int x, int y);
	void KeyUP(unsigned char key, int x, int y);
	void MouseClick(int button, int state, int x, int y);

	bool IsKeyDown(unsigned char key);
	bool IsKeyUp(unsigned char key);
	bool IsMouseClick(int button);

	void Mouseprocess();

private:
	InputState KeyState[255] = {};
	InputState MouseState[3] = {};

};

