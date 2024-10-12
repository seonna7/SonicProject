#pragma once
#include "Component.h"
#include "InputManager.h"
class Actor;
class Texture;

// ���ӵ�, �ӵ�, 

// �����͸� physic�� ���� �����س��� �����͸� ���� ���� ����ϰ� �ӻ��ϰ�
struct Physic
{
	Physic() {};
	Vector Speed = { 0,0 };
	float _accelerationSpeed = 5.0f;
	float _frictionSpeed = 3.0f;
	float _maxSpeedX = 250;
	float _jumpForce = 600;

	float _groundSpeed = 0.f;

	void RemoveSpeedX(){ Speed.x = 0; }
	void RemoveSpeedY() { Speed.y = 0; }
	bool _gravity = false;

	void SetGravity(bool gravity) { _gravity = gravity; }
};


class RigidBody : public Component
{
public :
	RigidBody(Actor* owner, Physic* py);

	virtual ~RigidBody();

	void BeginPlay() override;
	void TickComponent() override;
	void Render(HDC hdc) override;

	void SetPhysic(Physic* ph) { _physic = ph; }
	Physic* GetPhysic() { return _physic; }

	void LimitMaxSpeed();

public  :
	void MoveLeft();
	void MoveRight();
	void MoveTop();
	void MoveBottom();

	void Jump();

	void GravitationOnGround();
	void GravitationOnLeftWall();
	void GravitationOnRightWall();
	void GravitationOnCeiling();

	void SetFriction();
private :
	Physic* _physic;
};