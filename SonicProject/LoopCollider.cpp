#include "pch.h"
#include "LoopCollider.h"
#include "Player.h"
#include "TimeManager.h"
#include "GroundPixelCollider.h"
#include "WallPixelCollider.h"
#include "CeilingPixelCollider.h"
#include "PixelCollider.h"

LoopCollider::LoopCollider(Vector pos)
	: Collider(eColliderType::LOOP)
{
	this->_componentType = eComponentType::LOOP;
	_pos = pos;
}

LoopCollider::~LoopCollider()
{

}

void LoopCollider::BeginPlay()
{

}

void LoopCollider::TickComponent()
{
	
}

void LoopCollider::Render(HDC hdc)
{

}

bool LoopCollider::CheckCollision(Collider* other)
{
	PixelCollider* pixelcollider = dynamic_cast<PixelCollider*>(other);
	if (pixelcollider == nullptr)
		return false;
	
	ePixelColliderType _pixelColliderType = pixelcollider->GetPixelColliderType();
	if (_pixelColliderType != ePixelColliderType::GROUND)
		return false;

	Vector pos = other->GetOwner()->GetPos();
	switch (_dir)
	{
	case ePixelDirection::P_RIGHT : 
		return CollisionDetect_RightLoopcourse(pos);
	case ePixelDirection::P_LEFT : 
		return CollisionDetect_LeftLoopCourse(pos);
	}
}


bool LoopCollider::CollisionDetect_RightLoopcourse(Vector ownerPos)
{
	bool xLeft		= ownerPos.x >= _pos.x;
	bool xRight		= ownerPos.x <= _pos.x + _size.x / 2;
	//y 값에 owner 길이도 넣어줘야할듯
	bool yTop		= ownerPos.y >= _pos.y - _size.y / 2;
	bool yBottom	= ownerPos.y <= _pos.y + _size.y / 2;

	return xLeft && xRight && yTop && yBottom;
}

bool LoopCollider::CollisionDetect_LeftLoopCourse(Vector ownerPos)
{
	bool xLeft		= ownerPos.x <= _pos.x;
	bool xRight		= ownerPos.x >= _pos.x - _size.x / 2;
	bool yTop		= ownerPos.y >= _pos.y - _size.y / 2;
	bool yBottom	= ownerPos.y <= _pos.y + _size.y / 2;

	return xLeft && xRight && yTop && yBottom;
}

