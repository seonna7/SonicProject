#include "pch.h"
#include "CameraComponent.h"
#include "Actor.h"
#include "SceneManager.h"
CameraComponent::CameraComponent(Actor* owner)
{
	this->_componentType = eComponentType::CAMERA;
	owner->AddComponent(this);
}
CameraComponent::~CameraComponent()
{
}

void CameraComponent::BeginPlay()
{
}

void CameraComponent::TickComponent()
{
	if (_owner == nullptr)
		return;
	Vector pos = _owner->GetPos();
	pos.x = ::clamp(pos.x, 640.f, 5000.f - 640.f);
	pos.y = ::clamp(pos.y, 360.f, 4000.f - 360.f);
	GET_SINGLE(SceneManager)->SetCameraPos(pos);

}

void CameraComponent::Render(HDC hdc)
{
}
