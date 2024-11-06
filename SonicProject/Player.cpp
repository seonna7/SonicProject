#include "pch.h"
#include "Player.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "EventManager.h"
#include "SceneManager.h"
#include "Utils.h"
#include "ResourceManager.h"
#include "Flipbook.h"
#include "Component.h"
#include "CameraComponent.h"
#include "BoxCollider.h"
#include "RigidBody.h"
#include "Texture.h"
#include "DevScene.h"
#include "AccelObj.h"

#include "PixelCollider.h"
#include "LoopCollider.h"
#include "CollisionManager.h"


Player::Player()
{
#pragma region FlipBook �������� 
	{
		_flipbook_Pause				= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Standing");

		_flipbookSkiddling_Left		= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Skiddling_Left");
		_flipbookSkiddling_Right	= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Skiddling_Right");

		_flipbook_Rolling			= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Rolling");
		_flipbook_Sitting			= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Sitting");
		
		_flipbook_RunningLeft_0		= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Running_Left_0");
		_flipbook_RunningLeft_45	= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Running_Left_45");
		_flipbook_RunningLeft_90	= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Running_Left_90");
		_flipbook_RunningLeft_135	= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Running_Left_135");
		_flipbook_RunningLeft_180	= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Running_Left_180");
		_flipbook_RunningLeft_225	= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Running_Left_225");
		_flipbook_RunningLeft_270	= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Running_Left_270");
		_flipbook_RunningLeft_315	= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Running_Left_315");

		_flipbook_RunningRight_0	= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Running_Right_0");
		_flipbook_RunningRight_45	= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Running_Right_45");
		_flipbook_RunningRight_90	= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Running_Right_90");
		_flipbook_RunningRight_135	= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Running_Right_135");
		_flipbook_RunningRight_180	= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Running_Right_180");
		_flipbook_RunningRight_225	= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Running_Right_225");
		_flipbook_RunningRight_270	= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Running_Right_270");
		_flipbook_RunningRight_315	= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Running_Right_315");

	}

#pragma region ī�޶� �߰�
	{
		CameraComponent* camera = new CameraComponent(this);
	}

#pragma region rigidBody �߰�
	{
		_rigidBody = new RigidBody(this, new Physic());
		SetRigidBody(_rigidBody);
		_physic = _rigidBody->GetPhysic();
	}

#pragma region pixelCollider �߰� 
	{
		Vector size = Vector(e_Pixel_Len);

		_pixelDist = e_Pixel_Len * 2;

		_Right_Bottom = new PixelCollider(this, ePixelColliderType::WALL, _right | _bottom,size);
		_pixels[_right | _bottom] = _Right_Bottom;

		_Left_Bottom = new PixelCollider(this, ePixelColliderType::WALL, _left | _bottom,size);
		_pixels[_left | _bottom] = _Left_Bottom;

		_Left_Top = new PixelCollider(this, ePixelColliderType::CEILING, _left | _top,size);
		_pixels[_left | _top] = _Left_Top;

		_Right_Top = new PixelCollider(this, ePixelColliderType::CEILING, _right | _top,size);
		_pixels[_right | _top] = _Right_Top;
	}
}

Player::~Player()
{
	{
		_pixels.erase(_right | _top);
		_pixels.erase(_right | _bottom);
		_pixels.erase(_left | _top);
		_pixels.erase(_left | _bottom);
	}
}

void Player::BeginPlay()
{
	SetPos(Vector(300, 300));
	Super::BeginPlay();
	setFlipbook(_flipbook_Pause);
}

