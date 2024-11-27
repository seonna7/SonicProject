#include "pch.h"
#include "RigidBody.h"
#include "Actor.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Collider.h"
#include "Player.h"
RigidBody::RigidBody(Actor* owner, Physic* py) : _physic(py)
{
	this->_componentType = eComponentType::RIGIDBODY;
	this->SetOwner(owner);
	owner->AddComponent(this);
}
RigidBody::~RigidBody()
{
}
void RigidBody::BeginPlay()
{
}

void RigidBody::TickComponent()
{

}

void RigidBody::Render(HDC hdc)
{
}

void RigidBody::LimitMaxSpeed()
{

}

void RigidBody::MoveLeft()
{
	float deltaTime = GET_SINGLE(TimeManager)->Get_deltaTime();
	Player* player = static_cast<Player*>(GetOwner());

	if (_physic->_groundSpeed > -_physic->_maxSpeedX * deltaTime)
		_physic->_groundSpeed -= _physic->_accelerationSpeed * deltaTime;

}

void RigidBody::MoveRight()
{
	float deltaTime = GET_SINGLE(TimeManager)->Get_deltaTime();
	Player* player = static_cast<Player*>(GetOwner());

	if(_physic->_groundSpeed < _physic->_maxSpeedX * deltaTime)
		_physic->_groundSpeed += _physic->_accelerationSpeed * deltaTime;
}

void RigidBody::Jump()
{
	float deltaTime = GET_SINGLE(TimeManager)->Get_deltaTime();

	Player* player = static_cast<Player*>(GetOwner());
	float angle = player->GetAngle();
	_physic->_groundSpeed -= _physic->_jumpForce * deltaTime * sin(angle);
	
	_physic->Speed.y -= _physic->_jumpForce * deltaTime * cos(angle);

	_physic->Speed.x = _physic->_groundSpeed;
}

void RigidBody::MoveTop()
{
	float deltaTime = GET_SINGLE(TimeManager)->Get_deltaTime();
	Player* player = static_cast<Player*>(GetOwner());
	float angle = player->GetAngle();

	_physic->Speed.y -= _physic->_accelerationSpeed * 3 * deltaTime;
	if (_physic->Speed.y < -_physic->_maxSpeedX * 3 * deltaTime)
	{
		_physic->Speed.y = -_physic->_maxSpeedX * 3 * deltaTime;
	}
#if 0
	{
		_physic->Speed.x += 1 / sqrt(1 + angle * angle);
		_physic->Speed.y += -angle / sqrt(1 + angle * angle);
	}
#endif

}
void RigidBody::MoveBottom()
{
	float deltaTime = GET_SINGLE(TimeManager)->Get_deltaTime();
	Player* player = static_cast<Player*>(GetOwner());
	float angle = player->GetAngle();


	_physic->Speed.y += _physic->_accelerationSpeed * 3 * deltaTime;
	if (_physic->Speed.y > _physic->_maxSpeedX * 3 * deltaTime)
	{
		_physic->Speed.y = _physic->_maxSpeedX * 3 * deltaTime;
	}
#if 1
	{
		_physic->Speed.x += 1 / sqrt(1 + angle * angle);
		_physic->Speed.y += -angle / sqrt(1 + angle * angle);
	}
#endif
}
void RigidBody::SetGravityVector(float radian)
{
	float deltaTime = GET_SINGLE(TimeManager)->Get_deltaTime();
	float angle = radian * 180 / M_PI;
	
	if (angle == 270)
	{
		if (_physic->Speed.y < 200 * deltaTime)
		{
			_physic->Speed.y += 40 * deltaTime;
			return;
		}
	}
	if (angle < 90&& angle >= 0)
	{
		if(_physic->Speed.x < 700 * cos(radian))
		{
			_physic->Speed.x += 40 * deltaTime;
		}
		if (_physic->Speed.y > 700 * -sin(radian))
		{
			_physic->Speed.y -= 40 * deltaTime;
		}
	}
	else if (angle >= 90 && angle < 180)
	{
		if (_physic->Speed.x > 700 * cos(radian))
		{
			_physic->Speed.x -= 40 * deltaTime;
		}
		if (_physic->Speed.y > 700 * -sin(radian))
		{
			_physic->Speed.y -= 40 * deltaTime;
		}
	}
	else if (angle >= 180 && angle < 270)
	{
		if (_physic->Speed.x > 700 * cos(radian))
		{
			_physic->Speed.x -= 40 * deltaTime;
		}
		if (_physic->Speed.y < 700 * -sin(radian))
		{
			_physic->Speed.y += 40 * deltaTime;
		}
	}
	else if (angle > 270 && angle < 360)
	{
		if (_physic->Speed.x < 700 * cos(radian))
		{
			_physic->Speed.x += 40 * deltaTime;
		}
		if (_physic->Speed.y < 700 * -sin(radian))
		{
			_physic->Speed.y += 40 * deltaTime;
		}
	}

}

void RigidBody::LowerGroundSpeed()
{
	float deltaTime = GET_SINGLE(TimeManager)->Get_deltaTime();
	
	if (_physic->_groundSpeed > 0)
	{
		_physic->_groundSpeed -= _physic->_frictionSpeed * deltaTime;
		if (_physic->_groundSpeed < 0)
			_physic->_groundSpeed = 0;
	}
	else if (_physic->_groundSpeed < 0)
	{
		_physic->_groundSpeed += _physic->_frictionSpeed * deltaTime;
		if (_physic->_groundSpeed > 0)
			_physic->_groundSpeed = 0;
	}

}