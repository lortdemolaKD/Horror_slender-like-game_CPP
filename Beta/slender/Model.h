#pragma once
#include"Mesh.h"
#include"Texture.h"
#include"shader.h"
#include"Material.h"
#include"Camera.h"
#include <random>
struct Foo
{
	bool v1;
	bool v2;
};

class Model
{
private:
	Material* material;
	Texture* overridetexturediffuse;
	Texture* overridetexturespecular;
	std::vector<Mesh*> meshes;
	glm::vec3 position;
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

	void setRotationALL(const glm::vec3 rotation)
	{
		for (auto* i : this->meshes)
		{
			i->setRotation(rotation);
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



	//colision


	GLuint colision(Camera* camera , GLuint point)
	{
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
					i->setPosition(glm::vec3(0, -2, 0));
					point += 1;
					
				}
			}
			else
			{
				float tempdis = sqrt(pow((i->GetPosition().x - camera->getPosition().x), 2) + pow((i->GetPosition().z - camera->getPosition().z), 2));
				if (tempdis <= (0.65 * i->GetScale().x) && (abs(camera->getPosition().x - i->GetPosition().x) > abs(camera->getPosition().z - i->GetPosition().z))) {
					if (camera->getPosition().x < i->GetPosition().x) {
						camera->SetPositionX((float)-0.0999);
					}
					else
					{
						camera->SetPositionX((float)0.0999);
					}

				}
				if (tempdis <= (0.65 * i->GetScale().z) && (abs(camera->getPosition().x - i->GetPosition().x) < abs(camera->getPosition().z - i->GetPosition().z))) {
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

	void setRotationINV(const glm::vec3 rotation, GLuint index)
	{

		this->meshes[index]->setRotation(rotation);

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

	Foo GemMovement(bool move, bool sch)
	{

		GLfloat t;
		if (move == true)
		{
			int c = 1;
			if (sch == false)
			{
				c = 2;
			}
			
			for (auto* i : this->meshes)
			{
				c += 1;
				
				if (c%2 == 0) {
					t = -0.0025f;
				}
				else {
					t = 0.0025f;
				}
				// 0.005f
				i->move(glm::vec3(0.f, t, 0.f));
				
				
			}
			if (this->meshes[0]->GetPosition().y <= -0.25f)
			{
				move = false;
				Foo res = { move, sch };
				return res;
			}
			else
			{
				Foo res = { move, sch };
				return res;
			}
		}
		else
		{
			int c = 1;
			if (sch == false)
			{
				c = 2;
			}
			for (auto* i : this->meshes)
			{
				c += 1;
				if (c % 2 == 0) {
					t = 0.0025f;
				}
				else {
					t = -0.0025f;
				}

				i->move(glm::vec3(0.f, t, 0.f));
				
			}
			
			if (this->meshes[0]->GetPosition().y >= 0.f)
			{
				if (sch == true) 
				{
					sch = false; 
		
				}
				else
				{ 
					sch = true; 
			
				}
				move = true;
				Foo res = { move, sch };
				return res;
			}
			else
			{
				{
					Foo res = { move, sch };
					return res;
				}
			}
		}

	}
	
	//rest


	void Update()
	{

	}

	void Render(Shader* shader)
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
			i->render(shader);
		}
	

	}

};
//todo 
//1. rotation scale position for all
//2. rotation scale position for invidual