void Player::Tick()
{
	Super::Tick();
	float deltaTime = GET_SINGLE(TimeManager)->Get_deltaTime();

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::Q))
	{
		Gravity = !Gravity;
	}

	{

		Player::SetAngle();

		if (_angle >= -M_PI / 4 && _angle < M_PI / 4)
		{
			Player::CheckCollision((uint8)e_SlopeType::GROUND);
		}
		else if (_angle >= M_PI / 4 && _angle < 3 * M_PI / 4)
		{
			Player::CheckCollision((uint8)e_SlopeType::RIGHT_WALL);
		}
		else if (_angle >= 3 * M_PI / 4 || _angle < -3 * M_PI / 4)
		{
			Player::CheckCollision((uint8)e_SlopeType::CEILING);
		}
		else if (_angle > -3 * M_PI / 4 && _angle <=  -M_PI / 4)
		{
			Player::CheckCollision((uint8)e_SlopeType::LEFT_WALL);
		}
	}

	if (Gravity==true)//_IsOnGround == false)
	{
		Player::SetGravitationVec(e_SlopeType::GROUND);
	}

	
	if (true)
	{
		Player::JumpStateUpdate();
	}


	if (_IsOnGround == true && _physic->Speed == Vector{ 0,0 })
	{
		SetSonicState(SonicState::PAUSE);
	}
	
	if (_ctrlLockTimer != 0)
	{
		
	}
	else
	{
		void OnUpPressed();
		void OnLeftPressed();
		void OnRightPressed();
		void OnDownPressed();
	}
	
	if(_IsOnGround==true)
	{
		_physic->Speed.x = _physic->_groundSpeed * cos(_angle);
		_physic->Speed.y = _physic->_groundSpeed * -sin(_angle);
	}

	if (Player::SetMovement() == false)
	{
		return;
	}
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);

	{
		{
			wstring str = std::format(L"Player Position({0}, {1})", _pos.x, _pos.y);
			::TextOut(hdc, 10, 90, str.c_str(), static_cast<int32>(str.size()));
		}
		{
			wstring str = std::format(L"Player Angle({0})", _angle);
			::TextOut(hdc, 10, 110, str.c_str(), static_cast<int32>(str.size()));
		}
		{
			wstring str = std::format(L"Player onGround({0})", _IsOnGround);
			::TextOut(hdc, 10, 130, str.c_str(), static_cast<int32>(str.size()));
		}
		{
			wstring str = std::format(L"Player onLeftWall({0})", _IsOnLWall);
			::TextOut(hdc, 10, 150, str.c_str(), static_cast<int32>(str.size()));
		}
		{
			wstring str = std::format(L"Player onRightWall({0})", _IsOnRWall);
			::TextOut(hdc, 10, 170, str.c_str(), static_cast<int32>(str.size()));
		}
		{
			wstring str = std::format(L"Player onCeiling({0})", _IsOnCeiling);
			::TextOut(hdc, 10, 190, str.c_str(), static_cast<int32>(str.size()));
		}
		{
			wstring str = std::format(L"Speed Vector({0}, {1})", _physic->Speed.x, _physic->Speed.y);
			::TextOut(hdc, 10, 210, str.c_str(), static_cast<int32>(str.size()));
		}
		{
			//wstring str = std::format(L"onLoop({0})", _onLoopCondition);
			//::TextOut(hdc, 10, 230, str.c_str(), static_cast<int32>(str.size()));
		}
		{
			wstring str = std::format(L"Jumped({0})", _IsJumped);
			::TextOut(hdc, 10, 250, str.c_str(), static_cast<int32>(str.size()));
		}
		{
			//wstring str = std::format(L"LoopJumped({0})", _onLoopJumped);
			//::TextOut(hdc, 10, 270, str.c_str(), static_cast<int32>(str.size()));
		}
		{
			wstring str = std::format(L"CtrlLockTimer({0})", _ctrlLockTimer);
			::TextOut(hdc, 10, 290, str.c_str(), static_cast<int32>(str.size()));
		}
	}

#pragma region AnglePixel ��� 
	if(_A_Pixel[0]!=nullptr)
	{
		Vector cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
		Vector Apixel[2];
		Apixel[0] = *_A_Pixel[0];
		Apixel[1] = *_A_Pixel[1];
		for(int i = 0; i<2; i++)
		{
			Apixel[i].x -= (cameraPos.x - (GWinSizeX / 2));
			Apixel[i].y -= (cameraPos.y - (GWinSizeY / 2));
			Utils::DrawCircle(hdc, Apixel[i], PixelSize);
		}
	}

	Player::FinalRender(hdc);
}

void Player::FinalRender(HDC hdc)
{
	RenewPixelLocation();
	Player::FlipbookRender();
}

void Player::FlipbookRender()
{
	switch (_state)
	{
	case SonicState::NONE:
		break;
	case SonicState::PAUSE:
		setFlipbook(_flipbook_Pause);
		break;
	case SonicState::RUNLEFT_0:
		setFlipbook(_flipbook_RunningLeft_0);
		break;
	case SonicState::RUNLEFT_45:
		setFlipbook(_flipbook_RunningLeft_45);
		break;
	case SonicState::RUNLEFT_90:
		setFlipbook(_flipbook_RunningLeft_90);
		break;
	case SonicState::RUNLEFT_135:
		setFlipbook(_flipbook_RunningLeft_135);
		break;
	case SonicState::RUNLEFT_180:
		setFlipbook(_flipbook_RunningLeft_180);
		break;
	case SonicState::RUNLEFT_225:
		setFlipbook(_flipbook_RunningLeft_225);
		break;
	case SonicState::RUNLEFT_270:
		setFlipbook(_flipbook_RunningLeft_270);
		break;
	case SonicState::RUNLEFT_315:
		setFlipbook(_flipbook_RunningLeft_315);
		break;
	case SonicState::RUNRIGHT_0:
		setFlipbook(_flipbook_RunningRight_0);
		break;
	case SonicState::RUNRIGHT_45:
		setFlipbook(_flipbook_RunningRight_45);
		break;
	case SonicState::RUNRIGHT_90:
		setFlipbook(_flipbook_RunningRight_90);
		break;
	case SonicState::RUNRIGHT_135:
		setFlipbook(_flipbook_RunningRight_135);
		break;
	case SonicState::RUNRIGHT_180:
		setFlipbook(_flipbook_RunningRight_180);
		break;
	case SonicState::RUNRIGHT_225:
		setFlipbook(_flipbook_RunningRight_225);
		break;
	case SonicState::RUNRIGHT_270:
		setFlipbook(_flipbook_RunningRight_270);
		break;
	case SonicState::RUNRIGHT_315:
		setFlipbook(_flipbook_RunningRight_315);
		break;
	case SonicState::ROLLING:
		setFlipbook(_flipbook_Rolling);
	case SonicState::JUMPING:
		setFlipbook(_flipbook_Rolling);
		break;
	case SonicState::SKIDDLING_LEFT:
		setFlipbook(_flipbookSkiddling_Left);
		break;
	case SonicState::SKIDDLING_RIGHT:
		setFlipbook(_flipbookSkiddling_Right);
		break;
	case SonicState::SITTING:
		setFlipbook(_flipbook_Sitting);
		break;
	}
}

