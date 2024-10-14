#pragma once

#include <iostream>
#include <string>
class Serializer
{
	Serializer()=default;
	~Serializer();
	static Serializer* Instance_;
	Serializer(const Serializer& other) = delete;
	const Serializer& operator=(const Serializer& other) = delete;
	//Singleton
public:
	static Serializer* Instance()
	{
		if (Instance_ == nullptr)
		{
			Instance_ = new Serializer;

			std::cout << "Serializer 19: Created Serializer at " << Instance_ << std::endl;
		}
		return Instance_;
	}
	void LoadLevel(const std::string& s);
	void SaveLevel(const std::string& s);
	void DestroyThis();
};