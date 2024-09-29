#pragma once
#include "Collider.h"
class LoopCollider : public Collider
{
public : 
	LoopCollider(Vector pos);
	virtual ~LoopCollider();
	// Component을(를) 통해 상속됨
	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;
	virtual bool CheckCollision(Collider* other) override;

public : 
	Vector	GetPos() { return _pos; }
	void	SetPos(Vector vec) { _pos = vec; }

	void	SetSize(Vector size) { _size = size; }
	Vector	GetSize() { return _size; }

	bool CollisionDetect_RightLoopcourse(Vector ownerPos);
	bool CollisionDetect_LeftLoopCourse(Vector ownerPos);

	void SetIsLoopCoursePassed(bool passed) { _IsLoopCoursePassed = passed; }
	bool GetIsLoopCoursePassed() { return _IsLoopCoursePassed; }

	void SetDirection(ePixelDirection dir) { _dir = dir; }
	ePixelDirection GetDirection() { return _dir; }

private :

	Vector _pos;

	ePixelDirection _dir = ePixelDirection::P_RIGHT;
	bool _IsLoopCoursePassed = false; 

	Vector _size = { 350,312 };
};