void Player::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);

	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (collider->GetComponentType() == eComponentType::BOX_COLLIDER &&
		other->GetComponentType() == eComponentType::BOX_COLLIDER)
	{
		AccelObj* accObj = dynamic_cast<AccelObj*>(b2);
		if (accObj != nullptr)
		{
			GetAccBuff(accObj->GetDir());
		}
		else 
		{
			AdjustCollisionPos(b1, b2);
		}
	}
	
	else 
	{
		PixelCollider* pixelcollider = dynamic_cast<PixelCollider*>(collider);
		eComponentType otherComponentType = other->GetComponentType();
		ePixelColliderType _pixelcollidertype = pixelcollider->GetPixelColliderType();
		if (otherComponentType == eComponentType::BACKGROUND_COLLIDER)
		{
			switch (_pixelcollidertype)
			{
			case ePixelColliderType::GROUND:
				//Player::OnComponentBeginOverlap_Ground_Pixel(collider);
				//_IsOnGround = true;
				break;
			case ePixelColliderType::WALL:
				break;
			case ePixelColliderType::CLIFF:
				break;
			case ePixelColliderType::CEILING:
				break;
			case ePixelColliderType::PUSH:
				break;
			default:
				break;
			}
		}
	}
}

void Player::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	// �ȼ� �ݶ��̴��鼭, ground������
	PixelCollider* pixelcollider = dynamic_cast<PixelCollider*>(collider);

	if (pixelcollider == nullptr)
		return;

	eComponentType componentType = collider->GetComponentType();
	ePixelColliderType colliderType = pixelcollider->GetPixelColliderType();

	eComponentType otherComponentType = other->GetComponentType();
	switch (colliderType)
	{
	case ePixelColliderType::GROUND:
		switch (otherComponentType)
		{
		case eComponentType::LOOP:
		{
			break;
		}
		case eComponentType::BACKGROUND_COLLIDER:
			_IsOnGround = false;
			_physic->_gravity = true;
			break;

		}

		break;
	case ePixelColliderType::WALL:
		break;
	case ePixelColliderType::CEILING:
		break;
	case ePixelColliderType::CLIFF:
		break;
	case ePixelColliderType::PUSH:
		break;
	}
}

void Player::AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2)
{
	RECT r1 = b1->GetRect();
	RECT r2 = b2->GetRect();

	Vector pos = GetPos();

	RECT intersect = {};
	if (::IntersectRect(&intersect, &r1, &r2))
	{
		int32 w = intersect.right - intersect.left;
		int32 h = intersect.bottom - intersect.top;

		if (w > h)
		{
			if (intersect.top == r2.top)
			{
				pos.y -= h;
			}
			else
			{
				pos.y += h;
			}
		}
		else
		{
			if (intersect.left == r2.left)
			{
				pos.x -= w;
			}
			else
			{
				pos.x += w;
			}
		}
	}
	SetPos(pos);
}

