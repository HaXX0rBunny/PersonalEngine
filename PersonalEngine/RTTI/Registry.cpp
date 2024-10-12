#include "Registry.h"
#include "../Component/TransformComponent.h"
#include "../Component/SpriteComponent.h"
Registry* Registry::Instance_ = nullptr;  

Registry::Registry()
{
    //Register All the functions


    
    rttiMap.insert(std::pair<std::string, BaseRTTI * (*)()>("SpriteComp", SpriteComp::CreateSpriteComp));
    rttiMap.insert(std::pair<std::string, BaseRTTI * (*)()>("TransformComp", TransformComp::CreateTransformComp));
}
Registry::~Registry()
{
    Delete();
}




void Registry::Delete()
{
    if (Instance_ != nullptr)
        delete Instance_;
    Instance_ = nullptr;
}

BaseRTTI* Registry::FindAndCreate(const std::string& type)///<<< 
{
    if (rttiMap.find(type) == rttiMap.end())
    {
        return nullptr;// if not found   
    }
    if (rttiMap.find(type)->second() == nullptr)// if have not function;
        return nullptr;
    return rttiMap.find(type)->second();
 //final find create somethiong
}
