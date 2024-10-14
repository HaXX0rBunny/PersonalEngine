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

}
//Map. Keeps the order the variables were declared in
void Serializer::LoadLevel(const std::string& filename)
{
	//open file
	std::fstream file(filename, std::fstream::in);
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << filename << std::endl;
		return;
	}
	json Alldata;
	file >> Alldata;// the json has all the file data
	file.close();
	for (auto item : Alldata)//Depending on how you saved, you look for some values or others;
	{
		//Create an object IF this is an obj;
		auto obj = item.find("object");//Iterator
		if (obj != item.end())//It was found
		{
			//Create the go 
			GameObject* go = new GameObject(obj.value());//= GOManager::getPtr()->AddObj();
			//Find the component section
			auto cmp = item.find("Components");
			if (cmp == item.end())//NOT FOUND
				continue;

			//Iterate on the Json on cmp for each component, add it
			for (auto& c : *cmp)
			{
				auto it = c.find("Type");
				if (it != c.end() && it.value() == "TransformComp")
				{
					go->LoadComponent("TransformComp")->LoadFromJson(c);
				}
			}

			// 나머지 컴포넌트를 그 후 로드
			for (auto& c : *cmp)
			{
				auto it = c.find("Type");
				if (it != c.end() && it.value() != "TransformComp")
				{
					go->LoadComponent(it.value())->LoadFromJson(c);
				}
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
		object["object"] = go.second;

		json components;
		//iterate on each component
		for (auto& c : go.first->AllComp())
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

void Serializer::DestroyThis()
{
	delete Instance_;
	Instance_ = nullptr;
}
