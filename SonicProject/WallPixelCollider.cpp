#include "pch.h"
#include "WallPixelCollider.h"
#include "PixelCollider.h"
#include "Actor.h"
#include "Component.h"
#include "BoxCollider.h"
#include "CameraComponent.h"
#include "SceneManager.h"
#include "Utils.h"
#include "CollisionManager.h"

WallPixelCollider::WallPixelCollider(Actor* owner, ePixelDirection _dir) 
	: PixelCollider(ePixelColliderType::WALL)
{
	this->SetPixelDirection(_dir);
	this->SetOwner(owner);
	GET_SINGLE(CollisionManager)->AddCollider(this);
	owner->AddComponent(this);
}

WallPixelCollider::~WallPixelCollider()
{
}

void WallPixelCollider::BeginPlay()
{
    Super::BeginPlay();
    SetOriginPixels();
}

void WallPixelCollider::TickComponent()
{
    Super::TickComponent();
}

void WallPixelCollider::Render(HDC hdc)
{
    Super::Render(hdc);
	if (_showDebug == false)
		return;

	Vector cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	Vector pixel = _pixel;

	{
		pixel.x -= (cameraPos.x - GWinSizeX / 2);
		pixel.y -= (cameraPos.y - GWinSizeY / 2);
		Utils::DrawCircle(hdc, pixel, PixelSize);
	}
}

bool WallPixelCollider::CheckCollision(Collider* other)
{
    return false;
}

void WallPixelCollider::SetOriginPixels()
{
	if (_owner == nullptr)
		return;

	BoxCollider* boxCollider = static_cast<BoxCollider*>(_owner->FindComponent(eComponentType::BOX_COLLIDER));
	if (boxCollider == nullptr)
		return;

	float width = boxCollider->GetSize().x;
	float height = boxCollider->GetSize().y;
	if(_ePixeldirection==ePixelDirection::P_LEFT)
		_oppPixel  = Vector(-width / 2, height/2);
	else if (_ePixeldirection == ePixelDirection::P_RIGHT)
	_oppPixel = Vector( width / 2, height / 2);
}

void WallPixelCollider::AdjustPixels()
{
	if (_owner == nullptr)
		return;
	_pixel = _owner->GetPos() + _oppPixel;
}
