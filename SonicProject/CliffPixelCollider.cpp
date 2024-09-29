#include "pch.h"
#include "CliffPixelCollider.h"
#include "Collider.h"
#include "Actor.h"
#include "Component.h"
#include "BoxCollider.h"
#include "CameraComponent.h"
#include "SceneManager.h"
#include "Utils.h"
#include "CollisionManager.h"

enum
{
	DIST = 35
};
CliffPixelCollider::CliffPixelCollider(Actor* owner) 
	: PixelCollider(ePixelColliderType::CLIFF)
{
	this->SetShowDebug(false);

	owner->AddComponent(this);
	this->SetOwner(owner);
	GET_SINGLE(CollisionManager)->AddCollider(this);
}

CliffPixelCollider::~CliffPixelCollider()
{
}

void CliffPixelCollider::BeginPlay()
{
	Super::BeginPlay();
	CliffPixelCollider::SetPixels();
}

void CliffPixelCollider::TickComponent()
{
	Super::TickComponent();
	this->AdjustPixels();
}

void CliffPixelCollider::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_showDebug == false)
		return;

	Vector cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	Vector leftTop = _setLeftTop;
	Vector rightTop = _setRightTop;

	Vector leftBottom= _setLeftBottom;
	Vector rightBottom= _setRightBottom;

	leftTop.x -= (cameraPos.x - GWinSizeX / 2);
	leftTop.y -= (cameraPos.y - GWinSizeY / 2);
	leftBottom.x -= (cameraPos.x - GWinSizeX / 2);
	leftBottom.y -= (cameraPos.y - GWinSizeY / 2);

	rightTop.x -= (cameraPos.x - GWinSizeX / 2);
	rightTop.y -= (cameraPos.y - GWinSizeY / 2);
	rightBottom.x -= (cameraPos.x - GWinSizeX / 2);
	rightBottom.y -= (cameraPos.y - GWinSizeY / 2);

	Utils::DrawCircle(hdc, leftTop, 3);
	Utils::DrawCircle(hdc, rightTop, 3);
	Utils::DrawCircle(hdc, leftBottom, 3);
	Utils::DrawCircle(hdc, rightBottom, 3);
}

bool CliffPixelCollider::CheckCollision(Collider* other)
{
	return false;
}

void CliffPixelCollider::SetPixels()
{
	if (_owner == nullptr)
		return;

	BoxCollider* boxCollider = static_cast<BoxCollider*>(_owner->FindComponent(eComponentType::BOX_COLLIDER));
	if (boxCollider == nullptr)
		return;

	_originLeftTop = Vector(boxCollider->GetRect().left/3, boxCollider->GetRect().bottom);
	_originRightTop = Vector(boxCollider->GetRect().right/3, boxCollider->GetRect().bottom );
	_originLeftBottom = Vector(boxCollider->GetRect().left/3, boxCollider->GetRect().bottom + DIST);
	_originRightBottom = Vector(boxCollider->GetRect().right/3, boxCollider->GetRect().bottom + DIST);

}

void CliffPixelCollider::AdjustPixels()
{
	if (_owner == nullptr)
		return;

	_setLeftTop = _owner->GetPos() + _originLeftTop;
	_setRightTop = _owner->GetPos() + _originRightTop;
	_setLeftBottom = _owner->GetPos() + _originLeftBottom;
	_setRightBottom = _owner->GetPos() + _originRightBottom;

}