void Player::CheckCollision(uint8 dir)
{
	switch (dir)
	{
	case (uint8)e_SlopeType::GROUND : 
	{
		Vector LBottom = _Left_Bottom->GetPos() + Vector(0, 5);
		Vector RBottom = _Right_Bottom->GetPos() + Vector(0, 5);


		if (CheckCollision_ColorRef(LBottom, ColorRef::RED) &&
			CheckCollision_ColorRef(RBottom, ColorRef::RED))
		{
			_IsOnGround = true;
			if (_physic->Speed.x > 0)
			{
				_currCheckedPixel = _Right_Bottom->GetDir();
			}
			else if (_physic->Speed.x < 0)
			{
				_currCheckedPixel = _Left_Bottom->GetDir();
			}
			_Left_Bottom->SetIsCollided(true);
			_Right_Bottom->SetIsCollided(true);
			_pixelDoubleChecked = true;
			_slopeType = e_SlopeType::GROUND;
		}

		else if (CheckCollision_ColorRef(LBottom, ColorRef::RED))
		{
			_IsOnGround = true;
			_Left_Bottom->SetIsCollided(true);
			_Right_Bottom->SetIsCollided(false);
			_currCheckedPixel = _Left_Bottom->GetDir();
			_pixelDoubleChecked = false;
			_slopeType = e_SlopeType::GROUND;
		}

		else if (CheckCollision_ColorRef(RBottom, ColorRef::RED))
		{
			_IsOnGround = true;
			_Left_Bottom->SetIsCollided(false);
			_Right_Bottom->SetIsCollided(true);
			_currCheckedPixel = _Right_Bottom->GetDir();
			_pixelDoubleChecked = false;
			_slopeType = e_SlopeType::GROUND;
		}
		else
		{
			_IsOnGround = false;
			_Left_Bottom->SetIsCollided(false);
			_Right_Bottom->SetIsCollided(false);
			_pixelDoubleChecked = false;
			_slopeType = e_SlopeType::AIR;
		}
		break;
	}
	case (uint8)e_SlopeType::LEFT_WALL : 
	{
		Vector LBottom = _Left_Bottom->GetPos() + Vector(-5, 0);
		Vector LTop = _Left_Top->GetPos() + Vector(-5, 0);


		if (CheckCollision_ColorRef(LBottom, ColorRef::RED) &&
			CheckCollision_ColorRef(LTop, ColorRef::RED))
		{

			if (_physic->Speed.y > 0)
			{
				_currCheckedPixel = _Left_Bottom->GetDir();
			}
			else if (_physic->Speed.y < 0)
			{
				_currCheckedPixel = _Left_Top->GetDir();
			}
			_IsOnGround = true;
			_Left_Bottom->SetIsCollided(true);
			_Left_Top->SetIsCollided(true);
			_pixelDoubleChecked = true;
			_slopeType = e_SlopeType::LEFT_WALL;
		}


		else if (CheckCollision_ColorRef(LBottom, ColorRef::RED))
		{
			_IsOnGround = true;
			_Left_Bottom->SetIsCollided(true);
			_Left_Top->SetIsCollided(false);
			_currCheckedPixel = _Left_Bottom->GetDir();
			_pixelDoubleChecked = false;
			_slopeType = e_SlopeType::LEFT_WALL;
		}

		else if (CheckCollision_ColorRef(LTop, ColorRef::RED))
		{
			_IsOnGround = true;
			_Left_Bottom->SetIsCollided(false);
			_Left_Top->SetIsCollided(true);
			_currCheckedPixel = _Left_Top->GetDir();
			_pixelDoubleChecked = false;
			_slopeType = e_SlopeType::LEFT_WALL;
		}
		else
		{
			_IsOnGround = false;
			_Left_Bottom->SetIsCollided(false);
			_Left_Top->SetIsCollided(false);
			_pixelDoubleChecked = false;
			_slopeType = e_SlopeType::AIR;
		}
		break;
	}

	case (uint8)e_SlopeType::CEILING:
	{
		Vector RTop = _Right_Top->GetPos() + Vector(0, -5);
		Vector LTop = _Left_Top->GetPos() + Vector(0, -5);


		if (CheckCollision_ColorRef(RTop, ColorRef::RED) &&
			CheckCollision_ColorRef(LTop, ColorRef::RED))
		{
			_IsOnGround = true;
			if (_physic->Speed.x > 0)
			{
				_currCheckedPixel = _Right_Top->GetDir();
			}
			else if (_physic->Speed.x < 0)
			{
				_currCheckedPixel = _Left_Top->GetDir();
			}
			_Right_Top->SetIsCollided(true);
			_Left_Top->SetIsCollided(true);
			_pixelDoubleChecked = true;
			_slopeType = e_SlopeType::CEILING;
		}


		else if (CheckCollision_ColorRef(RTop, ColorRef::RED))
		{
			_IsOnGround = true;
			_Right_Top->SetIsCollided(true);
			_Left_Top->SetIsCollided(false);
			_currCheckedPixel = _Right_Top->GetDir();
			_pixelDoubleChecked = false;
			_slopeType = e_SlopeType::CEILING;
		}

		else if (CheckCollision_ColorRef(LTop, ColorRef::RED))
		{
			_IsOnGround = true;
			_Right_Top->SetIsCollided(false);
			_Left_Top->SetIsCollided(true);
			_currCheckedPixel = _Left_Top->GetDir();
			_pixelDoubleChecked = false;
			_slopeType = e_SlopeType::CEILING;
		}
		else
		{
			_IsOnGround = false;
			_Right_Top->SetIsCollided(false);
			_Left_Top->SetIsCollided(false);
			_pixelDoubleChecked = false;
			_slopeType = e_SlopeType::AIR;
		}
		break;
	}
	case (uint8)e_SlopeType::RIGHT_WALL:
	{
		Vector RBottom = _Right_Bottom->GetPos() + Vector(5, 0);
		Vector RTop = _Right_Top->GetPos() + Vector(5, 0);


		if (CheckCollision_ColorRef(RBottom, ColorRef::RED) &&
			CheckCollision_ColorRef(RTop, ColorRef::RED))
		{
			_IsOnGround = true;
			if (_physic->Speed.y > 0)
			{
				_currCheckedPixel = _Right_Bottom->GetDir();
			}
			else if (_physic->Speed.y < 0)
			{
				_currCheckedPixel = _Right_Top->GetDir();
			}
			_Right_Bottom->SetIsCollided(true);
			_Right_Top->SetIsCollided(true);
			_pixelDoubleChecked = true;
			_slopeType = e_SlopeType::RIGHT_WALL;
		}


		else if (CheckCollision_ColorRef(RBottom, ColorRef::RED))
		{
			_IsOnGround = true;
			_Right_Bottom->SetIsCollided(true);
			_Right_Top->SetIsCollided(false);
			_currCheckedPixel = _Right_Bottom->GetDir();
			_pixelDoubleChecked = false;
			_slopeType = e_SlopeType::RIGHT_WALL;
		}

		else if (CheckCollision_ColorRef(RTop, ColorRef::RED))
		{
			_IsOnGround = true;
			_Right_Bottom->SetIsCollided(false);
			_Right_Top->SetIsCollided(true);
			_currCheckedPixel = _Right_Top->GetDir();
			_pixelDoubleChecked = false;
			_slopeType = e_SlopeType::RIGHT_WALL;
		}
		else
		{
			_IsOnGround = false;
			_Right_Bottom->SetIsCollided(false);
			_Right_Top->SetIsCollided(false);
			_pixelDoubleChecked = false;
			_slopeType = e_SlopeType::AIR;
		}
		break;
	}

	}
}


