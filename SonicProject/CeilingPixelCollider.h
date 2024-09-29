#pragma once
#include "PixelCollider.h"
class Actor;
class CeilingPixelCollider : public PixelCollider
{
	using Super = PixelCollider;

public:
	CeilingPixelCollider(Actor* owner);
	~CeilingPixelCollider();

	void BeginPlay() override;
	void TickComponent() override;
	void Render(HDC hdc) override;
	bool CheckCollision(Collider* other) override;

	void SetOriginPixels();
	void AdjustPixels();

	Vector& GetPixel() { return _pixel; }


private:
	Vector _oppPixel;
	Vector _pixel;
};
