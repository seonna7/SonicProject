#pragma once
#include "BoxCollider.h"
class AccelObj : public BoxCollider
{
public  :
	using Super = BoxCollider;
	AccelObj(Vector dir);
	~AccelObj() {};

	Vector GetDir() { return _dir; }

	void BeginPlay();
	void TickComponent();
	void Render(HDC hdc);

	bool CheckCollision(Collider* other) override;

private : 
	Vector _dir; 
};

