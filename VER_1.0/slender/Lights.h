#pragma once
#include"libs.h"

class Lights
{
protected:
	//glm::vec3 position;
	float intensity;
	int id;
	glm::vec3 color;
public:
	Lights(float intensity, glm::vec3 color) 
	{
		this->intensity = intensity;
		this->color = color;
	}
	~Lights() {}

	virtual void sendToShader(Shader& programID) = 0;
	


};

class PointLight : public Lights
{
protected:
	glm::vec3 position;
	float constant;
	float Linear;
	float quadratic;
public:
	PointLight(glm::vec3 position, float intensity = 1.f, glm::vec3 color = glm::vec3(1.f), float constant = 1.f, float linear = 0.7f, float quadratic = 1.8f) : Lights(intensity, color)
	{
		this->position = position;
		this->constant = constant;
		this->Linear = linear;
		this->quadratic = quadratic;
	}			 
	~PointLight() 
	{

	}
	void SetPositon(const glm::vec3 position)
	{
		this->position = position;
	}

	void sendToShader(Shader& programID)
	{
	
		programID.set1f(0.f, "sl");
		programID.setVec3f(this->position, "pointlight.position");
		programID.set1f(this->intensity, "pointlight.intensity");
		programID.setVec3f(this->color, "pointlight.color");
		programID.set1f(this->constant, "pointlight.constant");
		programID.set1f(this->Linear, "pointlight.Linear"); 
		programID.set1f(this->quadratic, "pointlight.quadratic"); 

	}
};


class SpotLight : public Lights
{
protected:
	glm::vec3 position;
	glm::vec3 direction;
	float cutOff;
	float outerCutOff;
	float constant;
	float Linear;
	float quadratic;
public:
	SpotLight(glm::vec3 position, glm::vec3 direction, float cutOff = glm::cos(glm::radians(15.5f)), float outerCutOff = glm::cos(glm::radians(20.5f)), float intensity = 3.f, glm::vec3 color = glm::vec3(1.f), float constant = 1.f, float linear = 0.22f, float quadratic = 0.20f) : Lights(intensity, color)
	{
		this->position = position;
		this->constant = constant;
		this->Linear = linear;
		this->quadratic = quadratic;
		this->direction = direction;
		this->cutOff = cutOff;
		this->outerCutOff = outerCutOff;



		

	}
	~SpotLight()
	{

	}
	void SetPositon(const glm::vec3 position)
	{
		this->position = position;
	}
	glm::vec3  GETPositon()
	{
		return this->position;
	}
	void Setdirection(const glm::vec3 direction)
	{
		this->direction = direction;
	}
	glm::vec3  GETdirection()
	{
		return this->direction;
	}

	void sendToShader(Shader& programID)
	{
		programID.set1f(1.f, "sl");
		programID.setVec3f(this->position, "spotLight.position");
		programID.setVec3f(this->direction, "spotLight.direction");
		programID.set1f(this->cutOff, "spotLight.cutOff");
		programID.set1f(this->outerCutOff, "spotLight.outerCutOff");
		programID.set1f(this->intensity, "spotLight.intensity");
		programID.setVec3f(this->color, "spotLight.color");
		programID.set1f(this->constant, "spotLight.constant");
		programID.set1f(this->Linear, "spotLight.Linear");
		programID.set1f(this->quadratic, "spotLight.quadratic");

	}
};


