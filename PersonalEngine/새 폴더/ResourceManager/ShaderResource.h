#pragma once
#include "../Shader.h"
#include "Resource.h"

class ShaderResource : public Resource
{
	Shader* shader;
public:
	virtual void Load(const std::string& filename);
	void Loadshader(const std::string& vertexFilename, const std::string& fragmentFilename);
	void Unload() override;
	void* GetData() const override;


};