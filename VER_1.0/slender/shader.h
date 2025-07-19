#pragma once
#include<iostream>
#include<fstream>
#include<string>

#include<glew.h>
#include<glfw3.h>

#include<glm.hpp>
#include<vec2.hpp>
#include<vec3.hpp>
#include<vec4.hpp>
#include<mat4x4.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>

using namespace std;

class Shader
{
private:
	//member variables
	GLuint id;
	const int versionMajor;
	const int versionMinor;
	//priv functions
	string loadShaderSorce(char* filename) 
	{
		string temp = "";
		string src = "";

		ifstream in_file;

		//vertex
		in_file.open(filename);

		if (in_file.is_open())
		{
			while (getline(in_file, temp))
				src += temp + "\n";
		}
		else
		{
			cout << "ERROR::SHADER::COULD_NOT_OPEN_FILE: " << filename << endl;
		}

		in_file.close();

		string version = to_string(versionMajor) + to_string(versionMinor) + "0";
		src.replace(src.find("#version"), 12, ("#version " + version));
		return src;
	}

	GLuint loadShader(GLuint type, char* filename)
	{
		
		char infolog[512];
		GLint success;

		GLuint shader = glCreateShader(type);
		string str_src = this->loadShaderSorce(filename);
		const GLchar* src = str_src.c_str();
		glShaderSource(shader, 1, &src, NULL);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infolog);
			cout << "ERROR::SHADER::COULD_NOT_COMPILE_SHADER: " << filename << endl << infolog << endl;
		}

		return shader;
	}

	void linkprogram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader)
	{
		char infolog[512];
		GLint success;

		this->id = glCreateProgram();

		glAttachShader(this->id, vertexShader);

		if (geometryShader)
			glAttachShader(this->id, geometryShader);
		
		glAttachShader(this->id, fragmentShader);

		glLinkProgram(this->id);

		glGetProgramiv(this->id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->id, 512, NULL, infolog);
			cout << "ERROR::SHADER::COULD_NOT_LINK_PROGRAM" << endl << infolog << endl;
			
		}

		glUseProgram(0);
	}


public:
	
	Shader(const int versionMajor,const int versionMinor, char* vertexfile, char* fragmentfile, char* geometryfile = (char*)"")
		: versionMajor(versionMajor),versionMinor(versionMinor)
	{
		GLuint vertexShader = 0;
		GLuint geometryShader = 0;
		GLuint fragmentShader = 0;

		vertexShader = loadShader(GL_VERTEX_SHADER, vertexfile);

		if (geometryfile != "")
			geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryfile);

		fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentfile);

		this->linkprogram(vertexShader, geometryShader, fragmentShader);

		//end
		glDeleteShader(vertexShader);
		glDeleteShader(geometryShader);
		glDeleteShader(fragmentShader);
	}

	~Shader()
	{
		glDeleteProgram(this->id);
	}

	void use()
	{
		glUseProgram(this->id);
	}

	void UNuse()
	{
		glUseProgram(0);
	}

	GLuint getID() 
	{
		return this->id;
	}

	void set1i(GLint value, const GLchar* name)
	{
		this->use();

		glUniform1i(glGetUniformLocation(this->id, name), value);

		this->UNuse();
	}

	void set1f(GLfloat value, const GLchar* name)
	{
		this->use();

		glUniform1f(glGetUniformLocation(this->id, name), value);

		this->UNuse();
	}

	void setVec2f(glm::fvec2 value, const GLchar* name)
	{
		this->use();

		glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

		this->UNuse();
	}

	void setVec3f(glm::fvec3 value,const GLchar* name)
	{
		this->use();
		
		glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

		this->UNuse();
	}

	void setVec4f(glm::fvec4 value, const GLchar* name)
	{
		this->use();

		glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

		this->UNuse();
	}

	void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE)
	{
		this->use();

		glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

		this->UNuse();
	}

	void setMat4fv(glm::mat4 value, const GLchar* name,GLboolean transpose = GL_FALSE)
	{
		this->use();

		glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

		this->UNuse();
	}

	//set uniform functions

};