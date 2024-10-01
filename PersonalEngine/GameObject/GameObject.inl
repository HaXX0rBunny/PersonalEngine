

#include <iostream>
template < typename T>
inline void GameObject::AddComponent(T* component)
{
	Component[component->GetType()] = component;
	component->own = this;

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
	T temp;
	auto it = Component.find(temp.GetType());
	return it != Component.end();
}
template <typename T>
inline void GameObject::RemoveComponent()
{
	T temp;
	auto it = Component.find(temp.GetType());
	if (it != Component.end()) {
		delete it->second;
		Component.erase(it);
	}
}
