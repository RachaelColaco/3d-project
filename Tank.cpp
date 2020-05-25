// Dependency Includes
#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
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


#include "Tank.h"



Tank::Tank(Camera* Cam)
{
	modelObject = new Model("Resources/Models/Tank/Tank.obj", Cam);
	
	SetPVM();

}
Tank::~Tank()
{

}
void Tank::Render()
{
	modelObject->Render();
	
}

void Tank::SetPVM()
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
void Tank::Update(float ObjPo)
{
	Angle = ObjPo;
	//objPosition.z = ObjPo;
	SetPVM();

}
