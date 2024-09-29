#pragma once
#include "PixelCollider.h"

class Actor;
class PushPixelCollider : public PixelCollider
{
	using Super = PixelCollider;
public:
	PushPixelCollider(Actor* owner);
	~PushPixelCollider();

	void BeginPlay() override;
	void TickComponent() override;
	void Render(HDC hdc) override;

	
	
	bool CheckCollision(Collider* other) override;

	void SetPixels();
	void AdjustPixels();

	Vector& GetLeftVec() { return _leftPos; }
	Vector& GetRightVec() { return _rightPos; }

private:
	Vector _left = { 0,0 };
	Vector _right = { 0,0 };

	Vector _leftPos = { 0,0 };
	Vector _rightPos = { 0,0 };
};

