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
	float angle = player->GetAngle();

	_physic->_groundSpeed -= _physic->_accelerationSpeed * deltaTime;
	
	if (_physic->_groundSpeed < -_physic->_maxSpeedX * deltaTime)
	{
		_physic->_groundSpeed = -_physic->_maxSpeedX * deltaTime;
	}
	if (player->GetIsOnGround() == true)
	{
		_physic->Speed.x = _physic->_groundSpeed * cos(angle);
		_physic->Speed.y = _physic->_groundSpeed * -sin(angle);
	}
	else
	{
		_physic->Speed.x = _physic->_groundSpeed;
	}
}

void RigidBody::MoveRight()
{
	float deltaTime = GET_SINGLE(TimeManager)->Get_deltaTime();
	Player* player = static_cast<Player*>(GetOwner());
	float angle = player->GetAngle();


	_physic->_groundSpeed += _physic->_accelerationSpeed * deltaTime;
	if (_physic->_groundSpeed > _physic->_maxSpeedX * deltaTime)
	{
		_physic->_groundSpeed = _physic->_maxSpeedX * deltaTime;
	}

	if (player->GetIsOnGround() == true)
	{
		_physic->Speed.x = _physic->_groundSpeed * cos(angle);
		_physic->Speed.y = _physic->_groundSpeed * -sin(angle);
	}
	else
	{
		_physic->Speed.x = _physic->_groundSpeed;
	}
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
void RigidBody::GravitationOnGround()
{
	float deltaTime = GET_SINGLE(TimeManager)->Get_deltaTime();
	if (_physic->Speed.y > 200 * deltaTime)
	{
		_physic->Speed.y = 200 * deltaTime;
		return;
	}
	if (_physic->_gravity == true)
	{
		_physic->Speed.y += 40 * deltaTime;
	}
}

void RigidBody::GravitationOnLeftWall()
{
	float deltaTime = GET_SINGLE(TimeManager)->Get_deltaTime();
	if (_physic->Speed.x > 700 * deltaTime)
	{
		_physic->Speed.x = 700 * deltaTime;
		return;
	}
	if (_physic->_gravity == true)
	{
		_physic->Speed.x += 40 * deltaTime;
	}
}

void RigidBody::GravitationOnRightWall()
{
	float deltaTime = GET_SINGLE(TimeManager)->Get_deltaTime();
	if (_physic->Speed.x > 700 * deltaTime)
	{
		_physic->Speed.x = 700 * deltaTime;
		return;
	}
	if (_physic->_gravity == true)
	{
		_physic->Speed.x += 40 * deltaTime;
	}
}

void RigidBody::GravitationOnCeiling()
{
	float deltaTime = GET_SINGLE(TimeManager)->Get_deltaTime();
	if (_physic->Speed.y < -700 * deltaTime)
	{
		_physic->Speed.y = -700 * deltaTime;
		return;
	}
	if (_physic->_gravity == true)
	{
		_physic->Speed.y -= 10 * deltaTime;
	}
}

void RigidBody::SetFriction()
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
	_physic->Speed.x = _physic->_groundSpeed;
}