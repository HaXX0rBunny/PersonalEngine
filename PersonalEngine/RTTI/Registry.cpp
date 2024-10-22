#include "Registry.h"
#include "../Component/TransformComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Component/PlayerComponent.h"
#include "../Component/RigidbodyComponent.h"
Registry* Registry::Instance_ = nullptr;  

Registry::Registry()
{
    //Register All the functions


 
    rttiMap.insert({ "RigidbodyComp", &RigidbodyComp::CreateRigidbodyComp });
    rttiMap.insert({ "PlayerComp", &PlayerComp::CreatePlayerComp });
    rttiMap.insert({ "SpriteComp", &SpriteComp::CreateSpriteComp });
    rttiMap.insert({ "TransformComp", &TransformComp::CreateTransformComp });
}
Registry::~Registry()
{

    rttiMap.clear();
}




void Registry::Delete()
{

    //Instance()->rttiMap.clear();
    if (Instance_ != nullptr)
    {
        delete Instance_;
        Instance_ = nullptr;
    }
}

BaseRTTI* Registry::FindAndCreate(const std::string& type)///<<< 
{
    auto it = rttiMap.find(type);
    if (it == rttiMap.end())
    {
        return nullptr;// if not found   
    }
    if (it->second == nullptr)
    {
        return nullptr;  // No function registered for this type
    }
    return it->second();
 //final find create somethiong
}
