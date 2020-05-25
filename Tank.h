#pragma once
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
class Tank
{
public:
	Tank(Camera* Cam);
	 ~Tank();
	void Render();

	void Update(float ObjPos_X);
	void SetPVM();


	//variable members for MVP
	glm::mat4 translationMatrix;
	glm::mat4 rotationZ;
	glm::mat4 scaleMatrix;
	glm::mat4 model;

	glm::vec3 objPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotationAxisZ = glm::vec3(0.0f, 1.0f, 0.f);
	glm::vec3 objScale = glm::vec3(0.2f, 0.2f, 0.2f);

	glm::mat4 MVP;
	GLuint MVPloc;

	float AnimateTime = 0.0f; //time of animation
	float TimeEllapse = 0.0f;
	float Angle;

	GLfloat FramePos = 0.0f; //image position by frame
	GLfloat DeltaTime = 0.0f; //delta Time
	GLfloat frame = 4.0f; //frames of the sprite
	GLfloat CurrentTime; //Current Time



private:

	Model* modelObject;
	Camera* camera;
	void GenerateTexture(const char* imageID, GLuint& tex);
	int Objectsize = 0;
	GLuint programObject;
	GLuint TextureObject;
	GLuint VAO;
	GLuint EBO;
	GLuint VBO;

};

