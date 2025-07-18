#include "Game.h"

#include <iostream>
#include <random>
#include <iomanip>
using std::cout;
using std::endl;
using std::setprecision;
//Private Functions
void Game::initGLFW()
{
	if (glfwInit() == GLFW_FALSE) {

		std::cout << "ERROR::GLFW_INIT_FAILE" << endl;
		glfwTerminate();
	}
}

void Game::initwindow(const char* TITLE, bool resizable)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);						//Tell the game that OpenGL V3.3 is needed; Major then Minor
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MINOR);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // mac os

	this->window = glfwCreateWindow(this->W_WINDOW, this->H_WINDOW, TITLE, NULL, NULL);
	if (this->window == nullptr) 
	{
		std::cout << "ERROR::GLFW_WINDOW_INIT_FAILE" << endl;
		glfwTerminate();
	}
	//Setup Window
	int window_width = 0, window_height = 0;
	glfwGetFramebufferSize(this->window, &this->framebuffer_W, &this->framebuffer_H);				//get window sites
	//glViewport(0, 0, window_width, window_height);					//set coordinates to top left (0,0); and set width and height to actual window width and height
	glfwSetFramebufferSizeCallback(this->window, Game::framebuffer_resize_callback);
	glfwMakeContextCurrent(this->window);

}

void Game::initGLEW()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {

		std::cout << "ERROR::GLEW_INIT_FAILE" << endl;
		glfwTerminate();

	}
}

void Game::initOpenGLOptions()
{
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//GL_LINES
//	input
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Game::initMatrices()
{
	this->ViewMatrix = glm::mat4(1.f);
	this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);

	this->ProjectionMatrix = glm::mat4(1.f);
	this->ProjectionMatrix = glm::perspective(glm::radians(this->fov), static_cast<float>(this->framebuffer_W) / this->framebuffer_H, this->nearPlane, this->farPlane);
	
	
	this->textprojection = glm::ortho((GLfloat)this->W_WINDOW, 0.f, (GLfloat)this->H_WINDOW,0.f); //glm::ortho(0.f, (float)this->framebuffer_W, 0.f, (float)this->framebuffer_H);//(GLfloat)this->W_WINDOW,0.f, (GLfloat)this->H_WINDOW);//glm::ortho(0.f, (float)W_WINDOW, 0.f, (float)H_WINDOW);


}

void Game::initShaders()
{
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR, (char*)"vertex_core.glsl", (char*)"fragment_core.glsl"));
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR, (char*)"vertex_core.glsl", (char*)"fragment_2D.glsl"));
}

void Game::initTextures()
{
	//texture norm+spec 1
		//texture INIT 
		this->textures.push_back(new Texture("images/crate2.png", GL_TEXTURE_2D));
		//texture INIT spec
		this->textures.push_back(new Texture("images/crate_spec2.png", GL_TEXTURE_2D));
		

	//texture norm+spec 2
		//texture INIT
		this->textures.push_back(new Texture("images/ground.png", GL_TEXTURE_2D));
		//texture INIT spec
		this->textures.push_back(new Texture("images/ground_spec.png", GL_TEXTURE_2D));


	//texture norm+spec Border
		//texture INIT
		this->textures.push_back(new Texture("images/crate.png", GL_TEXTURE_2D));
		//texture INIT spec
		this->textures.push_back(new Texture("images/crate_spec.png", GL_TEXTURE_2D));
	
	//texture norm+spec 2
		//texture INIT
		this->textures.push_back(new Texture("images/fence.png", GL_TEXTURE_2D));
		//texture INIT spec
		this->textures.push_back(new Texture("images/fence_spec.png", GL_TEXTURE_2D));

		this->textures.push_back(new Texture("images/grass.png", GL_TEXTURE_2D));
		//texture INIT spec
		this->textures.push_back(new Texture("images/grass_spec.png", GL_TEXTURE_2D));

		this->textures.push_back(new Texture("images/leaves.png", GL_TEXTURE_2D));
		//texture INIT spec
		this->textures.push_back(new Texture("images/leaves_spec.png", GL_TEXTURE_2D));
		

}

