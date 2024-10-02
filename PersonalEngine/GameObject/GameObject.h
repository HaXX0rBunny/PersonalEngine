#pragma once
#include "../Component/BaseComponent.h"
#include <iostream>
#include <map>

class BaseComponent;

class GameObject {
public:
	GameObject();
	GameObject(std::string id);
	GameObject(const GameObject& other)=delete;
	GameObject& operator=(const GameObject& other) = delete;
	~GameObject();
	std::map<std::string, BaseComponent*>& AllComp();
	template <typename T>
	void AddComponent();
	template <typename T>
	void AddComponent(BaseComponent* component);
	template <typename T>
	T* GetComponent();
	template <typename T>
	T* GetComponent() const;
	template <typename T>
	bool HasComponent() const;
	template <typename T>
	void RemoveComponent();

	void Clear();
private:
	std::map<std::string, BaseComponent*> Component;


};

#include "GameObject.inl"