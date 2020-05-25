
// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand
//
// (c) 2020 Media Design School
//
// File Name: Enemy.cpp
// Description: Enemy Object implementation file
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

#include "Camera.h"
#include "Model.h"
#include "Enemy.h"



Enemy::Enemy(Camera* Cam)
{
	modelObject = new Model("Resources/Models/pug/Dog 1.obj", Cam);

	SetPVM();

}
Enemy::~Enemy()
{

}
void Enemy::Render()
{
	modelObject->Render();

}

void Enemy::SetPVM()
{

	translationMatrix = glm::translate(glm::mat4(), objPosition);

	//rotation matrix
	rotationZ = glm::rotate(glm::mat4(), glm::radians(Angle), rotationAxisZ);

	//scale matrix
	scaleMatrix = glm::scale(glm::mat4(), objScale);

	// model matrix= T*R*S
	model = translationMatrix * rotationZ * scaleMatrix;

	modelObject->model = model;

}
void Enemy::Update(float ObjPo)
{
	//objPosition.x = ObjPo;
	//objPosition.z = ObjPo;
	SetPVM();

}
