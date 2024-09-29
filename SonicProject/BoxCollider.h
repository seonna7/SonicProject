#pragma once
#include "Collider.h"
class BoxCollider : public Collider
{
	using Super = Collider;
public:
	BoxCollider();
	virtual ~BoxCollider();
	// Component��(��) ���� ��ӵ�
	void BeginPlay() override;
	void TickComponent() override;
	void Render(HDC hdc) override;

	bool CheckCollision(Collider* other) override;

	Vector GetSize() { return _size; }
	void SetSize(Vector size) { _size = size; }

	RECT GetRect();

private : 
	Vector _size = {};
};

