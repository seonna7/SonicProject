#include "pch.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "SceneManager.h"
#include "Actor.h"
#include "Utils.h"

SphereCollider::SphereCollider() : Collider(eColliderType::SPHERE)
{
	this->_componentType = eComponentType::SPHERE_COLLIDER;
} 

SphereCollider::~SphereCollider()
{
}

void SphereCollider::BeginPlay()
{
	Super::BeginPlay();
}

void SphereCollider::TickComponent()
{
	Super::TickComponent();
}

void SphereCollider::Render(HDC hdc)
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
	Utils::DrawCircle(hdc, pos, _radius);
	
	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);
}

bool SphereCollider::CheckCollision(Collider* other)
{
	switch (other->GetColliderType())
	{
	case eColliderType::BOX :
		return CheckCollisionSphereToBox(this, static_cast<BoxCollider*>(other));
		
	case eColliderType::SPHERE :
		return CheckCollisionSphereToSphere(this, static_cast<SphereCollider*>(other));
	}

	return false;
}
