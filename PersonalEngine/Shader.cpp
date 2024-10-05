#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	//1. file path to search vertex/fragment shader source
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ifstream objects can throw exceptions
	vShaderFile.exceptions(std::ifstream::failbit|std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{

		//https://heinleinsgame.tistory.com/8
	}
	catch (std::ifstream::failure e)
	{
	
	}
}
