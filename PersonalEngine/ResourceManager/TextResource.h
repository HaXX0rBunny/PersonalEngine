#pragma once
#include "Resource.h"
class TextResource : public Resource
{
public:
	void Load(const std::string& filename) override;
	void Unload() override;
	void* GetData() const override;

};