bool Player::CheckCollision_ColorRef(Vector& pos, COLORREF color)
{
	if (_background->GetPixel(pos.x, pos.y) == color)
		return true;
	return false;
}

void Player::OnUpPressed()
{
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::W) && _IsJumped == false)
	{
		Player::JumpMovement();
	}
}

void Player::OnLeftPressed()
{
	if (_IsJumped == true)
	{
		int a = 1;
	}

	else if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::A))
	{
		LeftMovement();
	}
}

void Player::OnRightPressed()
{
	if (_IsJumped == true)
	{
		int a = 1;
	}

	else if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::D))
	{
		RightMovement();
	}
}

void Player::OnDownPressed()
{
	if (_IsJumped == true)
	{
		int a = 1;
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::S))
	{
		Player::SetSonicStateSitting();
	}
}

bool Player::AdjustMovement()
{
	if (_angle >= 3.14)
	{
		int a = 1;
	}
	if (_slopeType == e_SlopeType::AIR)
	{
		return false;
	}
	if (_currCheckedPixel == 0)
	{
		return false;
	}
	
	Vector* pixel = &_pixels[_currCheckedPixel]->GetPos();
	
	if (_pixelDoubleChecked)
	{
		
	}
	while (CheckCollision_ColorRef(*pixel, ColorRef::RED))
	{
		_pos.x -= sin(_angle);
		_pos.y -= cos(_angle);
		Player::RenewPixelLocation();
	}
	return true;
}
//
//void Player::ModifyWallMovement(ePixelDirection _dir)
//{
//	Vector* pixel = nullptr;
//	if (_dir == ePixelDirection::P_RIGHT)
//		pixel = &_Right_Bottom->GetPos();
//	else if (_dir == ePixelDirection::P_LEFT)
//		pixel = &_Left_Bottom->GetPos();
//
//	while (CheckCollision_ColorRef(*pixel, ColorRef::MANGENTA) == true ||
//		CheckCollision_ColorRef(*pixel, ColorRef::CYAN) == true)
//	{
//		_pos.y += -1;
//		RenewPixelLocation();
//	}
//}



void Player::JumpMovement()
{
	float deltaTime = GET_SINGLE(TimeManager)->Get_deltaTime();
	if (_IsOnGround == true && _angle == 0)
		_pos.y -= 10;
	else
	{
		_pos.x -= 20 * sin(_angle);
		_pos.y -= 20 * cos(_angle);
	}

	_physic->RemoveSpeedY();

	_IsJumped = true;

	_physic->_gravity = true;

	Player::SetPlayerStateOnAir();

	_rigidBody->Jump();

	SetSonicState(SonicState::JUMPING);
	Player::AdjustMovement();
	return;
}

void Player::LeftMovement()
{
	_rigidBody->MoveLeft();

	if (_IsOnGround == true)
	{
		AdjustState_Angle_LEFT();
	}
	//Player::SetMovement();
}

void Player::RightMovement()
{
	_rigidBody->MoveRight();

	if (_IsOnGround == true)
	{
		AdjustState_Angle_RIGHT();
	}
	//Player::SetMovement();
}

bool Player::IsSkiddlingCondition()
{
	if ((GET_SINGLE(InputManager)->GetButtonNone(KeyType::D) &&
		GET_SINGLE(InputManager)->GetButtonNone(KeyType::A)) &&
		(_IsOnGround == true || _IsOnRWall == true || _IsOnLWall == true))
		return true;
	return false;
}

void Player::GetAccBuff(Vector dir)
{
	float deltaTime = GET_SINGLE(TimeManager)->Get_deltaTime();
	_physic->_groundSpeed = _physic->_maxSpeedX * deltaTime;

	float angle = atan2(dir.y, dir.x);

	_physic->Speed.x = _physic->_groundSpeed * cos(angle);
	_physic->Speed.y = _physic->_groundSpeed * -sin(angle);
}

