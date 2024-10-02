

#include <iostream>
#include "GameObject.h"
template<typename T>
inline void GameObject::AddComponent()
{
	if (!GetComponent<T>()) 
	{
		T* temp = new T(this);
		Component.insert({ temp->GetType(), temp });
	}
}
template < typename T>
inline void GameObject::AddComponent(BaseComponent* component)
{
	
	if (GetComponent<T>())
	{
		return nullptr;
	}
	component.insert({ component->GetType(), component });
	component->own = this;
}
template<typename T>
inline T* GameObject::GetComponent()
{
	auto it = Component.find(T::GetType());
	if (it != Component.end())
	{
		return dynamic_cast<T*>(it->second);
	}
	return nullptr;
}
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
template <typename T>
inline bool GameObject::HasComponent() const
{
	auto it = Component.find(T::GetType());
	return it != Component.end();
}
template <typename T>
inline void GameObject::RemoveComponent()
{
	auto it = Component.find(T::GetType());
	if (it != Component.end()) {
		delete it->second;
		Component.erase(it);
	}
}

