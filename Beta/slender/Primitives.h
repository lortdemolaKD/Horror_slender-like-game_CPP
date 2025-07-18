#pragma once
#include<glew.h>
#include<glfw3.h>

#include<vector>
#include"Vertex.h"

class Primitive
{
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;


public:
	Primitive() {}
	virtual ~Primitive() {}

	//Functions
	void set(const Vertex* vertices, const unsigned nrOfVertices, const GLuint* indices, const unsigned nrOfIndices)
	{
		for (size_t i = 0; i < nrOfVertices; i++)
		{
			this->vertices.push_back(vertices[i]);
		}
		for (size_t i = 0; i < nrOfIndices; i++)
		{
			this->indices.push_back(indices[i]);
		}
	}

	inline Vertex* getVertices() { return this->vertices.data(); }
	inline GLuint* getIndices() { return this->indices.data(); }
	inline const unsigned getNrOfVertices(){ return this->vertices.size(); }
	inline const unsigned getNrOfIndices(){ return this->indices.size(); }
};

class Quad : public Primitive
{
public:
	Quad() : Primitive()
	{
		Vertex vertices[] =
		{
			//positon                          //color                         //texcoord               //normal
			glm::vec3(-0.5f, 0.5f, 0.f),    glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.f),   glm::vec3(0.f, 1.f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f,-0.5f, 0.f),		glm::vec3(0.f, 0.f, 1.f),	glm::vec2(1.f, 0.f),	glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, 0.5f, 0.f),		glm::vec3(1.f, 1.f, 0.f),	glm::vec2(1.f, 1.f),	glm::vec3(0.f, 0.f, 1.f)

		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0, 1, 2, //tiangle1
			0, 2, 3 //tiangle2
		};
		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
};

class Quad_terrain : public Primitive
{
public:
	Quad_terrain() : Primitive()
	{
		Vertex vertices[] =
		{
			//positon                          //color                         //texcoord               //normal
			glm::vec3(-0.5f, 0.5f, 0.f),    glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.f, 70.f),	glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.f),   glm::vec3(0.f, 1.f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f,-0.5f, 0.f),		glm::vec3(0.f, 0.f, 1.f),	glm::vec2(70.f, 0.f),	glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, 0.5f, 0.f),		glm::vec3(1.f, 1.f, 0.f),	glm::vec2(70.f, 70.f),	glm::vec3(0.f, 0.f, 1.f)

		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0, 1, 2, //tiangle1
			0, 2, 3 //tiangle2
		};
		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
};

class Triangle: public Primitive
{
public:
	Triangle() : Primitive()
	{
		Vertex vertices[] =
		{
			//positon                          //color                         //texcoord               //normal
			glm::vec3(-0.5f, 0.5f, 0.f),    glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.f),   glm::vec3(0.f, 1.f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f,-0.5f, 0.f),		glm::vec3(0.f, 0.f, 1.f),	glm::vec2(1.f, 0.f),	glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, 0.5f, 0.f),		glm::vec3(1.f, 1.f, 0.f),	glm::vec2(1.f, 1.f),	glm::vec3(0.f, 0.f, 1.f)

		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0, 1, 2//tiangle1
			
		};
		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
};

class Piramide : public Primitive
{
public:
	Piramide() : Primitive()
	{
		Vertex vertices[] =
		{
			//positon                          //color                         //texcoord               //normal
			//triangle front
			glm::vec3(0.f, 0.5f, 0.f),			glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.5f, 1.f),	glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),		glm::vec3(0.f, 1.f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f,-0.5f, 0.5f),		glm::vec3(0.f, 0.f, 1.f),	glm::vec2(1.f, 0.f),	glm::vec3(0.f, 0.f, 1.f),
			
			//triangle left
			glm::vec3(0.f, 0.5f, 0.f),			glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.5f, 1.f),	glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec3(0.f, 1.f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(-0.5f,-0.5f, 0.5f),		glm::vec3(0.f, 0.f, 1.f),	glm::vec2(1.f, 0.f),	glm::vec3(-1.f, 0.f, 0.f),

			//triangle back
			glm::vec3(0.f, 0.5f, 0.f),			glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.5f, 1.f),	glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.5f, -0.5f, -0.5f),		glm::vec3(0.f, 1.f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(-0.5f,-0.5f, -0.5f),		glm::vec3(0.f, 0.f, 1.f),	glm::vec2(1.f, 0.f),	glm::vec3(0.f, 0.f, -1.f),

			//triangle write
			glm::vec3(0.f, 0.5f, 0.f),			glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.5f, 1.f),	glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.5f, -0.5f, 0.5f),		glm::vec3(0.f, 1.f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.5f,-0.5f, -0.5f),		glm::vec3(0.f, 0.f, 1.f),	glm::vec2(1.f, 0.f),	glm::vec3(1.f, 0.f, 0.f)



		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		this->set(vertices, nrOfVertices, nullptr, 0);
	}
	//make box

};

