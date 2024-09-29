#pragma once
#include "Collider.h"
class SpriteActor;
class BackGroundCollider : public Collider
{
public : 

	BackGroundCollider();
	virtual ~BackGroundCollider();
	// Component을(를) 통해 상속됨
	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

	virtual bool CheckCollision(Collider* other) override;
};

