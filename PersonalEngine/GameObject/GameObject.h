#pragma once
#include <iostream>
#include <map>

class BaseComponent;

class GameObject {
public:
	GameObject();
	GameObject(BaseComponent* component);
	GameObject(const GameObject& other);
	GameObject& operator=(const GameObject& other);
	~GameObject();
	std::map<std::string, BaseComponent*>& AllComp();
	template <typename T>
	void AddComponent(T* component);
	template <typename T>
	T* GetComponent() const;
	template <typename T>
	bool HasComponent() const;
	template <typename T>
	void RemoveComponent();

	void Clear();
private:
	std::map<std::string, BaseComponent*> Component;
	void CopyComponents(const GameObject& other);

};

#include "GameObject.inl"