void Player::OnComponentBeginOverlap_Ground_Pixel(Collider* collider)
{
	PixelCollider* pixelcollider = dynamic_cast<PixelCollider*>(collider);
	switch (pixelcollider->GetPixelColliderType())
	{
	case ePixelColliderType::CEILING:
		//
		break;
	case ePixelColliderType::GROUND:
		Player::SetGravitationVec(e_SlopeType::GROUND);
		_physic->RemoveSpeedY();
		_physic->_gravity = false;
		Player::AdjustMovement();
		break;
	case ePixelColliderType::WALL:
	{
		break;
	}
	case ePixelColliderType::PUSH:

		break;
	case ePixelColliderType::CLIFF:
		// cliff�� �ȼ� 4���� 
		break;
	}
}

void Player::SetAngle()
{
	bool LParamCollideCheck = false;
	bool RParamCollideCheck = true;
	if (_currCheckedPixel == _Left_Bottom->GetDir())
	{
		{
			if (AngleCalc(_Left_Bottom->GetPos(), _Right_Bottom->GetPos(),LParamCollideCheck)==true)
			{
				SetAnglePixel(_A_Left_Bottom, _A_Right_Bottom);
				return;
			}
			else if (AngleCalc(_Left_Top->GetPos(), _Left_Bottom->GetPos(),RParamCollideCheck) == true)
			{
				SetAnglePixel(_A_Left_Top, _A_Left_Bottom);
				return;
			}
		}
	}
	else if (_currCheckedPixel == _Right_Bottom->GetDir())
	{
		{
			if (AngleCalc(_Left_Bottom->GetPos(), _Right_Bottom->GetPos(), RParamCollideCheck) == true)
			{
				SetAnglePixel(_A_Left_Bottom, _A_Right_Bottom);
				return;
			}
			else if (AngleCalc(_Right_Bottom->GetPos(), _Right_Top->GetPos(),LParamCollideCheck) == true)
			{
				SetAnglePixel(_A_Right_Bottom, _A_Right_Top);
				return;
			}
		}
	}
	else if (_currCheckedPixel == _Right_Top->GetDir())
	{
		{
			if (AngleCalc(_Right_Bottom->GetPos(), _Right_Top->GetPos(), RParamCollideCheck) == true)
			{
				SetAnglePixel(_A_Right_Bottom, _A_Right_Top);
				return;
			}
			else if (AngleCalc(_Right_Top->GetPos(), _Left_Top->GetPos(),LParamCollideCheck) == true)
			{
				SetAnglePixel(_A_Right_Top, _A_Left_Top);
				return;
			}
		}
	}
	else if (_currCheckedPixel == _Left_Top->GetDir())
	{
		{
			if (AngleCalc(_Right_Top->GetPos(), _Left_Top->GetPos(), RParamCollideCheck) == true)
			{
				SetAnglePixel(_A_Right_Top, _A_Left_Top);
				return;
			}
			else if (AngleCalc(_Left_Top->GetPos(), _Left_Bottom->GetPos(), LParamCollideCheck) == true)
			{
				SetAnglePixel(_A_Left_Top, _A_Left_Bottom);
				return;
			}
		}
	}
}

