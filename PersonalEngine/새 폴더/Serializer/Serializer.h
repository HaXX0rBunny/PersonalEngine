#pragma once

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
			Instance_ = new Serializer;
		return Instance_;
	}
	void LoadLevel(const std::string& s);
	void SaveLevel(const std::string& s);
};