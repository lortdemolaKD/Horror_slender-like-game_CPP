#pragma once

#include<glew.h>
#include<glfw3.h>

#include<glm.hpp>
#include<vec2.hpp>
#include<vec3.hpp>
#include<vec4.hpp>
#include<mat4x4.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>

#include"shader.h"


using namespace std;

class Material
{
private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	GLint diffuseTex;
	GLint specularTex;

public:
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuseTex, GLint specularTex)
	{
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->diffuseTex = diffuseTex;
		this->specularTex = specularTex;
			
	}
	~Material()
	{

	}
	//functions
	void sendToShader(Shader& programID) 
	{
		programID.setVec3f(this->ambient,"material.ambient");
		programID.setVec3f(this->diffuse, "material.diffuse");
		programID.setVec3f(this->specular, "material.specular");
		programID.set1i(this->diffuseTex, "material.diffuseTex");
		programID.set1i(this->specularTex, "material.specularTex");
	}

};