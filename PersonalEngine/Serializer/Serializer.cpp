#include "Serializer.h"
#include "json.hpp"
#include <fstream>
//Architecture dependant
#include "../GameObjectManager/GameObjectManager.h"
#include "../GameObject/GameObject.h"
#include "../Component/BaseComponent.h"
#include "../RTTI/Registry.h"
//using json = nlohmann::json; //Map. order alphebetically on pushback and insert
using json = nlohmann::ordered_json;
Serializer* Serializer::Instance_ = nullptr; 
Serializer::~Serializer()
{
	delete Instance_;
	Instance_ = nullptr;
}
//Map. Keeps the order the variables were declared in
void Serializer::LoadLevel(const std::string& filename)
{
	//open file
	std::fstream file;
	file.open(filename, std::fstream::in);
	//Check the file is valid

	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << filename << std::endl;
		return;
	}
	json Alldata;
	file >> Alldata;// the json has all the file data
	for (auto item : Alldata)//Depending on how you saved, you look for some values or others;
	{
		//Create an object IF this is an obj;
		auto obj = item.find("Object");//Iterator
		if (obj != item.end())//It was found
		{
			//Create the go 
			GameObject* go = new GameObject;//= GOManager::getPtr()->AddObj();
			//Find the component section
			auto cmp = item.find("Components");
			if (cmp == item.end())//NOT FOUND
				continue;

			//Iterate on the Json on cmp for each component, add it
			for (auto& c : *cmp)
			{
				auto it = c.find("Type");
				if (it == c.end())// Not found
					continue;

				std::string typeName =it.value().dump(); // convert to string

				//Look in the registry for this type and create it
				BaseRTTI* p=Registry::Instance()->FindAndCreate(typeName);
				if (p != nullptr)
					p->LoadFromJson(c);
				//Add the comp to the Go
				go->AddComponent<BaseComponent>(static_cast<BaseComponent*>(p));
			}
			GameObjectManager::Instance()->AddObj(go);
		}
	}
}

void Serializer::SaveLevel(const std::string& filename)
{
	json ALLdata;
    
	int i = 0;
	//iteratre on each go
	for (auto go : GameObjectManager::Instance()->AllObj())
	{
		json object;
		object["object"] = i++;

		json components;
		//iterate on each component
		for (auto& c : go.second->AllComp())
		{
			BaseComponent* comp = c.second;
			components.push_back(comp->SaveToJson());//Check in  a moment
		}
		object["Components"] = components;
		ALLdata.push_back(object);
	}
	//iterate on each go

	//file open
	std::fstream file;
	file.open(filename, std::fstream::out); //Open as write mode. Create it if it does not exits!

	if (!file.is_open())
	{
		std::cout << "null" << "\n";
		return;
	}
	//file <<ALLdata;				//ALL is 1 line
	file << std::setw(2) << ALLdata;
	file.close();

}
