#pragma once
#include "Collider.h"
class SphereCollider : public Collider
{
	using Super = Collider;
public : 
	SphereCollider();
	virtual ~SphereCollider();
	// Component을(를) 통해 상속됨
	void BeginPlay() override;
	void TickComponent() override;
	void Render(HDC hdc) override;

	bool CheckCollision(Collider* other) override;

	float GetRadius() { return _radius; }
	void SetRadius(float radius) { _radius = radius; }

private : 
	float _radius = 0.f;
};