bool Player::AngleCalc(Vector pos1, Vector pos2, bool CollideFlag)
{
	if (pos1.y == pos2.y)
	{
		if (pos1.y < _pos.y)
		{
			// RightTop, LeftTop
			Vector *RightTop	= new Vector(pos1);
 			Vector *LeftTop		= new Vector(pos2);

			uint8 AddVal = 0;

			if (CollideFlag == false)
			{
				while (CheckCollision_ColorRef(*LeftTop, ColorRef::RED) ==false)
				{
					if (AddVal > _pixelDist)
					{		
						//SAFE_DELETE(_A_Left_Top, "LeftTop pixel");
						return false;
					}
					LeftTop->y -= 1;
					AddVal += 1;
				}
			}
			else if (CollideFlag == true)
			{
				while (CheckCollision_ColorRef(*RightTop, ColorRef::RED) ==false)
				{
					if (AddVal > _pixelDist)
					{
						//SAFE_DELETE(_A_Right_Top,"RightTop pixel");
						return false;
					}
					RightTop->y -= 1;
					AddVal += 1;
				}
			}
			_A_Left_Top = LeftTop;
			_A_Right_Top = RightTop;


			//SAFE_DELETE(_A_Left_Bottom, "LeftBottom pixel");
			//SAFE_DELETE(_A_Right_Bottom, "RightBottom pixel");

			float YVal = _A_Right_Top->y - _A_Left_Top->y;
			float XVal = _A_Left_Top->x - _A_Right_Top->x;
			_angle = atan2(YVal, XVal);
			return true;
		}
		else if (pos1.y > _pos.y)
		{
			//LeftBottom, RightBottom
			Vector* LeftBottom		= new Vector(pos1);
			Vector* RightBottom		= new Vector(pos2);

			uint8 addVal = 0; 

			if (CollideFlag == false)
			{
				while (CheckCollision_ColorRef(*RightBottom, ColorRef::RED) == false)
				{
					if (addVal > _pixelDist)
					{
						//SAFE_DELETE(_A_Right_Bottom, "RightBottom pixel");
						return false;
					}
					RightBottom->y += 1;
					addVal += 1;
				}
			}
			else if (CollideFlag == true)
			{
				while (CheckCollision_ColorRef(*LeftBottom, ColorRef::RED) == false)
				{
					if (addVal > _pixelDist)
					{
						//SAFE_DELETE(_A_Left_Bottom, "RightBottom pixel");
						return false;
					}
					LeftBottom->y += 1;
					addVal += 1;
				}
			}
			_A_Left_Bottom	= LeftBottom;
			_A_Right_Bottom	= RightBottom;

			//SAFE_DELETE(_A_Left_Top, "LeftTop pixel");
			//SAFE_DELETE(_A_Right_Top, "RightTop pixel");

			float YVal = _A_Left_Bottom->y - _A_Right_Bottom->y;
			float XVal = _A_Right_Bottom->x - _A_Left_Bottom->x;

			_angle = atan2(YVal, XVal);
			return true;
		}
	}
	else if (pos1.x == pos2.x)
	{
		if (pos1.x < _pos.x)
		{
			// LeftTop LeftBottom

			Vector* LeftTop		= new Vector(pos1);
			Vector* LeftBottom	= new Vector(pos2);

			uint8 addVal = 0;

			if (CollideFlag == false)
			{
				while (CheckCollision_ColorRef(*LeftBottom, ColorRef::RED) == false)
				{
					if (addVal > _pixelDist)
					{
						//SAFE_DELETE(_A_Left_Bottom, "LeftBottom pixel");
						return false;
					}
					LeftBottom->x -= 1;
					addVal += 1;
				}
			}
			else if (CollideFlag == true)
			{
				while (CheckCollision_ColorRef(*LeftTop, ColorRef::RED) == false)
				{
					if (addVal > _pixelDist)
					{
						//SAFE_DELETE(_A_Left_Top, "LeftTop pixel");
						return false;
					}
					LeftTop->x -= 1;
					addVal += 1;
				}
			}
			_A_Left_Top = LeftTop;
			_A_Left_Bottom = LeftBottom;

			//SAFE_DELETE(_A_Right_Top, "RightTop pixel");
			//SAFE_DELETE(_A_Right_Bottom, "RightBottom pixel")

			float YVal = _A_Left_Top->y - _A_Left_Bottom->y;
			float XVal = _A_Left_Bottom->x - _A_Left_Top->x;
			_angle = atan2(YVal, XVal);
			return true;
		}

		else if (pos1.x > _pos.x)
		{
			// RightBottom, RightTop
			Vector* RightBottom	= new Vector(pos1);
			Vector* RightTop	= new Vector(pos2);

			uint8 addVal = 0;

			if (CollideFlag == false)
			{
				while (CheckCollision_ColorRef(*RightTop, ColorRef::RED) == false)
				{
					if (addVal > _pixelDist)
					{
						//SAFE_DELETE(_A_Right_Top, "RightTop pixel");
						return false;
					}
					RightTop->x += 1;
					addVal += 1;
				}
			}
			else if (CollideFlag == true)
			{
				while (CheckCollision_ColorRef(*RightBottom, ColorRef::RED) == false)
				{
					if (addVal > _pixelDist)
					{
						//SAFE_DELETE(_A_Right_Bottom, "RightBottom pixel");
						return false;
					}
					RightBottom->x += 1;
					addVal += 1;
				}
			}
			_A_Right_Bottom		= RightBottom;
			_A_Right_Top		= RightTop;

			//SAFE_DELETE(_A_Left_Top, "LeftTop pixel");
			//SAFE_DELETE(_A_Left_Bottom, "LeftBottom pixel");

			float YVal = _A_Right_Bottom->y - _A_Right_Top->y;
			float XVal = _A_Right_Top->x - _A_Right_Bottom->x;
			_angle = atan2(YVal, XVal);

			return true;
		}
	}
	return false;
}

void Player::AdjustState_Angle_LEFT()
{
	//if (_angle < 0)
	//{
	//	_angle = 2 * M_PI + _angle;
	//}
	int StandardAngle = (_angle - fmod(_angle, M_PI / 4)) / (M_PI / 4);

	switch (StandardAngle)
	{
	case 0:
		SetSonicState(SonicState::RUNLEFT_180);
		break;
	case 1:
		SetSonicState(SonicState::RUNLEFT_225);
		break;
	case 2:
		SetSonicState(SonicState::RUNLEFT_270);
		break;
	case 3:
		SetSonicState(SonicState::RUNLEFT_315);
		break;
	case 4:
		SetSonicState(SonicState::RUNLEFT_0);
		break;
	case 5:
		SetSonicState(SonicState::RUNLEFT_45);
		break;
	case 6:
		SetSonicState(SonicState::RUNLEFT_90);
		break;
	case 7:
		SetSonicState(SonicState::RUNLEFT_135);
		break;
	}
}

