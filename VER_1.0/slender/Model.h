#pragma once
#include"Mesh.h"
#include"Texture.h"
#include"shader.h"
#include"Material.h"
#include"Camera.h"
#include <random>


class Model
{
private:
	Material* material;
	Texture* overridetexturediffuse;
	Texture* overridetexturespecular;
	std::vector<Mesh*> meshes;
	glm::vec3 position;

	glm::mat4 ViewWatrix;

	glm::vec3 worldUP;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	GLfloat pitch;
	GLfloat yaw;
	GLfloat vals;

	GLfloat speed;

	


	void updateuniforms()
	{
	
	}

public:
	Model(glm::vec3 position , Material* material, Texture* overtexdiff,Texture* overtexspe, std::vector<Mesh*> meshes)
	{
		
		this->position = position;
		this->material = material;
		this->overridetexturediffuse = overtexdiff;
		this->overridetexturespecular = overtexspe;
		
		for (auto*i : meshes)
		{
			this->meshes.push_back(new Mesh(*i));
		}
		this->speed = 1.f;

	}
	
	Model(glm::vec3 position, Material* material, Texture* overtexdiff, Texture* overtexspe, std::vector<Mesh*> meshes, glm::vec3 direction, glm::vec3 worldUP)
	{

		this->position = position;
		this->material = material;
		this->overridetexturediffuse = overtexdiff;
		this->overridetexturespecular = overtexspe;

		for (auto* i : meshes)
		{
			this->meshes.push_back(new Mesh(*i));
		}
		this->ViewWatrix = glm::mat4(1.f);

		this->speed = 1.f;

		this->worldUP = worldUP;
		this->right = glm::vec3(0.f);
		this->up = worldUP;
		this->vals = 0.f;
		this->pitch = 0.f;
		this->yaw = -90.f;
		setOriginALL(this->position);
	}

	~Model()	
	{
		for (auto* i : this->meshes)
		{
			delete i;
		}
	}

	//functions all 


	void setPositionALL(const glm::vec3 position)
	{
		for (auto* i : this->meshes)
		{
			i->setPosition(position);
		}
	}

	void setOriginALL(const glm::vec3 origin)
	{
		for (auto* i : this->meshes)
		{
			i->setOrigin(origin);
		}
	}


	void setRotationALL(const glm::vec3 rotation)
	{
		for (auto* i : this->meshes)
		{
			i->setRotation(rotation);
		}
	}
	glm::vec3 getRotationALL(const glm::vec3 rotation)
	{
		for (auto* i : this->meshes)
		{
			return i->getRotation();
		}
		
	}
	void setScaleALL(const glm::vec3 scale)
	{
		for (auto* i : this->meshes)
		{
			i->setScale(scale);
		}
	}

	void moveALL(const glm::vec3 position)
	{

		for (auto* i : this->meshes)
		{
			i->move(position);
		}
	}

	void rotateALL(glm::vec3 rotation)
	{

		for (auto* i : this->meshes)
		{
			i->rotate(rotation);
		}
	}

	void scaleUpALL(const glm::vec3 scale)
	{
		for (auto* i : this->meshes)
		{
			i->scaleUp(scale);
		}
	}

