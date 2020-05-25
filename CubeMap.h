#pragma once

// Dependency Includes
#include "glm.hpp" 
#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include "glm.hpp" 
#include "gtc/matrix_transform.hpp" 
#include "gtc/type_ptr.hpp" 
#include <fmod.hpp>

#include "ShaderLoader.h" 
#include "Camera.h"

class CubeMap
{
public:
	CubeMap(Camera* Cam);
	~CubeMap();
	void CreateTexture(const char* imageID, GLuint& tex);
	GLuint GetTextureID();
	void Render();
	void Update();
private:
	Camera* CameraObject;
	GLuint program_Cube;
	GLuint VAO;
	GLuint texID; //rayman texture

	

	glm::mat4 MVP;
	GLuint MVPloc;

};