void Player::AdjustState_Angle_RIGHT()
{
	int StandardAngle;
	//if (_angle < 0)
	//{
	//	_angle = 2 * M_PI + _angle;
	//}

	StandardAngle = (_angle - fmod(_angle, M_PI / 4)) / (M_PI / 4);

	switch (StandardAngle)
	{
	case 0:
		SetSonicState(SonicState::RUNRIGHT_0);
		break;
	case 1:
		SetSonicState(SonicState::RUNRIGHT_45);
		break;
	case 2:
		SetSonicState(SonicState::RUNRIGHT_90);
		break;
	case 3:
		SetSonicState(SonicState::RUNRIGHT_135);
		break;
	case 4:
		SetSonicState(SonicState::RUNRIGHT_180);
		break;
	case 5:
		SetSonicState(SonicState::RUNRIGHT_225);
		break;
	case 6:
		SetSonicState(SonicState::RUNRIGHT_270);
		break;
	case 7:
		SetSonicState(SonicState::RUNRIGHT_315);
		break;
	}
}

void Player::SetAnglePixel(Vector* v1, Vector* v2)
{
	_A_Pixel[0] = v1;
	_A_Pixel[1] = v2;
}


void Player::SetSonicStateOnAir()
{
	if (_state != SonicState::JUMPING)
		_state = SonicState::ROLLING;

	if (_state == SonicState::JUMPING && _physic->Speed.y > 0)
		_state = SonicState::ROLLING;
}

void Player::SetSonicStateSitting()
{
	if (_state == SonicState::PAUSE)
		_state = SonicState::SITTING;
	else if (_physic->Speed.x != 0)
		_state = SonicState::ROLLING;
}

void Player::JumpStateUpdate()
{
	if ((_IsOnGround || _IsOnRWall || _IsOnLWall))
	{

		_IsJumped = false;
	}
}

void Player::SetPlayerStateOnAir()
{
	bool	_IsOnGround_Slip = false;
	bool	_IsOnLoop = false;
	bool	_IsOnGround = false;
	bool	_IsOnLWall = false;
	bool	_IsOnRWall = false;
	bool	_IsOnCeiling = false;
}

void Player::SkiddlingMovement()
{
	_rigidBody->SetFriction();

	if (_physic->Speed.x > 0)
	{
		if (_state == SonicState::ROLLING || _state == SonicState::JUMPING);
		else _state = SonicState::SKIDDLING_RIGHT;
	}
	else if (_physic->Speed.x < 0)
	{
		if (_state == SonicState::ROLLING || _state == SonicState::JUMPING);
		else _state = SonicState::SKIDDLING_LEFT;
	}
	if (_IsOnGround == true)
		Player::AdjustMovement();
}

void Player::SlideSlopeMovement()
{
	if (this->_IsOnGround == true)
	{
		if (_ctrlLockTimer == 0)
		{
			float pi = float(M_PI);
			double Right = M_PI / 8;
			double Left = 15 * M_PI / 8;
			if (abs(_rigidBody->GetPhysic()->_groundSpeed) < 3 &&
				(Left>_angle&& Right<_angle))
			{
				_ctrlLockTimer = 30;

				if (Left * 2 > _angle && Right * 28 / 15 < _angle)
				{
					// 각도에 따른 Skiddling으로 수정해야함 
					if (_angle < M_PI / 2)//&&GET_SINGLE(InputManager)->GetButtonDown(KeyType::D))
					{
						_physic->_groundSpeed -= _physic->_frictionSpeed * 2;

					}
					else if (_angle > M_PI / 2)// && GET_SINGLE(InputManager)->GetButtonDown(KeyType::A))
					{
						_physic->_groundSpeed += _physic->_frictionSpeed * 2;

					}

					_physic->Speed.x = _physic->_groundSpeed;
				}
			}
		}
		else if (_ctrlLockTimer != 0)
		{
			_ctrlLockTimer -= 1;
		}
	}
}

void Player::SetGravitationVec(e_SlopeType vec)
{
	_rigidBody->GetPhysic()->SetGravity(true);
	switch (vec)
	{
	case e_SlopeType::GROUND:
		_rigidBody->GravitationOnGround();
		break;
	case e_SlopeType::LEFT_WALL:
		_rigidBody->GravitationOnLeftWall();
		break;
	case e_SlopeType::RIGHT_WALL:
		_rigidBody->GravitationOnRightWall();
		break;
	case e_SlopeType::CEILING:
		_rigidBody->GravitationOnCeiling();

	}
}

bool Player::SetMovement()
{
	SetPos(_pos + _physic->Speed);
	
	Player::AdjustMovement();

	Player::RenewPixelLocation();

	return true;
}

void Player::RenewPixelLocation()
{
	for (auto& i : _pixels)
	{
		i.second->SetPixelPos();
	}
}