	void speedUp(GLfloat s)
	{
		this->speed = s;
	}
	///
	void move(const float& dt, const int direction, GLfloat tempspeed, bool hit)
	{

		
		if (hit == true)
		{
			tempspeed = (tempspeed * -1.f);
		}
		
		switch (direction)
		{
		case FORWARD:
		
			this->position += this->front * tempspeed * dt * this->speed;
			this->position.y = 0.f;
			break;
		case BACKWARD:
			this->position -= this->front * tempspeed * dt * this->speed;
			this->position.y = 0.f;
			break;
		case LEFT:
			this->position -= this->right * tempspeed * dt * this->speed;
			this->position.y = 0.f;
			break;
		case RIGHT:
			this->position += this->right * tempspeed * dt * this->speed;
			this->position.y = 0.f;
			break;

		default:
			break;
		}

		setOriginALL(glm::vec3(this->position.x, this->position.y, this->position.z));
		setPositionALL(glm::vec3(this->position.x, this->position.y, this->position.z));

	}
	void updateVectors()
	{
		this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		this->front.y = sin(glm::radians(this->pitch));
		this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

		this->front = glm::normalize(this->front);
		this->right = glm::normalize(glm::cross(this->front, this->worldUP));
		this->up = glm::normalize(glm::cross(this->right, this->front));
	}
	void updat(const float& dt, glm::vec3 offset, bool hit)
	{
		GLfloat ABx = (0.f - offset.x)/(180.f - offset.z);

		// Find direction ratio of line BC
		GLfloat BCx = ( this->position.x- offset.x)/( this->position.z - offset.z);
		//std::cout << ABx<<" || " << BCx << endl;
		// Store the tan value  of the angle
		GLfloat angle = ((atan(ABx) * 180.f) / 3.14f) - ((atan(BCx) * 180.f) / 3.14f);//((BCx - ABx) / (1.f + ABx * BCx));
		// Calculate tan inverse of the angle
		//GLfloat ret = atan(angle);

		// Convert the angle from
		// radian to degree
		GLfloat val = angle*-1.f;// (ret * 180.f) / 3.14f;
		this->vals -= val;
		//apdate pitch yaw and roll
		//std::cout << val << endl;
		setRotationALL(glm::vec3(0.f, val, 0.f));
		
		this->yaw += this->vals * 50 * dt;
		this->vals = val;
		if (hit == true) {
			if (offset.z <= this->position.z) {
				move(dt, 0, -0.5f, false);
			}
			else {
				move(dt, 0, -0.5f, true);
			}
		}
		else {
			if (offset.z <= this->position.z) {
				move(dt, 0, -0.5f, true);
			}
			else {
				move(dt, 0, -0.5f, false);
			}
		}
		
		
	}
	bool ithit( bool hit ,glm::vec3 offset)
	{
			float tempdis = sqrt(pow((this->position.x - offset.x), 2) + pow((this->position.z - offset.z), 2));
			//std::cout << tempdis << endl;
			if (hit == false && tempdis <= 0.89f) {
				return true;
			}
			else if (hit == true &&  tempdis >=3.88f ) {
				return false;
			}
			else {
				return hit;
			}

		


	}

	//colision

	bool checkrenderdistance(Mesh* mesh, Camera* cam){
		float tempdisX = abs(mesh->GetPosition().x - cam->getPosition().x);
		float tempdisZ = abs(mesh->GetPosition().z - cam->getPosition().z);
		if (tempdisX <= 20.65 && tempdisZ <= 20.65) {
			return true;
		}
		else
		{
			return false;
		}
	}

