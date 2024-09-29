#pragma once
#include "Collider.h"
class PixelCollider : public Collider
{
	using Super = Collider;
public : 
	PixelCollider();
	PixelCollider(ePixelColliderType _type);
	virtual ~PixelCollider();
	// Component을(를) 통해 상속됨
	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

	virtual bool CheckCollision(Collider* other) abstract;

public  :
	ePixelColliderType	GetPixelColliderType() { return _ePixelColliderType; }
	void				SetPixelColliderType(ePixelColliderType _type) { _ePixelColliderType = _type; }

protected  :
	ePixelColliderType _ePixelColliderType;
};

