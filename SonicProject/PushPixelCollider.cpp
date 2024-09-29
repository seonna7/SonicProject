#include "pch.h"
#include "PushPixelCollider.h"
#include "Collider.h"
#include "Actor.h"
#include "Component.h"
#include "BoxCollider.h"
#include "CameraComponent.h"
#include "SceneManager.h"
#include "Utils.h"
#include "CollisionManager.h"

PushPixelCollider::PushPixelCollider(Actor* owner) 
	: PixelCollider(ePixelColliderType::PUSH)
{
	this->SetOwner(owner);
	owner->AddComponent(this);
	GET_SINGLE(CollisionManager)->AddCollider(this);
}

PushPixelCollider::~PushPixelCollider()
{
}

void PushPixelCollider::BeginPlay()
{
	Super::BeginPlay();

	SetPixels();
}

void PushPixelCollider::TickComponent()
{
	Super::TickComponent();

	AdjustPixels();
}

void PushPixelCollider::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_showDebug == false)
		return;

	Vector cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
	
	Vector leftPos = _leftPos;
	Vector rightPos = _rightPos;

	leftPos.x -= (cameraPos.x - GWinSizeX / 2);
	leftPos.y -= (cameraPos.y - GWinSizeY / 2);

	rightPos.x -= (cameraPos.x - GWinSizeX / 2);
	rightPos.y -= (cameraPos.y - GWinSizeY / 2);

	Utils::DrawCircle(hdc, leftPos, 3);
	Utils::DrawCircle(hdc, rightPos, 3);

}

bool PushPixelCollider::CheckCollision(Collider* other)
{
	return false;
}

void PushPixelCollider::SetPixels()
{
	if (_owner == nullptr)
		return;

	BoxCollider* boxCollider = static_cast<BoxCollider*>(_owner->FindComponent(eComponentType::BOX_COLLIDER));
	if (boxCollider == nullptr)
		return;

	_left = Vector(boxCollider->GetRect().left, _owner->GetPos().y);
	_right = Vector(boxCollider->GetRect().right, _owner->GetPos().y);

}

void PushPixelCollider::AdjustPixels()
{
	if (_owner == nullptr)
		return;

	_leftPos = _owner->GetPos() + _left;
	_rightPos = _owner->GetPos() + _right;
}