	GLuint colision(Camera* camera , GLuint point)
	{
		int a =0 ;
		for(auto*i : this->meshes)
		{
			if (i->GetBorder() == true)
			{

				if (i->GetXsite() == true)
				{
					float tempdis = abs(i->GetPosition().x - camera->getPosition().x);
					if (tempdis <= (0.65 * i->GetScale().x) && (abs(camera->getPosition().x - i->GetPosition().x) <= abs(camera->getPosition().z - i->GetPosition().z))) {
						if (camera->getPosition().x < i->GetPosition().x) {
							camera->SetPositionX((float)-0.0999);

						}
						else
						{
							camera->SetPositionX((float)0.0999);
						}

					}
					
				}
				else
				{
					float tempdis = abs(i->GetPosition().z - camera->getPosition().z);
					if (tempdis <= (0.65 * i->GetScale().z) && (abs(camera->getPosition().x - i->GetPosition().x) >= abs(camera->getPosition().z - i->GetPosition().z))) {
						if (camera->getPosition().z < i->GetPosition().z) {
							camera->SetPositionZ((float)-0.0999);

						}
						else
						{
							camera->SetPositionZ((float)0.0999);

						}


					}
					
				}
			}
			else if(i->ISPoint() == true)
			{
				float tempdis = sqrt(pow((i->GetPosition().x - camera->getPosition().x), 2) + pow((i->GetPosition().z - camera->getPosition().z), 2));
				if (tempdis <= (0.65 * i->GetScale().x) || tempdis <= (0.65 * i->GetScale().z))
				{
					
					//std::cout << point << endl;
					
					if (this->meshes.size() < 2) {
						i->setPosition(glm::vec3(0.f, 0.5f, -86.5f));
						i->setOrigin(glm::vec3(0.f, 0.5f, -86.5f));
						point += 1;
					
					}
					else
					{
						this->meshes.erase(this->meshes.begin() + a);
						point += 1;
					}
					
					
				}
			}
			else
			{
				if (camera->getPosition().x >= (i->GetPosition().x + (0.5f * i->GetScale().x)) && abs(camera->getPosition().x - i->GetPosition().x) < (0.5f * i->GetScale().x) + 0.2f)
				{
					if (camera->getPosition().z <= (i->GetPosition().z + (0.5f * i->GetScale().z)) && camera->getPosition().z > (i->GetPosition().z + (-0.5f * i->GetScale().z)))
					{
						if (camera->getPosition().y <= (i->GetPosition().y + (0.5f * i->GetScale().y)) && camera->getPosition().y > (i->GetPosition().y + (-0.5f * i->GetScale().y)))
						{
							camera->SetPositionX((float)0.0999);
						}
					}
				}
				else if (camera->getPosition().x <= (i->GetPosition().x + (-0.5f * i->GetScale().x)) && abs(camera->getPosition().x - i->GetPosition().x) < (0.5f * i->GetScale().x) + 0.2f)
				{
					if (camera->getPosition().z <= (i->GetPosition().z + (0.5f * i->GetScale().z)) && camera->getPosition().z > (i->GetPosition().z + (-0.5f * i->GetScale().z)))
					{
						if (camera->getPosition().y <= (i->GetPosition().y + (0.5f * i->GetScale().y)) && camera->getPosition().y > (i->GetPosition().y + (-0.5f * i->GetScale().y)))
						{
							camera->SetPositionX((float)-0.0999);
						}
					}
				}
				else if (camera->getPosition().z >= (i->GetPosition().z + (0.5f * i->GetScale().z)) && abs(camera->getPosition().z - i->GetPosition().z) < (0.5f * i->GetScale().z) + 0.2f)
				{
					if (camera->getPosition().x <= (i->GetPosition().x + (0.5f * i->GetScale().x)) && camera->getPosition().x > (i->GetPosition().x + (-0.5f * i->GetScale().x)))
					{
						if (camera->getPosition().y <= (i->GetPosition().y + (0.5f * i->GetScale().y)) && camera->getPosition().y > (i->GetPosition().y + (-0.5f * i->GetScale().y)))
						{
							camera->SetPositionZ((float)0.0999);
						}
					}
				}
				else if (camera->getPosition().z <= (i->GetPosition().z + (-0.5f * i->GetScale().z)) && abs(camera->getPosition().z - i->GetPosition().z) < (0.5f * i->GetScale().z) + 0.2f)
				{
					if (camera->getPosition().x <= (i->GetPosition().x + (0.5f * i->GetScale().x)) && camera->getPosition().x > (i->GetPosition().x + (-0.5f * i->GetScale().x)))
					{
						if (camera->getPosition().y <= (i->GetPosition().y + (0.5f * i->GetScale().y)) && camera->getPosition().y > (i->GetPosition().y + (-0.5f * i->GetScale().y)))
						{
							camera->SetPositionZ((float)-0.0999);
						}
					}
				}
				else
				{
					if (camera->GetSpeed() < 0.f)
					{
						camera->Speed(-1.f);
						
					}
				}
				
			}
			a += 1;
		}
		return point;
	}

