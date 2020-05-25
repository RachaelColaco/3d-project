//
// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand
//
// (c) 2020 Media Design School
//
// File Name: Camera.h
// Description: Camera declaration file
// Author: Rachael Colaco 
// Mail: Rachael.Col8495@mediadesign.school.nz 
//


#ifndef _CAMERA_H__
#define _CAMERA_H__

#pragma once

// Dependency Includes
#include "glm.hpp" 
#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>

class Camera
{
public:
	Camera();
	virtual ~Camera();
	void SetProjection(const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT);
	void Update(float deltaTine);
	glm::mat4 GetProjection();
	glm::mat4 GetView();
	glm::vec3 camPos;

private:

	
	glm::vec3 camLookDir = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 camUpDir= glm::vec3(0.0f, 0.5f, 0.0f);
	glm::mat4 proj;
	glm::mat4 view;
	float TimeEllapse;

};
#endif