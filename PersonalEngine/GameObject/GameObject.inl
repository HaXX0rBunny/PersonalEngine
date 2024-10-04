// AddComponent without parameters - Adds new component of type T to the GameObject
template<typename T>
inline void GameObject::AddComponent()
{
    if (!GetComponent<T>())
    {
        T* temp = new T(this);  // T must be a derived class of BaseComponent
        Component.insert({ temp->GetType(), temp });
    }
}

// AddComponent with BaseComponent pointer - Adds an existing component
template <typename T>
inline void GameObject::AddComponent(BaseComponent* component)
{
    if (GetComponent<T>())
    {
        return;  // Prevent adding duplicate components
    }
    Component.insert({ component->GetType(), component });
    component->own = this;  // Ensure that the component knows its owner
}

// Get a component of type T
template<typename T>
inline T* GameObject::GetComponent()
{
    auto it = Component.find(T::GetType());
    if (it != Component.end())
    {
        return static_cast<T*>(it->second);
    }
    return nullptr;
}

// Get a component of type T (const version)
template<typename T>
inline T* GameObject::GetComponent() const
{
    auto it = Component.find(T::GetType());
    if (it != Component.end())
    {
        return dynamic_cast<T*>(it->second);
    }
    return nullptr;
}

// Check if a component of type T exists
template <typename T>
inline bool GameObject::HasComponent() const
{
    auto it = Component.find(T::GetType());
    return it != Component.end();
}

// Remove a component of type T
template<typename T>
inline void GameObject::RemoveComponent(T* component)
{
    auto it = std::find_if(Component.begin(), Component.end(),
        [component](const auto& pair) { return pair.second == component; });
    if (it != Component.end()) {
        delete it->second;  // Free the memory
        Component.erase(it);
    }
}
