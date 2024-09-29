#pragma once
#include "Component.h"
#include "InputManager.h"
class Actor;
class Texture;

// °¡¼Óµµ, ¼Óµµ, 

// Èûº¤ÅÍ¸¦ physic¿¡ Á÷Á¢ ±¸ÇöÇØ³õ°í ¸®ÆÑÅÍ¸µ °úÁ¤ ¾øÀÌ ±ò½ÓÇÏ°í ½Ó»ÍÇÏ°Ô
struct Physic
{
	Physic() {};
	Vector Speed = { 0,0 };
	float _accelerationSpeed = 0.46875;
	float _frictionSpeed = 4.6875;
	float _maxSpeedX = 100;
	float _jumpForce = 500;
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