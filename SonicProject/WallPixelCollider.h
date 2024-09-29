#pragma once
#include "PixelCollider.h"
class Actor; 
class WallPixelCollider : public PixelCollider
{
	using Super = PixelCollider;

public:
	WallPixelCollider(Actor* owner, ePixelDirection _dir);
	~WallPixelCollider();

	void BeginPlay() override;
	void TickComponent() override;
	void Render(HDC hdc) override;
	bool CheckCollision(Collider* other) override;

	void SetOriginPixels();
	void AdjustPixels();

	Vector& GetPixel() { return _pixel; }

	void			SetPixelDirection(ePixelDirection direction) { _ePixeldirection = direction; }
	ePixelDirection GetPixelDirection() { return _ePixeldirection; }

private:
	ePixelDirection _ePixeldirection = ePixelDirection::P_LEFT;
	Vector _oppPixel;
	Vector _pixel = { 0,0 };
};

