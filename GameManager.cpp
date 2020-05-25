// Dependency Includes
#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include "glm.hpp" 
#include "gtc/matrix_transform.hpp" 
#include "gtc/type_ptr.hpp" 
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
#include "Input.h"
#include "Audio.h"
#include "Enemy.h"

//Width and Height of the screen
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;


float objPosX = 0.0f;
float objPosY = 0.0f;



glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 0.0f);

GLuint program_Animate; //program which doe animation and movement in images
GLuint program_Waver; //program which fades from one texture to another
GLuint program_Light;


float AnimateTime = 0.0f; //time of animation

GLfloat FramePos = 0.0f; //image position by frame
GLfloat DeltaTime = 0.0f; //delta Time
GLfloat frame = 8.0f; //frames of the sprite
GLfloat CurrentTime; //Current Time

float previousTime; //previous timestamp
float TimeEllapse;



//vectices for all side texture pyradmid 

GLfloat vertices1[] =
{
	//Position				//Color				//tex Coords
	/*0*/	-0.5f, 0.0f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f,1.0f,/*00*/
	/*1*/	-0.5f, 0.0f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f,0.0f,/*01*/
	/*2*/	0.5f, 0.0f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f,0.0f,/*02*/
	/*3*/	0.5f, 0.0f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f,1.0f,/*03*/

			//Side 1
			/*0*/	-0.5f, 0.0f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f,1.0f,/*04*/
			/*3*/	0.5f, 0.0f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f,1.0f,/*05*/

					//Side 2
					/*3*/	0.5f, 0.0f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f,1.0f,/*06*/
					/*2*/	0.5f, 0.0f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f,1.0f,/*07*/

							//Side 3
							/*2*/	0.5f, 0.0f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f,1.0f,/*08*/
							/*1*/	-0.5f, 0.0f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f,1.0f,/*09*/

									//Side 4
									/*1*/	-0.5f, 0.0f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f,1.0f,/*10*/
									/*0*/	-0.5f, 0.0f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f,1.0f,/*11*/

											//Top point
											/*4*/	0.0f, 0.5f, 0.0f,		0.0f, 1.0f, 1.0f,	0.5f,0.0f,/*12*/
};

GLuint indices1[] = {
	1,0,3, //base triangle 1
	1,3,2, //base triangle 2

	4,12,5, //side 1
	6,12,7,//side 2
	8,12,9,//side 3
	10,12,11, //side 4
};

//cube
GLfloat vertices2[] =
{
	//Position				//Color				//tex Coords
	//Front
	/*0*/	-0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f,0.0f,/*00*/
	/*1*/	-0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f,1.0f,/*01*/
	/*2*/	0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f,1.0f,/*02*/
	/*3*/	0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f,0.0f,/*03*/

	//Back
	/*4*/	-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f,0.0f,/*04*/
	/*5*/	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	1.0f,1.0f,/*05*/
	/*6*/	0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f,1.0f,/*06*/
	/*7*/	0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f,0.0f,/*07*/

	//left
	/*4*/	-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f,0.0f,/*08*/
	/*5*/	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	0.0f,1.0f,/*09*/
	/*1*/	-0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f,1.0f,/*10*/
	/*0*/	-0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f,0.0f,/*11*/

	//right
	/*3*/	0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f,0.0f,/*12*/
	/*2*/	0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f,1.0f,/*13*/
	/*6*/	0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f,1.0f,/*14*/
	/*7*/	0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f,0.0f,/*15*/

	//Top
	/*4*/	-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f,0.0f,/*16*/
	/*0*/	-0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f,1.0f,/*17*/
	/*3*/	0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f,1.0f,/*18*/
	/*7*/	0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f,0.0f,/*19*/

	//Bottom
	/*1*/	-0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f,0.0f,/*20*/
	/*5*/	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	0.0f,1.0f,/*21*/
	/*6*/	0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f,1.0f,/*22*/
	/*2*/	0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f,0.0f,/*23*/

};

