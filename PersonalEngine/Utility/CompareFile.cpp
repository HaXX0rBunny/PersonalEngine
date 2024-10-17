#include"CompareFile.h"
nlohmann::ordered_json currentData;
nlohmann::ordered_json originalData;
/*
    input filePath 
    if New 
    Return bool (new Data Check !Empty)
    
    if Open
    Compare FilePath Data == Current Level Data
    Return bool (it modified?)

*/
bool IsDataModified(const std::string& filePath)
{

    if (filePath == "None.json")
    {

        json newData;
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
            newData.push_back(object);
        }
        return !newData.empty();
    }
    

    json ALLdata;
    std::fstream file(filePath, std::fstream::in);
    if (!file.is_open()) {
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