class Teseract : public Primitive
{
public:
	Teseract() : Primitive()
	{
		Vertex vertices[] =
		{
			//positon                          //color                         //texcoord               //normal
			//triangle front 1
			glm::vec3(0.f, 0.5f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.5f, 1.f), glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f), glm::vec3(0.f, 0.f, 1.f),

			//triangle left 1
			glm::vec3(0.f, 0.5f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.5f, 1.f), glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f), glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f), glm::vec3(-1.f, 0.f, 0.f),

			//triangle back 1
			glm::vec3(0.f, 0.5f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.5f, 1.f), glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f), glm::vec3(0.f, 0.f, -1.f),

			//triangle right 1
			glm::vec3(0.f, 0.5f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.5f, 1.f), glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f), glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f), glm::vec3(1.f, 0.f, 0.f),


			//triangle front 21.f, 0.f
			glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(1.f, 0.f), glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.f, -1.f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(0.5f, 1.f), glm::vec3(0.f, 0.f, 1.f),

			//triangle left 2
			glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(1.f, 0.f), glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f), glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(0.f,  -1.f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(0.5f, 1.f), glm::vec3(-1.f, 0.f, 0.f),

			//triangle back 2
			glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(1.f, 0.f), glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.f,  -1.f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(0.5f, 1.f), glm::vec3(0.f, 0.f, -1.f),

			//triangle right 2
			glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(1.f, 0.f), glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f), glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.f,  -1.f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(0.5f, 1.f), glm::vec3(1.f, 0.f, 0.f)



		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		this->set(vertices, nrOfVertices, nullptr, 0);
	}
	//make box

};

