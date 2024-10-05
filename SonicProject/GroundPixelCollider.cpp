#include "pch.h"
#include "GroundPixelCollider.h"
#include "Collider.h"
#include "Actor.h"
#include "Component.h"
#include "BoxCollider.h"
#include "CameraComponent.h"
#include "SceneManager.h"
#include "Utils.h"
#include "Player.h"
#include "CollisionManager.h"
GroundPixelCollider::GroundPixelCollider(Actor* owner) 
	: PixelCollider(ePixelColliderType::GROUND)
{
	this->SetOwner(owner);
	owner->AddComponent(this);
	GET_SINGLE(CollisionManager)->AddCollider(this);
}

GroundPixelCollider::~GroundPixelCollider()
{
}

void GroundPixelCollider::BeginPlay()
{
	Super::BeginPlay();

	SetOriginPixels();
}

void GroundPixelCollider::TickComponent()
{
	Super::TickComponent();

	this->AdjustPixels();
}

void GroundPixelCollider::Render(HDC hdc)
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

bool GroundPixelCollider::CheckCollision(Collider* other)
{
	if (other->GetComponentType() == eComponentType::BACKGROUND_COLLIDER)
	{
		Player* player = dynamic_cast<Player*>(_owner);
		return player->GetIsOnGround();
	}
	return false;
}

void GroundPixelCollider::SetOriginPixels()
{
	if (_owner == nullptr)
		return;
	 
	BoxCollider* boxCollider = static_cast<BoxCollider*>(_owner->FindComponent(eComponentType::BOX_COLLIDER));
	if (boxCollider == nullptr)
		return;
	
	float height = boxCollider->GetSize().y;

	_oppPixel = Vector(0, height / 2  + 3);
}

void GroundPixelCollider::AdjustPixels()
{
	if (_owner == nullptr)
		return;
	
	_pixel = _owner->GetPos() + _oppPixel;
	
}
