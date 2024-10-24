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
	void RemoveComponent(T* component);
	void RemoveComponent(const std::string& id);
	bool HasComponent(const std::string&) const;
	bool IsPicking()const;
	void SetPicking(const bool& b_pickin);
	std::map<std::string, BaseComponent*> AllComponent();
	BaseComponent* LoadComponent(const std::string& type);
	void Renamed(const std::string&);
	void Clear();
	std::string GetName();
	enum Tag {
		Default,
		Player,
		Enemy,
		Tile,
		Wall,
		Bomb,
		None
	};
	Tag ObjectTag;
private:
	std::map<std::string, BaseComponent*> Component;
	std::string name;
	bool isPicking;
};

#include "GameObject.inl"