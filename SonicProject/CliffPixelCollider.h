#pragma once
#include "PixelCollider.h"
class Actor;
class CliffPixelCollider : public PixelCollider
{
	using Super = PixelCollider;
public:
	CliffPixelCollider(Actor* owner);
	~CliffPixelCollider();

	void BeginPlay() override;
	void TickComponent() override;
	void Render(HDC hdc) override;

	bool CheckCollision(Collider* other) override;

	void SetPixels();
	void AdjustPixels();

	Vector& GetLeftTop() { return _setLeftTop; }
	Vector& GetLeftBottom() { return _setLeftBottom; }
	Vector& GetRightTop() { return _setRightTop; }
	Vector& GetRightBottom() { return _setRightBottom; }

private:
	Vector _originLeftTop = { 0,0 };
	Vector _originRightTop = { 0,0 };
	Vector _originLeftBottom = { 0,0 };
	Vector _originRightBottom = { 0,0 };

	Vector _setLeftTop = { 0,0 };
	Vector _setRightTop = { 0,0 };
	Vector _setLeftBottom = { 0,0 };
	Vector _setRightBottom = { 0,0 };

};