	GLuint colisionButton(Camera* camera, GLuint point)
	{
		int a = 0;
		float distz;
		float distx;
		
		for (auto* i : this->meshes)
		{
			distz = abs(i->GetPosition().z - camera->getPosition().z);
			distx = abs(i->GetPosition().x - camera->getPosition().x);
			

			if (distz <= 0.7f && distx <= 0.5f) {
				
				if (i->isSTART() == TRUE) {
					std::cout << "Starts: " << endl;
					point = true;

				}
				else if (i->isExit() == TRUE) {
					std::cout << "exit: " << endl;
					point = true;

				}
				else if (i->isReset() == TRUE) {
					std::cout << "resert: " << endl;
					point = true;

				}
				
			}
			else if (distz >= 0.7f || distx >= 0.5f) {
			
				point = false;
		
			}
			
		}
		return point;
	}
	//functions invidual

	int getMeshSize()
	{
		return this->meshes.size();
	}
	void setPositionINV(const glm::vec3 position, GLuint index)
	{

		this->meshes[index]->setPosition(position);

	}
	glm::vec3 GetPositionINV( GLuint index)
	{

		return this->meshes[index]->GetPosition();

	}
	void copyPosition(Model* model, GLuint index)
	{
		model->setPositionINV(glm::vec3(this->meshes[index]->GetPosition().x, model->GetPositionINV(index).y, this->meshes[index]->GetPosition().z), index);

	}
	void setoriginINV(const glm::vec3 origin, GLuint index)
	{
	
			this->meshes[index]->setOrigin(origin);
	}

	void setRotationINV(const glm::vec3 rotation, GLuint index)
	{
		this->meshes[index]->setRotation(rotation);

	}

	glm::vec3 getRotationINV( GLuint index)
	{
			return this->meshes[index]->getRotation();
	}

	void setScaleINV(const glm::vec3 scale, GLuint index)
	{

		this->meshes[index]->setScale(scale);

	}

	void moveINV(const glm::vec3 position, GLuint index)
	{


		this->meshes[index]->move(position);

	}

	void rotateINV(glm::vec3 rotation, GLuint index)
	{


		this->meshes[index]->rotate(rotation);

	}

	void scaleUpINV(const glm::vec3 scale, GLuint index)
	{

		this->meshes[index]->scaleUp(scale);

	}
	
	
	//gems

	bool GemMovement(bool move)
	{

		GLfloat t;
		if (move == true)
		{
			for (auto* i : this->meshes)
			{
				
					t = -0.0025f;
				// 0.005f
				i->move(glm::vec3(0.f, t, 0.f));
				
				
			}
			if (this->meshes[this->meshes.size()-1]->GetPosition().y <= -0.25f)
			{
				move = false;
				
				return move;
			}
			else
			{
				
				return move;
			}
		}
		else
		{
	
			for (auto* i : this->meshes)
			{
			
				t = 0.0025f;
		
				i->move(glm::vec3(0.f, t, 0.f));
				
			} 
			
			if (this->meshes[this->meshes.size() - 1]->GetPosition().y >= 0.f)
			{
				move = true;
				
				return move;
			}
			else
			{
				
					
				return move;
				
			}
		}

	}
	
	//rest


	void Update()
	{

	}

	void Render(Shader* shader,Camera* camera,bool alwaysActive)
	{
		this->updateuniforms();

		//update the uniforms

		//update uniforms
		this->material->sendToShader(*shader);

		//use a program
		//this->shaders[SHADE_CORE_2D]->use();
		//this->text[0]->RenderText(this->shaders[SHADE_CORE_2D], "abc:", 1.f, 300.0f, 1.0f);

		shader->use();
		//temporary close
		
		//activate texture
		this->overridetexturediffuse->bind(0);
		this->overridetexturespecular->bind(1);


		//draw
		for (auto& i : this->meshes)
		{
			if (checkrenderdistance(i, camera) == true || alwaysActive == true) {
				i->render(shader);
			}
			
		}
	

	}

};
//todo 
//1. rotation scale position for all
//2. rotation scale position for invidual