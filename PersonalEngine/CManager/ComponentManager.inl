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
    // 즉시 Component 벡터에서 제거
    auto it = std::find(Component.begin(), Component.end(), component);
    if (it != Component.end()) {
        Component.erase(it);
    }

}


template<typename T>
inline void ComponentManager<T>::Update()
{
    // Pending 추가만 처리
    for (auto comp : PendingComp) {
        Component.push_back(comp);
    }
    PendingComp.clear();


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


}