void Game::initMaterials()
{
													//0.0125f
	this->materials.push_back(new Material(glm::vec3(0.05f), glm::vec3(1.f), glm::vec3(1.f), 0, 1));
}




void Game::initModels() {
	srand((unsigned int)time(NULL));
	Quad tempPrimativeQ = Quad();
	Quad_terrain tempPrimativeQT = Quad_terrain();
	Triangle tempPrimativeTRI = Triangle();
	Piramide tempPrimativePRI = Piramide();
	Teseract tempPrimativeTES = Teseract();
	Cube tempPrimativeCube = Cube();
	Cube2 tempPrimativeCube2 = Cube2();
	Hex tempPrimativeHex = Hex();
	Cross tempPrimativeCRS = Cross();

	this->meshes.push_back(new Mesh(&tempPrimativeQT, glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
	this->models.push_back(new Model(glm::vec3(0.f), this->materials[0], this->textures[2], this->textures[3], this->meshes));
	for (auto*& i : this->meshes)
	{
		delete i;
	}
	this->meshes.clear();
	srand((unsigned int)time(NULL));
	this->meshes.push_back(new Mesh(&tempPrimativeCube, glm::vec3(91.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(1.f), true, true));
	this->meshes.push_back(new Mesh(&tempPrimativeCube, glm::vec3(0.f, 0.f, 91.f), glm::vec3(0.f), glm::vec3(1.f), true, false));
	this->meshes.push_back(new Mesh(&tempPrimativeCube, glm::vec3(-91.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(1.f), true, true));
	this->meshes.push_back(new Mesh(&tempPrimativeCube, glm::vec3(0.f, 0.f, -91.f), glm::vec3(0.f), glm::vec3(1.f), true, false));
	this->models.push_back(new Model(glm::vec3(0.f), this->materials[0], this->textures[6], this->textures[7], this->meshes));
	for (auto*& i : this->meshes)
	{
		delete i;
	}
	this->meshes.clear();
	srand(4);
	this->meshes.push_back(new Mesh(&tempPrimativeTES, glm::vec3(rando(), -0.25f, rando()), glm::vec3(0.f), glm::vec3(1.f), false, false,true));
	this->meshes.push_back(new Mesh(&tempPrimativeTES, glm::vec3(rando(), 0.f, rando()), glm::vec3(0.f), glm::vec3(1.f), false, false,true));
	this->meshes.push_back(new Mesh(&tempPrimativeTES, glm::vec3(rando(), -0.25f, rando()), glm::vec3(0.f), glm::vec3(1.f), false, false,true));
	this->meshes.push_back(new Mesh(&tempPrimativeTES, glm::vec3(rando(), 0.f, rando()), glm::vec3(0.f), glm::vec3(1.f), false, false,true));
	this->meshes.push_back(new Mesh(&tempPrimativeTES, glm::vec3(rando(), -0.25f, rando()), glm::vec3(0.f), glm::vec3(1.f), false, false,true));
	this->meshes.push_back(new Mesh(&tempPrimativeTES, glm::vec3(rando(), 0.f, rando()), glm::vec3(0.f), glm::vec3(1.f), false, false,true));
	this->meshes.push_back(new Mesh(&tempPrimativeTES, glm::vec3(rando(), -0.25f, rando()), glm::vec3(0.f), glm::vec3(1.f), false, false,true));
	this->meshes.push_back(new Mesh(&tempPrimativeTES, glm::vec3(rando(), 0.f, rando()), glm::vec3(0.f), glm::vec3(1.f), false, false,true));
	this->meshes.push_back(new Mesh(&tempPrimativeTES, glm::vec3(rando(), -0.25f, rando()), glm::vec3(0.f), glm::vec3(1.f), false, false,true));
	this->meshes.push_back(new Mesh(&tempPrimativeTES, glm::vec3(rando(), 0.f, rando()), glm::vec3(0.f), glm::vec3(1.f), false, false,true));
	this->meshes.push_back(new Mesh(&tempPrimativeTES, glm::vec3(rando(), -0.25f, rando()), glm::vec3(0.f), glm::vec3(1.f), false, false,true));
	this->meshes.push_back(new Mesh(&tempPrimativeTES, glm::vec3(rando(), 0.f, rando()), glm::vec3(0.f), glm::vec3(1.f), false, false,true));
	this->meshes.push_back(new Mesh(&tempPrimativeTES, glm::vec3(rando(), -0.25f, rando()), glm::vec3(0.f), glm::vec3(1.f), false, false,true));
	this->meshes.push_back(new Mesh(&tempPrimativeTES, glm::vec3(rando(), 0.f, rando()), glm::vec3(0.f), glm::vec3(1.f), false, false,true));
	this->meshes.push_back(new Mesh(&tempPrimativeTES, glm::vec3(rando(), -0.25f, rando()), glm::vec3(0.f), glm::vec3(1.f), false, false,true));
	this->meshes.push_back(new Mesh(&tempPrimativeTES, glm::vec3(rando(), 0.f, rando()), glm::vec3(0.f), glm::vec3(1.f), false, false,true));
	this->meshes.push_back(new Mesh(&tempPrimativeTES, glm::vec3(rando(), -0.25f, rando()), glm::vec3(0.f), glm::vec3(1.f), false, false,true));
	this->meshes.push_back(new Mesh(&tempPrimativeTES, glm::vec3(rando(), 0.f, rando()), glm::vec3(0.f), glm::vec3(1.f), false, false,true));
	this->meshes.push_back(new Mesh(&tempPrimativeTES, glm::vec3(rando(), -0.25f, rando()), glm::vec3(0.f), glm::vec3(1.f), false, false,true));
	this->meshes.push_back(new Mesh(&tempPrimativeTES, glm::vec3(rando(), 0.f, rando()), glm::vec3(0.f), glm::vec3(1.f), false, false,true));
	this->models.push_back(new Model(glm::vec3(0.f), this->materials[0], this->textures[4], this->textures[5], this->meshes));
	for (auto*& i : this->meshes)
	{
		delete i;
	}
	this->meshes.clear();
	srand(17);
	for (int i = 0; i < 500; i++)
	{
		this->meshes.push_back(new Mesh(&tempPrimativeHex, glm::vec3(rando2(), 1.25f, rando2()), glm::vec3(0.f), glm::vec3(1.f), false, false, false));
	}
	this->models.push_back(new Model(glm::vec3(0.f), this->materials[0], this->textures[0], this->textures[1], this->meshes));
	for (auto*& i : this->meshes)
	{
		delete i;
	}
	this->meshes.clear();
	for (int i = 0; i < 500; i++)
	{
		this->meshes.push_back(new Mesh(&tempPrimativeCube2, glm::vec3(0.f, 3.5f, 0.f), glm::vec3(0.f), glm::vec3(1.f), false, false, false));
	}
	this->models.push_back(new Model(glm::vec3(0.f), this->materials[0], this->textures[10], this->textures[11], this->meshes));
	for (auto*& i : this->meshes)
	{
		delete i;
	}
	this->meshes.clear();
	srand(28);
	for (int i = 0; i < 500; i++)
	{
		this->meshes.push_back(new Mesh(&tempPrimativeCRS, glm::vec3(rando3(), 0.f, rando3()), glm::vec3(0.f), glm::vec3(1.f), false, false, false));
	}
	this->models.push_back(new Model(glm::vec3(0.f), this->materials[0], this->textures[8], this->textures[9], this->meshes));
	for (auto*& i : this->meshes)
	{
		delete i;
	}
	this->meshes.clear();
	this->meshes.push_back(new Mesh(&tempPrimativeCRS, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(1.f), false, false, false));
	this->models.push_back(new Model(glm::vec3(0.f), this->materials[0], this->textures[8], this->textures[9], this->meshes));
	for (auto*& i : this->meshes)
	{
		delete i;
	}
	}

void Game::initPoinlights()
{
	this->pointlights.push_back(new PointLight(glm::vec3(0.f, 0.f, -2.f)));
	//this->pointlights.push_back(new PointLight(glm::vec3(0.f, 0.f, 40.f)));
	//this->pointlights.push_back(new PointLight(glm::vec3(-40.f, 0.f, 0.f)));
	//this->pointlights.push_back(new PointLight(glm::vec3(040.f, 0.f, 0.f)));

}

void Game::initSpotlights()
{
	this->spotlights.push_back(new SpotLight(this->camera.getPosition(), this->camera.Getfront()));
	//this->spotlights.push_back(new SpotLight(glm::vec3(0.f, 0.f, 0.f), glm::vec3(-0.0571612f, -0.984808f, -0.16397f)));
}

void Game::initLights()
{
	this->initPoinlights();
	this->initSpotlights();
}

void Game::initUniforms()
{
	this->shaders[SHADE_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix");
	this->shaders[SHADE_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");
	this->shaders[SHADE_CORE_PROGRAM]->setVec3f(this->camera.getPosition(), "camPosition");

	for (auto* pl : this->pointlights)
	{
		pl->sendToShader(*this->shaders[SHADE_CORE_PROGRAM]);
	}
	for (auto* pl : this->spotlights)
	{
		pl->sendToShader(*this->shaders[SHADE_CORE_PROGRAM]);
	}
	
	
}

void Game::updateUniforms()
{
	//update view matrix "camera"
	this->ViewMatrix = this->camera.getViewWatrix();
	
	this->shaders[SHADE_CORE_PROGRAM]->setMat4fv(this->ViewMatrix, "ViewMatrix");
	this->shaders[SHADE_CORE_PROGRAM]->setVec3f(this->camera.getPosition(), "camPosition");

	

	this->textprojection = glm::ortho(0.f, (float)W_WINDOW, 0.f, (float)H_WINDOW);//this->camera.getViewWatrix();//(GLfloat)this->W_WINDOW,0.f, (GLfloat)this->H_WINDOW);//glm::ortho(0.f, (float)W_WINDOW, 0.f, (float)H_WINDOW);
	//update buffer and projection matrix

	glfwGetFramebufferSize(this->window, &this->framebuffer_W, &this->framebuffer_W);

	this->ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(this->framebuffer_W) / this->framebuffer_W, this->nearPlane, this->farPlane);
	this->shaders[SHADE_CORE_PROGRAM]->setMat4fv(this->ProjectionMatrix, "ProjectionMatrix");

	for (auto* pl : this->pointlights)
	{
		pl->sendToShader(*this->shaders[SHADE_CORE_PROGRAM]);
	}
	for (auto* pl : this->spotlights)
	{
		pl->sendToShader(*this->shaders[SHADE_CORE_PROGRAM]);
	}
}


//Constructros/Destructors
Game::Game(const char* TITLE, const int W_WINDOW, const int H_WINDOW, const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR, bool resizable)
	: W_WINDOW(W_WINDOW), H_WINDOW(H_WINDOW), GL_VERSION_MAJOR(GL_VERSION_MAJOR), GL_VERSION_MINOR(GL_VERSION_MINOR), camera(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f))
{
	this->window = nullptr;
	this->framebuffer_H = this->H_WINDOW;
	this->framebuffer_W = this->W_WINDOW;

	this->camPosition = glm::vec3(0.f, 0.f, 1.f);
	this->worldUp = glm::vec3(0.f, 1.f, 0.f);
	this->camFront = glm::vec3(0.f, 0.f, -1.f);

	this->fov = 90.f;
	this->nearPlane = 0.1f;
	this->farPlane = 1000.f;

	//delta time
	this->dt = 0.f;
	this->curTime = 0.f;
	this->lastTime = 0.f;

	//gem
	this->move = true;	
	this->movesch = true;
	this->point = 0;

	//mouse input
	this->lastMouseX = 0.0;
	this->lastMouseY = 0.0;
	this->MouseX = 0.0;
	this->MouseY = 0.0;
	this->MouseOffsetX = 0.0;
	this->MouseOffsetY = 0.0;
	this->firstMouse = true;
	if (FT_Init_FreeType(&ft)) {
		std::cout << "error ft" << endl;
	}

	this->initGLFW();
	this->initwindow(TITLE, resizable);
	this->initGLEW();
	this->initOpenGLOptions();
	this->initMatrices();
	this->initShaders();
	this->initTextures();
	this->initMaterials();
	this->initModels();
	this->initLights();

	this->initUniforms();
	for (int i = 0; i < this->models[3]->getMeshSize(); i++)
	{
		this->models[3]->copyPosition(this->models[4], i);
	}
}


Game::~Game()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();
	
	for (auto*& i : this->shaders)
		delete i;

	for (auto*& i : this->textures)
		delete i;

	for (auto*& i : this->materials)
		delete i;
	
	for (auto*& i : this->models)
		delete i;

	for (auto*& i : this->pointlights)
		delete i;
	

}

//Accessors
int Game::getWindowShouldClose()
{
	return glfwWindowShouldClose(this->window);
}

//Modifies
void Game::setWindowShouldClose()
{
	glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}

//Functions

void Game::updateDT()
{
	
	this->curTime = static_cast<float>(glfwGetTime());
	this->dt = this->curTime - this->lastTime;
	this->lastTime = this->curTime;

	
}

void Game::updateMouseInput()
{
	glfwGetCursorPos(this->window, &this->MouseX, &this->MouseY);

	if (this->firstMouse) {
		this->lastMouseX = this->MouseX;
		this->lastMouseY = this->MouseY;
		this->firstMouse = false;
	}
	//calc offset
	this->MouseOffsetX = this->MouseX - this->lastMouseX;
	this->MouseOffsetY = this->MouseY - this->lastMouseY;

	//set last x and y
	this->lastMouseX = this->MouseX;
	this->lastMouseY = this->MouseY;

	if (glfwGetMouseButton(this->window,GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
		//this->spotlights[0]->SetPositon(this->camera.getPosition());
	}
}

void Game::updateKeyboardInput()
{
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(this->window, GLFW_TRUE);
	}

	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		if (glfwGetKey(this->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) 
		{
			this->camera.move(this->dt, FORWARD, true, false);
		}
		else if (glfwGetKey(this->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			this->camera.move(this->dt, FORWARD, false, true);
		}
		else
		{
			this->camera.move(this->dt, FORWARD, false, false);
		}
		
		this->spotlights[0]->SetPositon(this->camera.getPosition());
	
	}
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
	{
	
		if (glfwGetKey(this->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			this->camera.move(this->dt, BACKWARD, true, false);
		}
		else if (glfwGetKey(this->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			this->camera.move(this->dt, BACKWARD, false, true);
		}
		else
		{
			this->camera.move(this->dt, BACKWARD, false, false);
		}


		this->spotlights[0]->SetPositon(this->camera.getPosition());
	}
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
	{
	
		if (glfwGetKey(this->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			this->camera.move(this->dt, LEFT, true,false);
		}
		else if (glfwGetKey(this->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			this->camera.move(this->dt, LEFT, false, true);
		}
		else
		{
			this->camera.move(this->dt, LEFT, false, false);
		}

		this->spotlights[0]->SetPositon(this->camera.getPosition());
	}
	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		
		if (glfwGetKey(this->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			this->camera.move(this->dt, RIGHT, true, false);
		}
		else if (glfwGetKey(this->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			this->camera.move(this->dt, RIGHT, false, true);
		}
		else
		{
			this->camera.move(this->dt, RIGHT, false, false);
		}

		this->spotlights[0]->SetPositon(this->camera.getPosition());
	}
	
}

void Game::updateInput()
{
	glfwPollEvents();

	this->updateKeyboardInput();
	this->updateMouseInput();
	this->camera.updateInput(dt, -1, this->MouseOffsetX, this->MouseOffsetY);
	this->spotlights[0]->Setdirection(this->camera.Getfront());

}

void Game::GemMovement()
{
	GLfloat t;
	if(move == true)
	{
		
		for (size_t i = 5; i < 25; i++)
		{
			if (i % 2 == 0) {
				t = 0.005f;
			}
			else {
				t =-0.005f;
			}
			// 0.005f
			this->meshes[i]->move(glm::vec3(0.f, t, 0.f));
			this->meshes[i]->rotate(glm::vec3(0.f, 1.f, 0.f)); 

		}
		if (this->meshes[24]->GetPosition().y >= 0.f)
		{
			this->move = false;
		}
	}
	else
	{
		for (size_t i = 5; i < 25; i++)
		{
			if (i % 2 == 0) {
				t = -0.005f;
			}
			else {
				t = 0.005f;
			}
			
			this->meshes[i]->move(glm::vec3(0.f, t , 0.f));
			this->meshes[i]->rotate(glm::vec3(0.f, 1.f, 0.f));
		}
		if (this->meshes[24]->GetPosition().y <= -0.25f)
		{
			this->move = true;
		}
	}

}

void Game::update()
{
	//update input
	this->updateDT();
	this->updateInput();
	this->models[1]->colision(&this->camera, this->point);
	this->models[2]->colision(&this->camera,this->point);
	this->models[3]->colision(&this->camera, this->point);
	this->move = this->models[2]->GemMovement(this->move,this->movesch).v1;
	this->movesch = this->models[2]->GemMovement(this->move, this->movesch).v2;
	this->models[6]->setPositionALL(glm::vec3(this->camera.getPosition().x, this->camera.getPosition().y + 1.f, this->camera.getPosition().z));
	this->models[6]->setRotationALL(this->camera.Getfront());
	//this->GemMovement();
	this->models[2]->rotateALL(glm::vec3(0.f, 1.f, 0.f));
	for (int i = 0; i < this->models[2]->getMeshSize(); i++)
	{
		pointlights[0]->SetPositon(this->models[2]->GetPositionINV(i));
	}
	
	

	//this->updateInput(this->window);
//	this->updateInput(this->window, *this->meshes[MESH_QUAD]);
}

void Game::render()
{



	//Update
	//updateInput(game_window);
	//Swap Buffers
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//update the uniforms
	this->updateUniforms();

	//update uniforms
	//use a program
	//this->shaders[SHADE_CORE_2D]->use();
	//this->text[0]->RenderText(this->shaders[SHADE_CORE_2D], "abc:", 1.f, 300.0f, 1.0f);

	this->models[0]->Render(this->shaders[SHADE_CORE_PROGRAM]);
	this->models[0]->setPositionALL(glm::vec3(0.f, -0.5f, 0.f));
	this->models[0]->setRotationALL(glm::vec3(-90.f, 0.f, 0.f));
	this->models[0]->setScaleALL(glm::vec3(190.f));

	this->models[1]->Render(this->shaders[SHADE_CORE_PROGRAM]);
	this->models[1]->setScaleINV(glm::vec3(1.5f, 1.f, 200.f),0);//ta
	this->models[1]->setScaleINV(glm::vec3(200.f, 1.f, 1.5f),1);
	this->models[1]->setScaleINV(glm::vec3(1.5f, 1.f, 200.f),2);
	this->models[1]->setScaleINV(glm::vec3(200.f, 1.f, 1.5f),3);

	this->models[2]->Render(this->shaders[SHADE_CORE_PROGRAM]);
	this->models[2]->setScaleALL(glm::vec3(0.125f, 0.25f, 0.125f));

	this->models[3]->Render(this->shaders[SHADE_CORE_PROGRAM]);
	this->models[3]->setScaleALL(glm::vec3(0.25f, 3.5f, 0.25f));

	this->models[4]->Render(this->shaders[SHADE_CORE_PROGRAM]);
	this->models[4]->setScaleALL(glm::vec3(2.f, 1.f, 2.f));
	
	this->models[5]->Render(this->shaders[SHADE_CORE_PROGRAM]);
	this->models[6]->Render(this->shaders[SHADE_CORE_PROGRAM]);
	this->models[6]->setRotationALL(glm::vec3(90.f, 0.f, 0.f));
	//temporary close
	//this->shaders[SHADE_CORE_2D]->use();
	//renderFont(0, this->shaders[SHADE_CORE_2D], "jjjjjjjjj", 1.f, 1.f, 1.f, glm::vec3(1.f, 1.f, 1.f));
	//renderFont(0, this->shaders[SHADE_CORE_2D], "yyyyyyyyy", 1.0f, 1.0f, glm::vec2(0.41f,1.0f), glm::vec3(0.5, 0.8f, 0.2f));
	//renderFont(0, this->shaders[SHADE_CORE_2D], "ppppppppp", 1.0f, 1.0f, glm::vec2(0.4f, 1.0f), glm::vec3(0.5, 0.8f, 0.2f));
	
	/*//activate texture
this->textures[TEX_PUSHEEN]->bind(0);
this->textures[TEX_PUSHEEN_SPEC]->bind(1);
	 

	//							1920,1080
	// 
	// 
	// 
	// 
	// 
	// 
	// 0,0
	//draw
	this->meshes[MESH_TERRAIN]->render(this->shaders[SHADE_CORE_PROGRAM]);
	this->meshes[MESH_TERRAIN]->setPosition(glm::vec3(0.f, -0.5f, 0.f));
	this->meshes[MESH_TERRAIN]->setRotation(glm::vec3(-90.f, 0.f, 0.f));
	this->meshes[MESH_TERRAIN]->setScale(glm::vec3(180.f));
	this->textures[4]->bind(0);
	this->textures[5]->bind(1);

	this->meshes[1]->render(this->shaders[SHADE_CORE_PROGRAM]);
	this->meshes[1]->setScale(glm::vec3(0.5f, 1.f, 180.f));
	this->textures[4]->bind(0);
	this->textures[5]->bind(1);

	this->meshes[2]->render(this->shaders[SHADE_CORE_PROGRAM]);
	this->meshes[2]->setScale(glm::vec3(180.f, 1.f, 0.5f));
	this->textures[4]->bind(0);
	this->textures[5]->bind(1);

	this->meshes[3]->render(this->shaders[SHADE_CORE_PROGRAM]);
	this->meshes[3]->setScale(glm::vec3(0.5f, 1.f, 180.f));
	this->textures[4]->bind(0);
	this->textures[5]->bind(1);

	this->meshes[4]->render(this->shaders[SHADE_CORE_PROGRAM]);
	this->meshes[4]->setScale(glm::vec3(180.f, 1.f, 0.5f));

	for (size_t i = 5; i < 25; i++)
	{
		this->textures[4]->bind(0);
		this->textures[5]->bind(1);

		this->meshes[i]->render(this->shaders[SHADE_CORE_PROGRAM]);
		this->meshes[i]->setScale(glm::vec3(0.125f, 0.25f, 0.125f));

	}*/
	


	//this->Texts[0]->RenderText(*this->shaders[SHADE_CORE_PROGRAM]); 
//	this->Texts[1]->RenderText(*this->shaders[SHADE_CORE_PROGRAM]);
	

	//end
	glfwSwapBuffers(this->window);
	glFlush();

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
}

//Static Functions
void Game::framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH)
{
	glViewport(0, 0, fbW, fbH);
}





float Game::rando()
{

	int FLOAT_MIN = 89;
	int FLOAT_MAX = -89;
	FLOAT_MAX -= FLOAT_MIN;
	float c = (float(rand()) / float((RAND_MAX)) * FLOAT_MAX + FLOAT_MIN);
//
	
	 return c;
}

float Game::rando2()
{


	int FLOAT_MIN = 83;
	int FLOAT_MAX = -83;
	FLOAT_MAX -= FLOAT_MIN;
	float c = (float(rand()) / float((RAND_MAX)) * FLOAT_MAX + FLOAT_MIN);
	//

	return c;
}

float Game::rando3()
{
	
	int FLOAT_MIN = 88;
	int FLOAT_MAX = -88;
	FLOAT_MAX -= FLOAT_MIN;
	float c = (float(rand()) / float((RAND_MAX)) * FLOAT_MAX + FLOAT_MIN);
	//

	return c;
}
/*
void Game::updateInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void Game::updateInput(GLFWwindow* window, Mesh& mesh)
{

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(0.f, 0.f, -0.01f));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(0.f, 0.f, 0.01f));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(-0.01f, 0.f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(0.01f, 0.f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(0.f, 0.01f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(0.f, -0.01f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		mesh.rotate(glm::vec3(0.f, 1.f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		mesh.rotate(glm::vec3(0.f, -1.f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		mesh.scaleUp(glm::vec3(0.1f));
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		mesh.scaleUp(glm::vec3(-0.1f));
	}
	


}
*/