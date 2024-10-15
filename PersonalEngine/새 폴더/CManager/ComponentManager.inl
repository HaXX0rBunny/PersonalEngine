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
    Clear();
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
    Component.push_back(component);
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
    for (auto& it : Component) {  // Correctly iterate through components
        if (it != nullptr)
        it->Update();  // Ensure 'it' is a valid pointer
    }
    for (auto it = Component.begin(); it != Component.end(); )
    {
        if (*it == nullptr)
        {
            it = Component.erase(it);
        }
        else
        {
            it++;
        }
    }
}