class Cube : public Primitive
{
public:
	Cube() : Primitive()
	{
		Vertex vertices[] =
		{
			//positon                          //color                         //texcoord               //normal
			//triangle front
			glm::vec3(-0.5f, 0.5f, 0.5f),		glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(-1.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),		glm::vec3(0.f, 1.f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(-1.f, 0.f, 1.f),
			glm::vec3(0.5f,-0.5f, 0.5f),		glm::vec3(0.f, 0.f, 1.f),	glm::vec2(150.f, 0.f),	glm::vec3(1.f, 0.f, 1.f),
			glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec3(1.f, 1.f, 0.f),	glm::vec2(150.f, 1.f),	glm::vec3(1.f, 0.f, 1.f),

			glm::vec3(0.5f, 0.5f, -0.5f),		glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(1.f, 0.f, -1.f),
			glm::vec3(0.5f,-0.5f, -0.5f),		glm::vec3(0.f, 1.f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(1.f, 0.f, -1.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec3(0.f, 0.f, 1.f),	glm::vec2(150.f, 0.f),	glm::vec3(-1.f, 0.f, -1.f),
			glm::vec3(-0.5f, 0.5f, -0.5f),		glm::vec3(1.f, 1.f, 0.f),	glm::vec2(150.f, 1.f),	glm::vec3(-1.f, 0.f, -1.f),




		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0, 1, 2,//tiangle1
			0, 2, 3,

			7, 6, 1,
			7, 1, 0,

			4, 5, 6,
			4, 6, 7,

			3, 2, 5,
			3, 5, 4
		};

		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
	//make box

};

class Cube2 : public Primitive
{
public:
	Cube2() : Primitive()
	{
		Vertex vertices[] =
		{
			//positon                          //color                         //texcoord               //normal
			//triangle front
			glm::vec3(-0.5f, 0.5f, 0.5f),		glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.f, 3.f),	glm::vec3(-1.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),		glm::vec3(0.f, 1.f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(-1.f, 0.f, 1.f),
			glm::vec3(0.5f,-0.5f, 0.5f),		glm::vec3(0.f, 0.f, 1.f),	glm::vec2(1.f, 0.f),	glm::vec3(1.f, 0.f, 1.f),
			glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec3(1.f, 1.f, 0.f),	glm::vec2(1.f, 1.f),	glm::vec3(1.f, 0.f, 1.f),

			glm::vec3(0.5f, 0.5f, -0.5f),		glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.f, 3.f),	glm::vec3(1.f, 0.f, -1.f),
			glm::vec3(0.5f,-0.5f, -0.5f),		glm::vec3(0.f, 1.f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(1.f, 0.f, -1.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec3(0.f, 0.f, 1.f),	glm::vec2(1.f, 0.f),	glm::vec3(-1.f, 0.f, -1.f),
			glm::vec3(-0.5f, 0.5f, -0.5f),		glm::vec3(1.f, 1.f, 0.f),	glm::vec2(1.f, 1.f),	glm::vec3(-1.f, 0.f, -1.f),

			
			//Position								//Color							//Texcoords					//Normals
			glm::vec3(-0.5f, -0.5f, 0.5f),		glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),//8
			glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),//9 t
			glm::vec3(0.5f,-0.5f, -0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),//10 t
			glm::vec3(0.5f, -0.5f, 0.5f),		glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f)//11
		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] ={
		
			0, 1, 2,//tiangle1
			0, 2, 3,

			7, 6, 1,
			7, 1, 0,

			4, 5, 6,
			4, 6, 7,

			3, 2, 5,
			3, 5, 4,

			8, 9, 10,	//Triangle 1
			8, 10,11		//Triangle 2
		};

		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
	//make box

};

class Hex : public Primitive
{
public:
	Hex() : Primitive()
	{
		Vertex vertices[] =
		{
			//positon                          //color                         //texcoord               //normal
			//triangle front
			glm::vec3(-0.5f, 0.5f, 0.5f),		glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(-1.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),		glm::vec3(0.f, 1.f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(-1.f, 0.f, 1.f),
			glm::vec3(0.5f,-0.5f, 0.5f),		glm::vec3(0.f, 0.f, 1.f),	glm::vec2(1.f, 0.f),	glm::vec3(1.f, 0.f, 1.f),
			glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec3(1.f, 1.f, 0.f),	glm::vec2(1.f, 1.f),	glm::vec3(1.f, 0.f, 1.f),

			glm::vec3(0.5f, 0.5f, -0.5f),		glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(1.f, 0.f, -1.f),
			glm::vec3(0.5f,-0.5f, -0.5f),		glm::vec3(0.f, 1.f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(1.f, 0.f, -1.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec3(0.f, 0.f, 1.f),	glm::vec2(1.f, 0.f),	glm::vec3(-1.f, 0.f, -1.f),
			glm::vec3(-0.5f, 0.5f, -0.5f),		glm::vec3(1.f, 1.f, 0.f),	glm::vec2(1.f, 1.f),	glm::vec3(-1.f, 0.f, -1.f),




		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0, 1, 2,//tiangle1
			0, 2, 3,

			7, 6, 1,
			7, 1, 0,

			4, 5, 6,
			4, 6, 7,

			3, 2, 5,
			3, 5, 4
		};
		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
	//make box

};

class Cross : public Primitive
{
public:
	Cross() : Primitive()
	{
		Vertex vertices[] =
		{
			//positon                          //color                         //texcoord               //normal
			//triangle front
			glm::vec3(-0.25f, 0.0f, 0.f),		glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(-1.f, 0.f, 1.f),
			glm::vec3(-0.25f, -0.5f, 0.f),	glm::vec3(0.f, 1.f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(-1.f, 0.f, 1.f),
			glm::vec3(0.25f,-0.5f, 0.f),		glm::vec3(0.f, 0.f, 1.f),	glm::vec2(1.f, 0.f),	glm::vec3(1.f, 0.f, 1.f),
			glm::vec3(0.25f, 0.0f, 0.f),		glm::vec3(1.f, 1.f, 0.f),	glm::vec2(1.f, 1.f),	glm::vec3(1.f, 0.f, 1.f),

			glm::vec3(0.25f, 0.0f, -0.001f),		glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(1.f, 0.f, -1.f),
			glm::vec3(0.25f,-0.5f, -0.001f),		glm::vec3(0.f, 1.f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(1.f, 0.f, -1.f),
			glm::vec3(-0.25f, -0.5f, -0.001f),	glm::vec3(0.f, 0.f, 1.f),	glm::vec2(1.f, 0.f),	glm::vec3(-1.f, 0.f, -1.f),
			glm::vec3(-0.25f, 0.0f, -0.001f),		glm::vec3(1.f, 1.f, 0.f),	glm::vec2(1.f, 1.f),	glm::vec3(-1.f, 0.f, -1.f),


			glm::vec3(-0.001f, 0.0f, 0.25f),		glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(-1.f, 0.f, 1.f),
			glm::vec3(-0.001f, -0.5f, 0.25f),		glm::vec3(0.f, 1.f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(-1.f, 0.f, 1.f),
			glm::vec3(0.f,-0.5f, 0.25f),		glm::vec3(0.f, 0.f, 1.f),	glm::vec2(1.f, 0.f),	glm::vec3(1.f, 0.f, 1.f),
			glm::vec3(0.f, 0.0f, 0.25f),		glm::vec3(1.f, 1.f, 0.f),	glm::vec2(1.f, 1.f),	glm::vec3(1.f, 0.f, 1.f),

			glm::vec3(0.f, 0.0f, -0.25f),		glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(1.f, 0.f, -1.f),
			glm::vec3(0.f,-0.5f, -0.25f),		glm::vec3(0.f, 1.f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(1.f, 0.f, -1.f),
			glm::vec3(-0.001f, -0.5f, -0.25f),	glm::vec3(0.f, 0.f, 1.f),	glm::vec2(1.f, 0.f),	glm::vec3(-1.f, 0.f, -1.f),
			glm::vec3(-0.001f, 0.0f, -0.25f),		glm::vec3(1.f, 1.f, 0.f),	glm::vec2(1.f, 1.f),	glm::vec3(-1.f, 0.f, -1.f),




		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0, 1, 2,//tiangle1
			0, 2, 3,

			7, 6, 1,
			7, 1, 0,

			4, 5, 6,
			4, 6, 7,

			3, 2, 5,
			3, 5, 4,



			8, 9, 10,//tiangle1
			8, 10, 11,

			15, 14, 9,
			15, 9, 8,

			12, 13, 14,
			12, 14, 15,

			11, 10, 13,
			11, 13, 12,

		};

		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
};
