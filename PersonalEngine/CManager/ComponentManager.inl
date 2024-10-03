#include "ComponentManager.h"
template<typename T>
ComponentManager<T>* ComponentManager<T>::Instance_ = nullptr;

template<typename T>
inline ComponentManager<T>::~ComponentManager()
{
    Clear();
}
template<typename T>
inline void ComponentManager<T>::Clear()
{
    // Clear all components and delete them
    for (auto& comp : Component) {  // Correct usage without 'this'
        delete comp;  // Ensure 'comp' is a pointer
    }
    Component.clear();
}

template<typename T>
inline void ComponentManager<T>::DestroyInstance()
{
    if (Instance_) {
        Instance_->Clear();  // First clear the components
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
        delete* it;  // Ensure '*it' is a pointer
        Component.erase(it);
    }
}


template<typename T>
inline void ComponentManager<T>::Update()
{
    for (auto& it : Component) {  // Correctly iterate through components
        it->Update();  // Ensure 'it' is a valid pointer
    }
}