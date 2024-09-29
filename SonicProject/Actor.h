#pragma once

class Sprite;
class Component;
class Collider;

class Actor
{
public  :
	Actor();
	virtual ~Actor();

	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

	void SetPos(Pos pos)		{ _pos = pos; }
	Vector GetPos()				{ return _pos; }

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);
	Component* FindComponent(eComponentType type);

	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

protected : 
	std::vector<Component*> _components;
	Vector _pos{ 0,0 };
};

