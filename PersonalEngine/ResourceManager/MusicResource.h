#pragma once
#pragma once
#include "Resource.h"

class MusicResource : public Resource
{
	char mAudio;// not now
	char mGroup; // not now
public:


	void Load(const std::string& filename) override;
	void Unload() override;
	void* GetData() const override;

};