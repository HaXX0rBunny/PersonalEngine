#include "ComponentManager.h"
template<typename T>
ComponentManager<T>* ComponentManager<T>::Instance_ = nullptr;

template <typename T>
ComponentManager<T>::ComponentManager()
{
 
    
}

template<typename T>
inline ComponentManager<T>::~ComponentManager()
{
    

}
template<typename T>
inline void ComponentManager<T>::Clear()
{
    // Clear all components and delete them
    for (auto comp : Component) {  // Correct usage without 'this'
        delete comp;  // Ensure 'comp' is a pointer
    }
    Component.clear();
}

template<typename T>
inline void ComponentManager<T>::DestroyInstance()
{
    if (Instance_) {

        delete Instance_;
        Instance_ = nullptr;
    }
}
template<typename T>
inline T* ComponentManager<T>::GetComponent(const std::string& str) const
{
    for (auto a : Component)
        if (a->GetType() == str)
            return a;
    return nullptr;
}

template<typename T>
inline void ComponentManager<T>::AddComponent(T* component)
{
    PendingComp.push_back(component);
}


template<typename T>
inline void ComponentManager<T>::RemoveComp(T* component)
{
    auto it = std::find(Component.begin(), Component.end(), component);
    if (it != Component.end()) {
        Component.erase(it);  
    }
}


template<typename T>
inline void ComponentManager<T>::Update()
{
    for (auto it = Component.begin(); it != Component.end(); )
    {
        if (*it != nullptr) {
            (*it)->Update();
            ++it;
        }
        else {
            it = Component.erase(it);  // Remove null components
        }
    }

    // Move pending components to the active list
    for (auto it = PendingComp.begin(); it != PendingComp.end(); ++it)
    {
        Component.push_back(*it);  // Move pending component to active list
    }
    PendingComp.clear();
}