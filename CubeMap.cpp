#include "CubeMap.h"

std::string Texture[] =
{
	"right.jpg",
	"left.jpg",
	"top.jpg",
	"bottom.jpg",
	"back.jpg",
	"front.jpg",
};
CubeMap::CubeMap(Camera* Cam)
{
	CameraObject = Cam;
	program_Cube = ShaderLoader::CreateProgram("Resources/CubeMap.vs", "Resources/CubeMap.fs");
	GLfloat vertices[] =
	{
			//Position				
			//Front
	/*0*/	-0.5f, 0.5f, 0.5f,		
	/*1*/	-0.5f, -0.5f, 0.5f,		
	/*2*/	0.5f, -0.5f, 0.5f,		
	/*3*/	0.5f, 0.5f, 0.5f,		

			//Back
	/*4*/	-0.5f, 0.5f, -0.5f,		
	/*5*/	-0.5f, -0.5f, -0.5f,	
	/*6*/	0.5f, -0.5f, -0.5f,		
	/*7*/	0.5f, 0.5f, -0.5f,		

			//left
	/*4*/	-0.5f, 0.5f, -0.5f,		
	/*5*/	-0.5f, -0.5f, -0.5f,	
	/*1*/	-0.5f, -0.5f, 0.5f,		
	/*0*/	-0.5f, 0.5f, 0.5f,		
			//right
	/*3*/	0.5f, 0.5f, 0.5f,		
	/*2*/	0.5f, -0.5f, 0.5f,		
	/*6*/	0.5f, -0.5f, -0.5f,		
	/*7*/	0.5f, 0.5f, -0.5f,		

			//Top
	/*4*/	-0.5f, 0.5f, -0.5f,		
	/*0*/	-0.5f, 0.5f, 0.5f,		
	/*3*/	0.5f, 0.5f, 0.5f,		
	/*7*/	0.5f, 0.5f, -0.5f,		

			//Bottom
	/*1*/	-0.5f, -0.5f, 0.5f,		
	/*5*/	-0.5f, -0.5f, -0.5f,	
	/*6*/	0.5f, -0.5f, -0.5f,		
	/*2*/	0.5f, -0.5f, 0.5f,		

	};

GLuint indices[] = {
	0,2,1, //Front
	0,3,2, //Front

	7,5,6, //back
	7,4,5,//back

	8,10,9,//Left
	8,11,10, //Left

	12,14,13, //Right
	12,15,14, //Right

	16,18,17, //Top
	16,19,18,//Top

	20,22,21,//Bottom
	20,23,22, //Bottom

};
	
	GLuint VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);


	

	CreateTexture("Resources/Textures/Rayman.jpg", texID);

}

CubeMap::~CubeMap()
{

}

void 
CubeMap::CreateTexture(const char* imageID, GLuint& tex)
{
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex);

	int width, height;

	unsigned char* image;

	for (int i = 0; i < 6; i++)
	{
		std::string fullPathName = "Resources/Textures/CubeMap/";
		fullPathName.append(Texture[i]);

		image= SOIL_load_image(fullPathName.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}
	
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	

	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
void 
CubeMap::Render()
{
	glUseProgram(program_Cube);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
	glUniform1i(glGetUniformLocation(program_Cube, "cubeSampler"), 0);
	glUniformMatrix4fv(glGetUniformLocation(program_Cube, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}
void 
CubeMap::Update()
{
	
	glm::mat4 Model = glm::scale(glm::mat4(), glm::vec3(2000.0f, 2000.0f, 2000.0f));
	MVP = CameraObject->GetProjection() * CameraObject->GetView() * Model;

}
GLuint 
CubeMap::GetTextureID()
{
	return texID;
}