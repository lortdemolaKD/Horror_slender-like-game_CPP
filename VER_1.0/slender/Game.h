#pragma once

#include"libs.h"
#include"Camera.h"
#include"Lights.h"
#include"TextRender.h"

//enumerations
enum shader_enums{SHADE_CORE_PROGRAM = 0, SHADE_CORE_SPOTLIGHT};
enum texture_enums { TEX_PUSHEEN = 0, TEX_PUSHEEN_SPEC , TEX_CONTAINER, TEX_CONTAINER_SPEC};
enum material_enums { MAT_1 = 0 };
enum mesh_enums { MESH_TERRAIN = 0 };


class Game
{
private:
//Variable
	//window
	const char* TITLE; 
	bool resizable;

	GLFWwindow* window;
	const int W_WINDOW;
	const int H_WINDOW;
	int framebuffer_W;
	int framebuffer_H;
	GLfloat timer;
	//opengl context
	const int GL_VERSION_MAJOR;
	const int GL_VERSION_MINOR;
	
	//delta time
	float dt;
	float curTime;
	float lastTime;

	//mouse input
	double lastMouseX;
	double lastMouseY;
	double MouseX;
	double MouseY;
	double MouseOffsetX;
	double MouseOffsetY;
	bool firstMouse;

	//gems
	bool move;
	bool movesch;
	bool intro;
	bool GAME_started;
	bool PLAYER_died;
	bool teleported;
	bool BR_start;
	bool BR_exit;
	bool BR_reset;
	int point;
	int tempoint;

	//camera

	Camera camera;

	//matrices
	FT_Library ft;
	glm::mat4 ViewMatrix;
	glm::mat4 textprojection;
	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 camFront;

	glm::mat4 ProjectionMatrix;
	float fov;
	float nearPlane;
	float farPlane;

	bool hit;
	bool tick;
	
	GLint life;
	//Shaders
	std::vector<Shader*> shaders;
	//Textures
	std::vector<Texture*> textures;
	//Material
	std::vector<Material*> materials;
	//Meshes
	std::vector<Mesh*> meshes;
	//models
	std::vector <Model*> models;
	//Meshes
	std::vector <PointLight*> pointlights;

	std::vector <SpotLight*> spotlights;
	//sounds
	std::vector <Sound*> sounds;
	



//Private Functions
	void initGLFW();
	void initwindow(const char* TITLE, bool resizable);
	void initGLEW();
	void initOpenGLOptions();
	void initMatrices();
	void initShaders();
	void initTextures();
	void initMaterials();

	void initModels();
	void initPoinlights();
	void initSpotlights();
	void initLights();
	void initSounds();

	void initUniforms();

	void updateUniforms();
//Static Variables

public:
//Constructros/Destructors
	Game(const char* TITLE, const int W_WINDOW, const int H_WINDOW, const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR, bool resizable);
	virtual ~Game();

//Accessors
	void Game_RESET();
	int getWindowShouldClose();
//Modifies
	void setWindowShouldClose();
//Functions
	void updateDT();
	void updateMouseInput();
	void updateKeyboardInput();
	void updateInput();
	void GemMovement();
	void update();
	void render();

//Static Functions
static void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH);


float rando();
float rando2();
float rando3();
/*
static void updateInput(GLFWwindow* window);

static void updateInput(GLFWwindow* window, Mesh& mesh);*/
};

