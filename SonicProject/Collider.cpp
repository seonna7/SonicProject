#include "pch.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "Actor.h"
Collider::Collider(eColliderType type)
: _colliderType(type)
{
	
}

Collider::~Collider()
{
}

void Collider::BeginPlay()
{

}

void Collider::TickComponent()
{
}

void Collider::Render(HDC hdc)
{
}

bool Collider::CheckCollision(Collider* other)
{

	uint32 layer = other->GetCollisonLayerType();

	if (_collisionFlag & (1 << layer))
		return true; 
	return false;
}

bool Collider::CheckCollisionBoxToBox(BoxCollider* b1, BoxCollider* b2)
{
	RECT r1 = b1->GetRect();
	RECT r2 = b2->GetRect();


	RECT intersect = {};
	return ::IntersectRect(&intersect, &r1, &r2);
}

bool Collider::CheckCollisionSphereToSphere(SphereCollider* s1, SphereCollider* s2)
{
	Vector pos1 = s1->GetOwner()->GetPos();
	float d1 = s1->GetRadius();
	
	Vector pos2 = s2->GetOwner()->GetPos();
	float d2 = s2->GetRadius();

	Vector _dir = pos2 - pos1;

	float dist = _dir.Length();

	return dist<=d1 + d2;
}

bool Collider::CheckCollisionSphereToBox(SphereCollider* s1, BoxCollider* b1)
{
	return false;
}

void Collider::AddCollisionFlagLayer(COLLISION_LAYER_TYPE layer)
{
	_collisionFlag |= (1 << layer);
}

void Collider::RemoveCollisionFlagLayer(COLLISION_LAYER_TYPE layer)
{
	_collisionFlag &= ~(1<<layer);
}
