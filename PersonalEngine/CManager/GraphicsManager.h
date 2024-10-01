#pragma once
#include "../Component/GraphicsComponent.h"
#include <vector>
class GraphicsManager
{
    static GraphicsManager* Instance_;
    std::vector<GraphicsComponent*> Component;
    ~GraphicsManager();
public:
    static GraphicsManager* Instance()
    {
        if (!Instance_)
            Instance_ = new GraphicsManager();
        return Instance_;
    }
    //void Render();
    void clear();
    GraphicsComponent* GetComponent(const std::string& str) const;
    void AddComponent(GraphicsComponent* component);
    void RemoveComp(GraphicsComponent* component);
    void Update();
};