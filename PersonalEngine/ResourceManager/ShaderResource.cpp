#include "ShaderResource.h"
#include <iostream>
#include <string>

void ShaderResource::Load(const std::string& filename)
{
    if (!shader)
    {
        std::string vertPath = filename + ".vert";
        std::string fragPath = filename + ".frag";
        std::cout << "Loading vertex shader: " << vertPath << std::endl;
        std::cout << "Loading fragment shader: " << fragPath << std::endl;

        shader = new Shader(vertPath.c_str(), fragPath.c_str());

        std::cout << "ShderResource 16: Created Shader at " << shader << std::endl;

        if (shader->ID == 0)
        {
            std::cerr << "Failed to load shader: " << filename << std::endl;
            delete shader;
            shader = nullptr;
        }
    }
    data = shader;
}
void ShaderResource::Loadshader(const std::string& vertexFilename, const std::string& fragmentFilename)
{
    if (!shader)
    {
        // 개별 파일 경로 설정
        std::string vertPath = vertexFilename + ".vert";
        std::string fragPath = fragmentFilename + ".frag";

        std::cout << "Loading vertex shader: " << vertPath << std::endl;
        std::cout << "Loading fragment shader: " << fragPath << std::endl;

        // 셰이더 생성 및 로드
        shader = new Shader(vertPath.c_str(), fragPath.c_str());

        std::cout << "ShderResource 41: Created Shader at " << shader << std::endl;

        if (shader->ID == 0)
        {
            std::cerr << "Failed to load shader: " << vertexFilename << " and " << fragmentFilename << std::endl;
            delete shader;
            shader = nullptr;
        }
    }
    data = shader;
}
void ShaderResource::Unload()
{
    if (shader)
    {
        shader->deleteProgram();  
        delete shader; 
        shader = nullptr;
        data = nullptr;
        counter--;
    }
}

void* ShaderResource::GetData() const
{
    return shader;
}
