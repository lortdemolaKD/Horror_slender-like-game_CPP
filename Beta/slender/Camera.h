#pragma once

#include<iostream>

#include<glew.h>
#include<glfw3.h>

#include<glm.hpp>
#include<vec3.hpp>
#include<mat4x4.hpp>
#include<gtc/matrix_transform.hpp>

enum direction { FORWARD = 0, BACKWARD, LEFT, RIGHT,SHIFT};

class Camera
{
private:
	glm::mat4 ViewWatrix;
	
	GLfloat movementSpeed;
	GLfloat sensitivity;

	glm::vec3 worldUP;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;

	void updateCameraVectors()
	{
		this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		this->front.y = sin(glm::radians(this->pitch));
		this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

	this->front = glm::normalize(this->front);
	this->right = glm::normalize(glm::cross(this->front, this->worldUP));
	this->up = glm::normalize(glm::cross(this->right, this->front));
	}


public:
	Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUP)
	{
		this->ViewWatrix = glm::mat4(1.f);

		this->movementSpeed = 3.f;
		this->sensitivity = 5.f;

		this->worldUP = worldUP;
		this->position = position;
		this->right = glm::vec3(0.f);
		this->up = worldUP;

		this->pitch = 0.f;
		this->yaw = -90.f;
		this->roll = 0.f;

	}

	~Camera(){}
	//cAccessor
	const glm::mat4 getViewWatrix()
	{
		updateCameraVectors();

		this->ViewWatrix = glm::lookAt(this->position, this->position + this->front , this->up);

		return this->ViewWatrix;
	}

	const glm::vec3 getPosition() const
	{
		return this->position;
	}
	void SetPositionX(GLfloat pos) 
	{
		this->position.x += pos;
	}
	void SetPositionZ(GLfloat pos)
	{
		this->position.z += pos;
	}
	glm::vec3 Getfront()
	{
		return this->front;
	}
	//function
	void updateMouseInput(const float& dt, const double& offsetX, const double& offsetY)
	{  
		//update pitch yaw and roll
		this->pitch -= static_cast<GLfloat>(offsetY) * this->sensitivity *dt;
		this->yaw += static_cast<GLfloat>(offsetX) * this->sensitivity * dt;

		if (this->pitch >= 80.f) 
		{
			this->pitch = 80.f;
		}
		else if (this->pitch < -80.f)
		{
			this->pitch = -80.f;
		}
		if (this->yaw > 360.f || this->yaw < -360.f)
			this->yaw = 0.f;
		
	}
	void move(const float& dt, const int direction,bool sprint, bool walk)
	{
		
		GLfloat tempspeed = this->movementSpeed;
		if (sprint == true)
		{
			tempspeed = (tempspeed * 2);
		}
		if (walk == true)
		{
			tempspeed = (tempspeed / 2);
		}
		switch (direction)
		{
		case FORWARD:
			
			this->position += this->front * tempspeed * dt ;
			this->position.y = 0.f;
			break;
		case BACKWARD:
			this->position -=  this->front * tempspeed * dt ;
			this->position.y = 0.f;
			break;
		case LEFT:
			this->position -= this->right * tempspeed * dt;
			this->position.y = 0.f;
			break;
		case RIGHT:
			this->position += this->right * tempspeed * dt;
			this->position.y = 0.f;
			break;
	
		default:
			break;
		}
	}
	

	void updateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY)
	{
	
		this->updateMouseInput(dt, offsetX, offsetY);
	}

};