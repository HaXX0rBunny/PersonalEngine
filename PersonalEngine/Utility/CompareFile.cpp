#include"CompareFile.h"
nlohmann::ordered_json currentData;
nlohmann::ordered_json originalData;

bool IsDataModified(const std::string& filePath)
{
    json ALLdata;
    std::fstream file(filePath, std::fstream::in);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return true;  
    }

    json OriginData;
    file >> OriginData;  
    file.close();


    for (auto go : GameObjectManager::Instance()->AllObj())
    {
        json object;
        object["object"] = go.first;

        json components;

        for (auto& c : go.second->AllComp())
        {
            BaseComponent* comp = c.second;
            components.push_back(comp->SaveToJson());  
        }
        object["Components"] = components;
        ALLdata.push_back(object);
    }


    return OriginData != ALLdata;  
}

