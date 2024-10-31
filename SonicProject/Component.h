#pragma once

class Actor;

class Component
{
public:
	Component();
	Component(Actor* owner);
	Component(eComponentType type);
	~Component();

	virtual void BeginPlay()					abstract;
	virtual void TickComponent()				abstract;
	virtual void Render(HDC hdc)				abstract;


public : 
	void SetOwner(Actor* owner) { _owner = owner; }
	Actor* GetOwner() { return _owner; }

	eComponentType GetComponentType() { return _componentType; }
	void SetComponentType(eComponentType type) { _componentType = type; }
protected : 
	Actor* _owner;
	eComponentType _componentType = eComponentType::NONE;
};