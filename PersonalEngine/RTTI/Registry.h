#pragma once
#include "BaseRTTI.h"
#include <string>
#include <map>

#include <iostream>
class Registry
{
	//Singleton
	static Registry* Instance_;
	Registry(); //Default contstruct
	~Registry(); // Destructor
	//Prevent copies
	Registry(const Registry&) = delete; //Resgistry a(b); Registry a= b;
	const Registry& operator=(const Registry&) = delete;  //a=b;

	//map with names/function_pointer
	std::map<std::string, BaseRTTI* (*)()> rttiMap;
public:
	//Singleton interface;
	static Registry* Instance() {
		if (Instance_ == nullptr)
		{
			Instance_ = new Registry;


			std::cout << "Registry 26: Created Registry at " << Instance_ << std::endl;
		}
		return Instance_;
	};
	static void Delete();
	
	//Some interface to find inside me
	//TODO: 
	BaseRTTI* FindAndCreate(const std::string& type);

};