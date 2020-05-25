//
// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand
//
// (c) 2020 Media Design School
//
// File Name: Audio.cpp
// Description: Audio implementation file
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
#include "Audio.h"

Audio::Audio()
{
	Initialize();
}
Audio::~Audio()
{

}
bool Audio::Initialize()
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&System);
	result = System->init(100, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0);

	result = System->createSound("Resources/Audio/Thump.wav", FMOD_DEFAULT, 0, &fxThump); //plays once



	if (result != FMOD_OK)
		return false;


	return true;
}