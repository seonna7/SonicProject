#include "pch.h"
#include "CeilingPixelCollider.h"
#include "Collider.h"
#include "Actor.h"
#include "Component.h"
#include "BoxCollider.h"
#include "CameraComponent.h"
#include "SceneManager.h"
#include "Utils.h"
#include "CollisionManager.h"
CeilingPixelCollider::CeilingPixelCollider(Actor* owner)
	: PixelCollider(ePixelColliderType::CEILING)
{
	this->SetOwner(owner);
	owner->AddComponent(this);
	GET_SINGLE(CollisionManager)->AddCollider(this);
}

CeilingPixelCollider::~CeilingPixelCollider()
{
}

void CeilingPixelCollider::BeginPlay()
{
	Super::BeginPlay();

	SetOriginPixels();
}

void CeilingPixelCollider::TickComponent()
{
	Super::TickComponent();

	this->AdjustPixels();
}

void CeilingPixelCollider::Render(HDC hdc)
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

bool CeilingPixelCollider::CheckCollision(Collider* other)
{
	return false;
}

void CeilingPixelCollider::SetOriginPixels()
{
	if (_owner == nullptr)
		return;

	BoxCollider* boxCollider = static_cast<BoxCollider*>(_owner->FindComponent(eComponentType::BOX_COLLIDER));
	if (boxCollider == nullptr)
		return;

	float height = boxCollider->GetSize().y;

	_oppPixel = Vector(0, - height / 2);
}

void CeilingPixelCollider::AdjustPixels()
{
	if (_owner == nullptr)
		return;

	_pixel = _owner->GetPos() + _oppPixel;

}
