#include "pch.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "SceneManager.h"
#include "Actor.h"
#include "Utils.h"

BoxCollider::BoxCollider() : Collider(eColliderType::BOX)
{
	this->SetComponentType(eComponentType::BOX_COLLIDER);
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::BeginPlay()
{
	Super::BeginPlay();
}

void BoxCollider::TickComponent()
{
	Super::TickComponent();
}

void BoxCollider::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_showDebug == false)
		return;

	Vector cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
	Vector pos = GetOwner()->GetPos();

	pos.x -= (cameraPos.x - GWinSizeX / 2);
	pos.y -= (cameraPos.y - GWinSizeY / 2);

	HBRUSH myBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, myBrush);
	Utils::DrawRect(hdc, pos, _size.x,_size.y);

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);
}

bool BoxCollider::CheckCollision(Collider* other)
{
	if (Super::CheckCollision(other) == false)
		return false;

	switch (other->GetColliderType())
	{
	case eColliderType::SPHERE:
		return CheckCollisionSphereToBox(static_cast<SphereCollider*>(other), this);

	case eColliderType::BOX:
		return CheckCollisionBoxToBox(this, static_cast<BoxCollider*>(other));
	}
	return false;
}

RECT BoxCollider::GetRect()
{
	Vector pos = GetOwner()->GetPos();
	
	Vector size = GetSize();

	RECT rect =
	{
		(int32)(pos.x - size.x / 2),
		(int32)(pos.y - size.y / 2),
		(int32)(pos.x + size.x / 2),
		(int32)(pos.y + size.y / 2)
	};
	return rect;
}