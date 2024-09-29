#include "pch.h"
#include "Component.h"

Component::Component() 
{
}

Component::Component(Actor* owner)
{
	this->SetOwner(owner);
}

Component::Component(eComponentType type) : _componentType(type)
{
}

Component::~Component()
{
}
