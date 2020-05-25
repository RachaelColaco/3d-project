//
// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand
//
// (c) 2020 Media Design School
//
// File Name: Camera.cpp
// Description: Camera implementation file
// Author: Rachael Colaco 
// Mail: Rachael.Col8495@mediadesign.school.nz 
//


// Dependency Includes
#include "glm.hpp" 
#include "gtc/matrix_transform.hpp" 
#include "gtc/type_ptr.hpp" 


//Local Includes
#include "Camera.h"


Camera::Camera()
{
	
}

Camera::~Camera()
{

}
void Camera::SetProjection(const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT)
{
	//set projection in Orthographic 
	float halfScreenWidth = (float)SCR_WIDTH * 0.5f;
	float halfScreenHeight = (float)SCR_HEIGHT * 0.5f;
	proj = glm::perspective(45.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);

}
void Camera::Update(float deltatine)
{
	//Set view 
	GLfloat radius = 2.0f;

	camPos.x = sin(deltatine) * radius;
	camPos.y = 0.5f;
	camPos.z = cos(deltatine) * radius;
	view = glm::lookAt(camPos, camLookDir, camUpDir);
}
glm::mat4 Camera::GetProjection()
{
	//return projection value
	return proj;
}
glm::mat4 Camera::GetView()
{
	//return view value
	return view;
}
