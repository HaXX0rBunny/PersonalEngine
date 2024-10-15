#pragma once
#ifndef SHADER_H
#define SHADER_H
#include <gl.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
	void checkCompileErrors(unsigned int shader, std::string type);
public:
	//program ID
	
	GLuint ID;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value)const;
	void setFloat (const std::string& name, float value)const;
	void deleteProgram();

};

#endif SHADER_H