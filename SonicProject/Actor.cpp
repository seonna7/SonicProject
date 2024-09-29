#include "pch.h"
#include "Actor.h"
#include "Component.h"
#include "Collider.h"
Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::BeginPlay()
{
	for (Component* component : _components)
	{
		component->BeginPlay();
	}
}

void Actor::Tick()
{
	for (Component* component : _components)
	{
		component->TickComponent();
	}
}

void Actor::Render(HDC hdc)
{
	for (Component* component : _components)
	{
		component->Render(hdc);
	}
}

void Actor::AddComponent(Component* component)
{
	if (component == nullptr)
		return;
	component->SetOwner(this);
	_components.push_back(component);
}

void Actor::RemoveComponent(Component* component)
{
	auto findit = std::find(_components.begin(), _components.end(), component);
	if (findit == _components.end())
		return;
	_components.erase(findit);
}

Component* Actor::FindComponent(eComponentType type)
{
	if (_components.size() == 0)
		return nullptr;
	for (auto& component : _components)
	{
		if (component->GetComponentType() == type)
			return component;
	}
	return nullptr;
}

void Actor::OnComponentBeginOverlap(Collider* collider, Collider* other)
{

}

void Actor::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}
