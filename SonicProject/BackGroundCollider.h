#pragma once
#include "Collider.h"
class SpriteActor;
class BackGroundCollider : public Collider
{
public : 

	BackGroundCollider();
	virtual ~BackGroundCollider();
	// Component��(��) ���� ��ӵ�
	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

	virtual bool CheckCollision(Collider* other) override;
};