GLuint indices2[] = {
	0,1,2, //Front
	0,2,3, //Front

	7,6,5, //back
	7,5,4,//back

	8,9,10,//Left
	8,10,11, //Left

	12,13,14, //Right
	12,14,15, //Right

	16,17,18, //Top
	16,18,19,//Top

	20,21,22,//Bottom
	20,22,23, //Bottom

};


GLfloat vertices[] =
{
	-0.5f,	0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f,0.0f,//top-left
	-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f,1.0f,//bot-left
	0.5f,  -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	1.0f,1.0f,//bot-right
	0.5f,	0.5f,-0.0f,		0.0f, 0.0f, 1.0f,	1.0f,0.0f,//top-right

};

GLuint indices[] = {
	0,4,3, //first triangle
	3,4,2, //second triangle
	2,4,1,
	1,4,0,

	1,0,3,
	1,3,2,
};
GLuint RaymanTex; //rayman texture
GLuint AwesomeFaceTex; //awesomeface texture
GLuint WalkingTex; //walking guy texture
GLuint LiefTex; //Lief texture


//variable members for MVP
glm::vec3 objPosition;
glm::mat4 translationMatrix;
glm::vec3 rotationAxisZ;
glm::mat4 rotationZ;
float rotationAngle = 0.0f;

glm::vec3 objScale;
glm::mat4 scaleMatrix;
glm::mat4 model;

glm::mat4 MVP;
GLuint MVPloc;

GLuint ModelLoc;
GLuint CamPosLoc;


GameManager::GameManager()
{

}
GameManager::~GameManager()
{

}
void 
GameManager::MainSetup()
{
	Audiosystem = new Audio();
	CameraObject = new Camera();
	label = new TextLabel("There is some juicy text", "Resources/Fonts/arial.ttf", glm::vec2(-350.0f, 300.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);
	//Create the textures


	//AudioInit();
	Spheremesh = new Sphere();
	cubeMap = new CubeMap(CameraObject);

	Pug = new Enemy(CameraObject);
	TankObject = new Tank(CameraObject);


	//Inputs
	InputKey = new Input();

	program_Animate = ShaderLoader::CreateProgram("Resources/basic.vs", "Resources/Waver.fs");
	program_Waver = ShaderLoader::CreateProgram("Resources/basic.vs", "Resources/Waver.fs");
	program_Light = ShaderLoader::CreateProgram("Resources/Reflection.vs", "Resources/Reflection.fs");

	
	previousTime = glutGet(GLUT_ELAPSED_TIME) * 0.001f; //initilizing the previous time stamp and set to seconds

	
}
void 
GameManager::Render()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	// Render code will be written here

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	ModelREF(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.5f, 0.5f, 0.5f), 0.0f);
	glUseProgram(program_Light);

	//Animation time applied
	//GLint currentTimeLoc = glGetUniformLocation(program_Light, "FramePos");
	//glUniform1f(currentTimeLoc, 0);

	//Set the translate, rotation, scale


	//Apply MVP to the program
	MVPloc = glGetUniformLocation(program_Light, "MVP");
	glUniformMatrix4fv(MVPloc, 1, GL_FALSE, glm::value_ptr(MVP));

	//Apply MVP to the program
	ModelLoc = glGetUniformLocation(program_Light, "model");
	glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));

	//Apply texture to program texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, RaymanTex);
	glUniform1i(glGetUniformLocation(program_Light, "tex"), 0);

	glActiveTexture(GL_TEXTURE1);
	glUniform1i(glGetUniformLocation(program_Light, "skybox"), 1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap->GetTextureID());

	CamPosLoc = glGetUniformLocation(program_Light, "camPos");
	glUniform3fv(CamPosLoc, 1, glm::value_ptr(CameraObject->camPos));


	Spheremesh->Render();
	//	glBindVertexArray(0); //Unbind VAO

	cubeMap->Render();

	Pug->Render();

	TankObject->Render();
	
	
	//modelObject->Render();
	/*
	glUseProgram(program_Animate);

	//Animation time applied
	currentTimeLoc = glGetUniformLocation(program_Animate, "FramePos");
	glUniform1f(currentTimeLoc, CurrentTime);

	//Set the translate, rotation, scale
	ModelREF(glm::vec3(0.0f, -150.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(400.0f, 400.0f, 1.0f), 0.0f);

	//Apply MVP to the program
	MVPloc = glGetUniformLocation(program_Animate, "MVP");
	glUniformMatrix4fv(MVPloc, 1, GL_FALSE, glm::value_ptr(MVP));

	//Apply texture to program texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, LiefTex);
	glUniform1i(glGetUniformLocation(program_Animate, "tex"), 0);


	glBindVertexArray(VAO1); //Bind VAO
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0); //Unbind VAO
	glUseProgram(0);
	*/
	label->Render();
	glutSwapBuffers();
}
void 
GameManager::Update()
{
	//Update game information
	ProcessInput();
	
	InputKey->Mouseprocess();
	CurrentTime = glutGet(GLUT_ELAPSED_TIME) * 0.001f; //get current time and Convert milliseconds to second
	DeltaTime = (CurrentTime - previousTime);   //calculate Deltatime
	previousTime = CurrentTime; //update the previous with current
	AnimateTime += DeltaTime; //updates the time for animation
	CameraObject->Update(objPosX);
	TankObject->Update((objPosX+0.56f) * 57.2958f);
	Pug->Update(objPosY);
	cubeMap->Update();
	MVP = CameraObject->GetProjection() * CameraObject->GetView() * model;
	//Updating rotation
	//rotationAngle += DeltaTime * 100;
	//audioSystem->update();
	
	Audiosystem->System->update();
	glutPostRedisplay(); //Function in glutDisplayFunc() us cakked
}
void GameManager::KeyboardDown(unsigned char key, int x, int y)
{
	InputKey->KeyDown(key, x, y);
}
void GameManager::KeyboardUP(unsigned char key, int x, int y)
{
	InputKey->KeyUP(key, x, y);
}
void GameManager::MouseClick(int button, int state, int x, int y)
{
	InputKey->MouseClick(button, state, x, y);
}

