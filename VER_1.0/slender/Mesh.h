#pragma once

#include<iostream>
#include<vector>

#include"Vertex.h"
#include"Primitives.h"
#include"shader.h"
#include"Texture.h"
#include"Material.h"



class Mesh
{
private:

	Vertex* vertexArray;
	unsigned nrOfVertices;
	GLuint* indexArray;
	unsigned nrOfIndices;
	

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 position;
	glm::vec3 origin;
	glm::vec3 rotation;
	glm::vec3 scale;
	bool border;
	bool xSite;
	bool Point;

	bool Start;
	bool Exit;
	bool RESET;
	
	glm::mat4 ModelMatrix;

	
	void initVAO()
	{
		//setvariable
	


		glCreateVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);
		//GEN VBO AND BIND AND SEND DATA

		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(Vertex), this->vertexArray, GL_STATIC_DRAW);

		//GEN EBO AND BIND AND SEND DATA
		if (this->nrOfIndices > 0)
		{
			glGenBuffers(1, &this->EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices * sizeof(GLuint), this->indexArray, GL_STATIC_DRAW);
		}
		//set vertexattribpointers and enable
		//position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);
		//color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);
		//texcoord
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
		glEnableVertexAttribArray(2);
		//normal
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(3);
		//bind VAO 0
		glBindVertexArray(0);
	}

	void UpdateUniforms(Shader* shader)
	{
		shader->setMat4fv(this->ModelMatrix, "ModelMatrix");
	}

	void updateModelMatrix() 
	{
		this->ModelMatrix = glm::mat4(1.f);
		this->ModelMatrix = glm::translate(this->ModelMatrix, this->origin);
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
		this->ModelMatrix = glm::translate(this->ModelMatrix, this->position - this->origin);
		this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);

	}

public:
	Mesh(Vertex* vertexArray, const unsigned nrOfVertices, GLuint* indexArray, const unsigned nrOfIndices, glm::vec3 position = glm::vec3(0.f),  glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f),bool border = false, bool xSite = false, bool Point = false, bool Start = false, bool Exit = false, bool RESET = false, glm::vec3 origin = glm::vec3(-1.f, -1000.f, -1.f))
	{
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
		if (origin != glm::vec3(-1.f, -1000.f, -1.f))
		{
			this->origin = origin;
		}
		else {
			this->origin = this->position;
		}
		
		this->nrOfVertices = nrOfVertices;
		this->nrOfIndices = nrOfIndices;
		this->vertexArray = new Vertex[this->nrOfVertices];
		for (size_t i = 0;i < nrOfVertices; i++)
		{
			this->vertexArray[i] = vertexArray[i];
		}
		this->indexArray = new GLuint[this->nrOfIndices];
		for (size_t i = 0; i < nrOfIndices; i++)
		{
			this->indexArray[i] = indexArray[i];
		}

		this->border = border;
		this->xSite = xSite;
		this->Point = Point;
		this->Start = Start;
		this->Exit = Exit;
		this->RESET = RESET;
		this->initVAO();
		this->updateModelMatrix();
	}

	Mesh(Primitive* primitive, glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f), bool border = false, bool xSite = false, bool Point = false, bool Start = false, bool Exit = false, bool RESET = false, glm::vec3 origin = glm::vec3(-1.f, -1000.f, -1.f))
	{
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
		this->border = border;
		if (origin != glm::vec3(-1.f, -1000.f, -1.f))
		{
			this->origin = origin;
		}
		else {
			this->origin = this->position;
		}

		this->nrOfVertices = primitive->getNrOfVertices();
		this->nrOfIndices = primitive->getNrOfIndices();
		this->vertexArray = new Vertex[this->nrOfVertices];
		for (size_t i = 0; i < this->nrOfVertices; i++)
		{
			this->vertexArray[i] = primitive->getVertices()[i];
		}
		this->indexArray = new GLuint[this->nrOfIndices];
		for (size_t i = 0; i < this->nrOfIndices; i++)
		{
			this->indexArray[i] = primitive->getIndices()[i];
		}
		this->Start = Start;
		this->Exit = Exit;
		this->RESET = RESET;
		this->xSite = xSite;
		this->Point = Point;

		this->initVAO();
		this->updateModelMatrix();
	}


	Mesh(const Mesh& obj)
	{
		this->position = obj.position;
		this->origin = obj.origin;
		this->rotation = obj.rotation;
		this->scale = obj.scale;

		this->nrOfVertices = obj.nrOfVertices;
		this->nrOfIndices = obj.nrOfIndices;
		this->vertexArray = new Vertex[this->nrOfVertices];
		for (size_t i = 0; i < this->nrOfVertices; i++)
		{
			this->vertexArray[i] = obj.vertexArray[i];
		}
		this->indexArray = new GLuint[this->nrOfIndices];
		for (size_t i = 0; i < this->nrOfIndices; i++)
		{
			this->indexArray[i] = obj.indexArray[i];
		}

		this->border = obj.border;
		this->xSite = obj.xSite;
		this->Point = obj.Point;
		this->Start = obj.Start;
		this->Exit = obj.Exit;
		this->RESET = obj.RESET;
		this->initVAO();
		this->updateModelMatrix();
	}


	~Mesh()
	{
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(1, &this->VBO);
		if (this->nrOfIndices > 0)
			glDeleteBuffers(1, &this->EBO);
		delete[] this->vertexArray;
		delete[] this->indexArray;

	}		
	//Accessors

	//Modifiers
	void setPosition(const glm::vec3 position) 
	{
		this->position = position;
	}
	void setOrigin(const glm::vec3 origin)
	{
		this->origin = origin;
	}

	void setRotation(const glm::vec3 rotation)
	{
		this->rotation = rotation;
	}
	glm::vec3 getRotation()
	{
		return this->rotation;
	}
	
	void setScale(const glm::vec3 scale)
	{
		this->scale = scale;
	}
	
	glm::vec3 GetScale()
	{
		return this->scale;
	}

	glm::vec3 GetPosition()
	{
		return this->position;
	}
	
	bool GetBorder() 
	{
		return this->border;
	}

	bool GetXsite() 
	{
		return this->xSite;
	}
	bool isSTART()
	{
		
		return this->Start;
	}
	bool isExit()
	{
		return this->Exit;
	}
	bool isReset()
	{
		return this->RESET;
	}

	bool ISPoint() 
	{
		return this->Point;
	}
	//functions
	void move(const glm::vec3 position)
	{
		this->position += position;
		this->origin += position;
	}

	void rotate(const glm::vec3 rotation)
	{
		this->rotation += rotation;
		if (this->rotation.x > 360 || this->rotation.x < -360)
			this->rotation.x = 0;
		if (this->rotation.y > 360 || this->rotation.y < -360)
			this->rotation.y = 0;
		if (this->rotation.z > 360 || this->rotation.z < -360)
			this->rotation.z = 0;
	}

	void scaleUp(const glm::vec3 scale)
	{
		this->scale += scale;
	}

	void update()
	{
	
	}

	void render(Shader* shader)
	{
		this->updateModelMatrix();
		this->UpdateUniforms(shader);

		shader->use();
		//bind VAO
		glBindVertexArray(this->VAO);

		//render
		if (this->nrOfIndices == 0)
		{
			glDrawArrays(GL_TRIANGLES, 0,this->nrOfVertices);
		}
		else
		{
			glDrawElements(GL_TRIANGLES, this->nrOfIndices, GL_UNSIGNED_INT, 0);
		}
		
		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	

};