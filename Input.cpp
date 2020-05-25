//
// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand
//
// (c) 2020 Media Design School
//
// File Name: Input.cpp
// Description: Input implementation file
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


//Local Includes
#include "Input.h"

//checks on the keys and inputs down
void Input::KeyDown(unsigned char key, int x, int y)
{
	KeyState[key] = INPUT_DOWN;
}
//checks on the keys and inputs up
void Input::KeyUP(unsigned char key, int x, int y)
{
	KeyState[key] = INPUT_UP;
}

void Input::MouseClick(int button, int state, int x, int y)
{
	if (button >= 3)
		return;

	MouseState[button] = (state == GLUT_DOWN) ? INPUT_DOWN : INPUT_UP;
}
//is the key input down
bool Input::IsKeyDown(unsigned char key)
{
	if (KeyState[key] == INPUT_DOWN)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//is the key input up
bool Input::IsKeyUp(unsigned char key)
{
	if (KeyState[key] == INPUT_UP)
	{

		return true;
	}
	else
	{
		return false;
	}

}
bool Input::IsMouseClick(int button)
{
	if (MouseState[button] == INPUT_DOWN)
	{

		return true;
	}
	else
	{
		return false;
	}

}

void Input::Mouseprocess()
{
	if (MouseState[0] == INPUT_DOWN)
	{
		MouseState[0] = INPUT_DOWN_FIRST;
	}
	if (MouseState[0] == INPUT_UP)
	{
		MouseState[0] = INPUT_UP_FIRST;
	}

}