void GameManager::ProcessInput()
{
	if ((InputKey->IsKeyDown('w') == true || InputKey->IsKeyDown('W') == true))
	{
		objPosY += 1.0f * DeltaTime;

	}
	if ((InputKey->IsKeyDown('s') == true || InputKey->IsKeyDown('S') == true))
	{
		objPosY -= 1.0f * DeltaTime;

	}
	if ((InputKey->IsKeyDown('d') == true || InputKey->IsKeyDown('D') == true))
	{
		objPosX += 1.0f * DeltaTime;

	}
	if ((InputKey->IsKeyDown('a') == true || InputKey->IsKeyDown('A') == true))
	{
		objPosX -= 1.0f * DeltaTime;;

	}
	if ((InputKey->IsMouseClick(0) ==true))
	{
		Audiosystem->System->playSound(Audiosystem->fxThump, 0, false, 0);
	}

}

void CreateTexture(const char* imageID, GLuint& tex)
{
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	int width, height;
	unsigned char* image = SOIL_load_image(imageID, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void 
GameManager::ModelREF(glm::vec3 objPosition, glm::vec3 rotationAxis, glm::vec3 objScale, float rotationAngle)
{
	
	//translate matrix
	translationMatrix = glm::translate(glm::mat4(), objPosition);

	//rotation matrix
	rotationZ = glm::rotate(glm::mat4(), glm::radians(rotationAngle), rotationAxis);
	
	//scale matrix
	scaleMatrix = glm::scale(glm::mat4(), objScale);


	CameraObject->SetProjection(SCR_WIDTH, SCR_HEIGHT);
	// model matrix= T*R*S
	model = translationMatrix * rotationZ * scaleMatrix;


	//MVP = Proj*View*Model

	//Delete new camera class
	//delete CameraObject;

}
