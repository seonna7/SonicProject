#pragma once
#include "Collider.h"

class Actor;

class PixelCollider : public Collider
{
	using Super = Collider;
public:
	PixelCollider(Actor* owner, ePixelColliderType _type, uint8 dir,Vector dist);
	
	~PixelCollider();

	// Component을(를) 통해 상속됨
	void BeginPlay() override;
	void TickComponent() override;
	void Render(HDC hdc) override;

	void SetDirVector(uint8 dir);

	virtual bool CheckCollision(Collider* other);

	void SetPixelPos();
	
	void SetPos(Vector pos) { _pos = pos; }
	Vector &GetPos() { return _pos; }

	uint8 GetDir() { return _dir; }
public:
	ePixelColliderType	GetPixelColliderType() { return _ePixelColliderType; }
	void				SetPixelColliderType(ePixelColliderType _type) { _ePixelColliderType = _type; }

	void SetIsCollided(bool isCollided) { _isCollided = isCollided; }
	bool GetIsCollided() { return _isCollided; }

private : 
	bool _isCollided = false;
protected:
	ePixelColliderType	_ePixelColliderType;

	uint8				_dir = 0;
	Vector				_dist = { 0,0 };
	Vector				_dirVector = { 0,0 };
	Vector				_pos = { 0,0 };
};