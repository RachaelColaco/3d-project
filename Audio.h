#pragma once
//
// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand
//
// (c) 2020 Media Design School
//
// File Name: Audio.h
// Description: Audio declaration file
// Author: Rachael Colaco 
// Mail: Rachael.Col8495@mediadesign.school.nz 
//

// Dependency Includes
#include <fmod.hpp>

class Audio
{
public:
	Audio();
	~Audio();

	FMOD::System* System = 0;
	FMOD::Sound* BGM = 0; //background music
	FMOD::Sound* fxThump=0; //sound effect for player colliding with alien

private:
	bool Initialize();
};

