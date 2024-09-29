#include "pch.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "Actor.h"

void CollisionManager::Init()
{
}

void CollisionManager::Update()
{
	vector<Collider*>& colliders = _colliders;

	for (int32 i = 0; i < colliders.size(); i++)
	{
		for (int32 j = i + 1; j < colliders.size(); j++)
		{
			Collider* src = colliders[i];
			Collider* dst = colliders[j];
			
			if (Is_Src_Dst_SameOwner(src, dst))
				continue;

			if (src->CheckCollision(dst)==true)
			{
				//
				if (src->GetCollisionMap().contains(dst) == false)
				{
					src->GetCollisionMap().insert(dst);
					dst->GetCollisionMap().insert(src);
				}
				src->GetOwner()->OnComponentBeginOverlap(src, dst);
				dst->GetOwner()->OnComponentBeginOverlap(dst, src);
			}
			else if (src->CheckCollision(dst)==false)
				if (src->GetCollisionMap().contains(dst) == true)
				{
					src->GetOwner()->OnComponentEndOverlap(src, dst);
					dst->GetOwner()->OnComponentEndOverlap(dst, src);

					src->GetCollisionMap().erase(dst);
					dst->GetCollisionMap().erase(src);

				}
		}
	}
}

void CollisionManager::AddCollider(Collider* collider)
{
	_colliders.push_back(collider);
}

void CollisionManager::RemoveCollider(Collider* collider)
{
	auto it =std::remove(_colliders.begin(), _colliders.end(), collider);
	_colliders.erase(it);
}

bool CollisionManager::Is_Src_Dst_SameOwner(Collider* c1, Collider* c2)
{
	return c1->GetOwner() == c2->GetOwner();
}
