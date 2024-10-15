#pragma once
#include <map>
#include <string>

#include "Resource.h"
#include "MusicResource.h"
#include "TextResource.h"
#include <iostream>
class ResourceManager
{
	static ResourceManager* Instance_;
	ResourceManager() {};
	ResourceManager(const ResourceManager& other) = delete;
	const ResourceManager& operator= (const ResourceManager& other) = delete;
	~ResourceManager();
	std::map<std::string, Resource*> ResourceContainer;

	enum FileExt
	{
		unvalid,
		png,
		jpg,
		wav,
		mp3,
		vert,
		frag
	};
public:

	static ResourceManager* GetInstance()
	{
		if (Instance_ == nullptr)
		{
			Instance_ = new ResourceManager;
			std::cout << "ResourceManager 35: Created ResourceManager at " << Instance_ << std::endl;
		}
		return Instance_;
	}
	template <typename T>
	T* GetResource(const std::string& filename);
	FileExt GetFileExt(const std::string& filename);
	void UnloadResource(const std::string& filename);
	void Clear();

};

#include "ResourceManager.inl"
