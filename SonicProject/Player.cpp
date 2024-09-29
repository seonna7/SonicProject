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

#include "CeilingPixelCollider.h"
#include "GroundPixelCollider.h"
#include "PushPixelCollider.h"
#include "WallPixelCollider.h"
#include "CliffPixelCollider.h"
#include "LoopCollider.h"
#include "CollisionManager.h"
#define ONAIR									\
	_IsOnGround_Slip	= false					\
	_IsOnLoop			= false					\
	_IsOnGround			= false					\
	_IsOnLWall			= false					\
	_IsOnRWall			= false					\
	_checkCeiling		= false					\		


#define AdjustAllPixelCollider					\
{												\
	_ceilingPixelCollider->AdjustPixels();		\
	_groundPixelCollider->AdjustPixels();		\
	_pushPixelCollider->AdjustPixels();			\
	_RwallPixelCollider->AdjustPixels();		\
	_LwallPixelCollider->AdjustPixels();		\
}


//===================================================================
//								RULES
//===================================================================
// 1. 내가 지금 접촉한 경사면은 비트 연산으로 인해서 동시 접촉이 가능하다
//		경사면의 각도 세팅에 대한 우선순위는 다음과 같다
//		AIR -> GROUND -> CEILING -> LWALL -> RWALL	
// 
// 2. 포지션 수정 후 CorrectingMovement로 좆같은 덜덜거림을 없앤다 
// 3. 포지션 수정 후 AdjustAllPixelCollider로 픽셀 위치를 좆같게 하지 않는다 
// 4. 함수 중복이 일어나면 무조건 줄여라 
// 5. 대가리 안돌아가면 시간끌지 말고 딸잡고 와라 
// 6. 이상한 코드 싸지마라  
//====================================================================

Player::Player()  
{
#pragma region FlipBook 가져오기 
	{
		_flipbook_Pause = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Standing");

		_flipbookSkiddling_Left = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Skiddling_Left");
		_flipbookSkiddling_Right = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Skiddling_Right");

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

		_flipbook_Rolling = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Rolling");
		_flipbook_Sitting = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Sitting");
	}
	
#pragma region 카메라 추가
	{
		CameraComponent* camera = new CameraComponent(this);
	}

#pragma region rigidBody 추가
	 {
		 _rigidBody = new RigidBody(this, new Physic());
		 SetRigidBody(_rigidBody);
		 _physic = _rigidBody->GetPhysic();
	 }

#pragma region pixelCollider 추가 
	 {
		 _ceilingPixelCollider = new CeilingPixelCollider(this);
		 _groundPixelCollider = new GroundPixelCollider(this);
		 _pushPixelCollider= new PushPixelCollider(this);
		 _RwallPixelCollider = new WallPixelCollider(this, ePixelDirection::P_RIGHT);
		 _LwallPixelCollider = new WallPixelCollider(this, ePixelDirection::P_LEFT);
		 _cliffPixelCollider = new CliffPixelCollider(this);
	 }
}

Player::~Player()
{
	for(int i = 0 ; i<2; i++)
	{
		if (_anglePixel[i] != nullptr)
		{
			SAFE_DELETE(_anglePixel[i], "delete");
		}
	}

	SAFE_DELETE(_currLoop, "delete");
}

void Player::BeginPlay()
{	
	Super::BeginPlay();
	setFlipbook(_flipbook_Pause);
}

void Player::Tick()
{
	Super::Tick();
	float deltaTime = GET_SINGLE(TimeManager)->Get_deltaTime();

	_IsOnGround = Player::CheckCollision_Ground();

	if (_IsOnGround == false)
	{
		Player::SetGravitationVec(GravitationVec::GROUND);
	}

	else if (_IsOnGround==true)
	{
		_rigidBody->GetPhysic()->RemoveSpeedY();
		_slopeType = SlopeType::GROUND;
	}

	if (_onLoopCondition == false)
	{
		
	}

	Player::JumpStateUpdate();

	Player::SetAngle(_slopeType);
	
	if (_IsOnGround == true && _physic->Speed == Vector{ 0,0 })
		SetSonicState(SonicState::PAUSE);
	
	GET_SINGLE(EventManager)->InputEventFunctionExecution();

	if(_currLoop!=nullptr)
	{
	}

	// 루프 실패 움직임 
	if ((_onLoopCondition == true) &&
		(GET_SINGLE(InputManager)->GetButtonUp(KeyType::D) ||
			GET_SINGLE(InputManager)->GetButtonUp(KeyType::A)))
	{
		_onLoopCondition = false;
		_currLoop->SetIsLoopCoursePassed(false);
	}

	if (IsLoopFailed())
	{
		LoopFailedProcess();
	}

	if (IsSkiddlingCondition())
	{
		Player::SkiddlingMovement();
	}

	Player::AdjustMovement();
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);

#pragma region 플레이어 상태 출력 
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
			wstring str = std::format(L"onLoop({0})", _onLoopCondition);
			::TextOut(hdc, 10, 230, str.c_str(), static_cast<int32>(str.size()));
		}
		{
			wstring str = std::format(L"Jumped({0})", _IsJumped);
			::TextOut(hdc, 10, 250, str.c_str(), static_cast<int32>(str.size()));
		}
		{
			wstring str = std::format(L"LoopJumped({0})", _onLoopJumped);
			::TextOut(hdc, 10, 270, str.c_str(), static_cast<int32>(str.size()));
		}
	}

#pragma region AnglePixel 출력 
	{
		Vector cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
		if (_anglePixel[0] != nullptr && _anglePixel[1] != nullptr)
		{
			{
				Vector pixel0 = *_anglePixel[0];
				pixel0.x -= (cameraPos.x - GWinSizeX / 2);
				pixel0.y -= (cameraPos.y - GWinSizeY / 2);
				Utils::DrawCircle(hdc, pixel0, PixelSize);
			}
			{
				Vector pixel1 = *_anglePixel[1];
				pixel1.x -= (cameraPos.x - GWinSizeX / 2);
				pixel1.y -= (cameraPos.y - GWinSizeY / 2);
				Utils::DrawCircle(hdc, pixel1, PixelSize);
			}
		}
	}

	Player::FinalRender(hdc);
}

void Player::FinalRender(HDC hdc)
{
	AdjustAllPixelCollider;
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
	case SonicState::RUNLEFT_0 : 
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
	case SonicState::JUMPING :
		setFlipbook(_flipbook_Rolling);
		break;
	case SonicState::SKIDDLING_LEFT:
		setFlipbook(_flipbookSkiddling_Left);
		break;
	case SonicState::SKIDDLING_RIGHT:
		setFlipbook(_flipbookSkiddling_Right);
		break;
	case SonicState::SITTING : 
		setFlipbook(_flipbook_Sitting);
		break;
	}
}

void Player::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
#pragma region BoxCollider에 대한 충돌 처리
	{
		BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);

		BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

		if (collider->GetComponentType() == eComponentType::BOX_COLLIDER &&
			other->GetComponentType() == eComponentType::BOX_COLLIDER)
			AdjustCollisionPos(b1, b2);
	}

	PixelCollider* pixelcollider = dynamic_cast<PixelCollider*>(collider);
	eComponentType otherComponentType = other->GetComponentType();
	ePixelColliderType _pixelcollidertype = pixelcollider->GetPixelColliderType();
	if ( otherComponentType == eComponentType::BACKGROUND_COLLIDER)
	{
		switch (_pixelcollidertype)
		{
		case ePixelColliderType::GROUND : 
			Player::OnComponentBeginOverlap_Ground_Pixel(collider);
			_IsOnGround = true;
			break;
		case ePixelColliderType::WALL:
			break;
		case ePixelColliderType::CLIFF : 
			break;
		case ePixelColliderType::CEILING : 
			break;
		case ePixelColliderType::PUSH : 
			break;
		default : 
			break;
		}
	}
}

void Player::OnComponentEndOverlap(Collider* collider, Collider* other)
{


	// 픽셀 콜라이더면서, ground여야함
	PixelCollider* pixelcollider = dynamic_cast<PixelCollider*>(collider);
	
	if (pixelcollider == nullptr)
		return;
	
	eComponentType componentType = collider->GetComponentType();
	ePixelColliderType colliderType = pixelcollider->GetPixelColliderType();
	
	eComponentType otherComponentType = other->GetComponentType();
	switch (colliderType)
	{
	case ePixelColliderType::GROUND :  
		switch (otherComponentType)
		{
			case eComponentType::LOOP :
			{
				LoopCollider* loopcollider = dynamic_cast<LoopCollider*>(other);
				if (loopcollider->GetIsLoopCoursePassed() == true)
				{
					
				}
				else
				{
					if (loopcollider->GetDirection() == ePixelDirection::P_LEFT)
					{
						loopcollider->SetDirection(ePixelDirection::P_RIGHT);
					}
					else if (loopcollider->GetDirection() == ePixelDirection::P_RIGHT)
					{
						loopcollider->SetDirection(ePixelDirection::P_LEFT);
					}
				}
			}
			case eComponentType::BACKGROUND_COLLIDER : 
				_IsOnGround = false;
				_physic->_gravity = true;
				_slopeType = SlopeType::AIR;
				break;

		}

		break;
	case ePixelColliderType::WALL : 
		break;
	case ePixelColliderType::CEILING : 
		break;
	case ePixelColliderType::CLIFF : 
		break;
	case ePixelColliderType::PUSH : 
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

bool Player::CheckCollision_Ground()
{
	Vector Ground= _groundPixelCollider->GetPixel();
	Ground.y += 3;
	if (CheckCollsion_ColorRef(Ground, ColorRef::RED))
		return true;

	return false;
}


bool Player::CheckCollsion_ColorRef(Vector& pos, COLORREF color)
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
	if (_onLoopJumped == true || _IsJumped == true)
	{
		int a = 1;
	}

	else if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::A))
	{
		Player::MovementCallBack
		(&Player::IsMeetingLoopPassCondition,
			ePixelDirection::P_LEFT,
			&Player::LoopMovement,
			&Player::LeftMovement);
	}
}

void Player::OnRightPressed()
{
	if (_onLoopJumped == true || _IsJumped == true)
	{
		int a = 1;
	}

	else if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::D))
	{
		Player::MovementCallBack
		(&Player::IsMeetingLoopPassCondition,
			ePixelDirection::P_RIGHT,
			&Player::LoopMovement,
			&Player::RightMovement);
	}
}

void Player::OnDownPressed()
{
	if (_onLoopJumped == true || _IsJumped == true)
	{
		int a = 1;
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::S))
	{
		Player::SetSonicStateSitting();
	}
}

void Player::ModifyGroundMovement()
{
	Vector& pixel = _groundPixelCollider->GetPixel();
	bool CollisionDetect = 1;
	
	bool RunLeft = (_physic->Speed.x < 0) && (_IsOnGround == true);
	bool RunRight = (_physic->Speed.x > 0) && (_IsOnGround == true);

	bool LeftHighSlope = (_angle > 3 * M_PI / 4 && _angle < 4 * M_PI / 4);
	bool RightHighSlope = ((_angle > 0 * M_PI / 4 && _angle < 1 * M_PI / 4) || (_angle < 0));
	
	if (RunLeft == true && LeftHighSlope)
		CollisionDetect = 0;
	else if (RunRight == true && RightHighSlope)
		CollisionDetect = 0;


	int addVal = ((CollisionDetect) ? -1 : 1);
	while (CheckCollsion_ColorRef(pixel,ColorRef::RED) == CollisionDetect)
	{
		_pos.y += addVal;
		AdjustAllPixelCollider;
	}
	_IsOnGround = true;
	
	#pragma region 벽 충돌 확인 
	{
		Vector& Rwall = _RwallPixelCollider->GetPixel();
		while (CheckCollsion_ColorRef(Rwall, ColorRef::RED) == true)
		{
			_pos.y -= 1;
			AdjustAllPixelCollider;
		}
		Vector& Lwall = _LwallPixelCollider->GetPixel();
		while (CheckCollsion_ColorRef(Lwall, ColorRef::RED) == true)
		{
			_pos.y -= 1;
			AdjustAllPixelCollider;
		}
	}
}

void Player::ModifyWallMovement(ePixelDirection _dir)
{
	Vector* pixel = nullptr;
	if(_dir ==ePixelDirection::P_RIGHT)
		pixel = &_RwallPixelCollider->GetPixel();
	else if (_dir == ePixelDirection::P_LEFT)
		pixel = &_LwallPixelCollider->GetPixel();
	
	while (CheckCollsion_ColorRef(*pixel,ColorRef::MANGENTA) == true||
		CheckCollsion_ColorRef(*pixel, ColorRef::CYAN) == true)
	{
		_pos.y += -1;
		AdjustAllPixelCollider;
	}
}

void Player::SlipMovement()
{
	if (abs(_angle) <= 0.f)
		return;

	if (IsOnLoopCircle() == false)
		return;

	// MAGENTA ver
	if (_pos.x >= _currLoopPos.x &&
		(_angle >= 0 * M_PI / 4 && _angle <= 1 * M_PI / 4))
	{
		_physic->Speed.x = -3;
		SetPos(_pos + _physic->Speed);
		//CorrectingMovementOnGround(ePixelDirection::P_RIGHT);
	}
	else if (_pos.x < _currLoopPos.x &&
		(_angle >= 3 * M_PI / 4 && _angle >= 4 * M_PI / 4))
	{
		_physic->Speed.x = 3;
		SetPos(_pos + _physic->Speed);
		//CorrectingMovementOnGround(ePixelDirection::P_LEFT);
	}
	_state = SonicState::ROLLING;
}

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

	_physic->Speed.x -= _physic->_jumpForce * deltaTime * sin(_angle);
	_physic->Speed.y -= _physic->_jumpForce * deltaTime * cos(_angle);
	
	if(_onLoopCondition ==true)
	{
		_onLoopCondition = false;
		_onLoopPlayerAngle._myDegree = 0;
		_onLoopJumped = false;
	}

	_IsJumped = true;

	_physic->_gravity = true;

	Player::SetPlayerStateOnAir();

	_rigidBody->Jump();

	SetSonicState(SonicState::JUMPING);
	Player::ModifyGroundMovement();
	return;
}

void Player::LeftMovement()
{
	_rigidBody->MoveLeft();

	if (_IsOnGround == true)
	{
		if (_state == SonicState::ROLLING);
		AdjustState_Angle_LEFT();
	}
	Player::AdjustMovement();
}

void Player::RightMovement()
{
	_rigidBody->MoveRight();

	if (_IsOnGround == true)
	{
		AdjustState_Angle_RIGHT();
	}
	Player::AdjustMovement();
}

bool Player::IsSkiddlingCondition()
{
	if (GET_SINGLE(InputManager)->GetButtonNone(KeyType::D) &&
		GET_SINGLE(InputManager)->GetButtonNone(KeyType::A) &&
		(_IsOnGround == true || _IsOnRWall == true || _IsOnLWall == true))
		return true;
	return false;
}

void Player::MovementCallBack
   (bool(Player::* LoopFunc)(ePixelDirection), 
	ePixelDirection _dir, 
	void(Player::* SucceedFunc)(ePixelDirection),
	void(Player::* FailedFunc)())
{
	if ((this->*LoopFunc)(_dir))
		(this->*SucceedFunc)(_dir);
	else
		(this->*FailedFunc)();

	Player::AdjustMovement();
}

bool Player::IsMeetingLoopPassCondition(ePixelDirection _dir)
{
	bool DIRECTION = (bool)_dir;

	if (_state == SonicState::JUMPING)
		return false;

	if (_loopInfo.size() == 0)
		return false;

	float deltaTime = GET_SINGLE(TimeManager)->Get_deltaTime();

	if (abs(_onLoopPlayerAngle._myDegree) >= 340.f)
	{
		_currLoop->SetIsLoopCoursePassed(true);
		if (_currLoop->GetDirection() == ePixelDirection::P_RIGHT)
			_currLoop->SetDirection(ePixelDirection::P_RIGHT);
		else
			_currLoop->SetDirection(ePixelDirection::P_LEFT);
	}

	if (_onLoopCondition == true && ((_onLoopPlayerAngle._myDegree >= 360.f) ||
		(_onLoopPlayerAngle._myDegree <= -360.f)))
	{
		_onLoopPlayerAngle = DIRECTION ? 360.f : -360.f; 
		if ((_pos - _currLoopPos).Length() >= _radius + 1 )
		{
			_onLoopCondition = false;
			_onLoopPlayerAngle = 0.f;
			_currLoop->SetIsLoopCoursePassed(false);
		}
	}
	else if (_onLoopCondition == false)
	{
		for (LoopCollider* loopInfo : _loopInfo)
		{
			bool CheckPosX = DIRECTION ?  _pos.x >= _currLoopPos.x : _pos.x <= _currLoopPos.x;
			bool LoopDirCheck;
			if( DIRECTION ==false && loopInfo->GetDirection()==ePixelDirection::P_LEFT||
				DIRECTION == true && loopInfo->GetDirection() == ePixelDirection::P_RIGHT)
			{
				if (CheckPosX == true && (_pos - loopInfo->GetPos()).Length() <= _radius - 100 / 1.8 + 35
					&& ((_state == SonicState::RUNRIGHT_0) || (_state == SonicState::RUNLEFT_180)))
				{
					Player::SetAngleSpeed();
					_onLoopCondition = true;
					_onLoopPlayerAngle = 0.f;
					_currLoop = loopInfo;
					_currLoopPos = loopInfo->GetPos();
				}
			}
		}
	} 
	return _onLoopCondition;
}

void Player::LoopMovement(ePixelDirection _dir)
{
	bool DIRECTION = (bool)_dir;
	// 루프 좌표 확인 
	float deltaTime = GET_SINGLE(TimeManager)->Get_deltaTime();
	
	short Weight = (DIRECTION) ? 1 : -1;

	_physic->Speed.x = Weight * _radius * deltaTime * sin(Utils::DegreeToRadian(_onLoopPlayerAngle._WindowDegree));
	_physic->Speed.y = Weight * _radius * deltaTime * cos(Utils::DegreeToRadian(_onLoopPlayerAngle._WindowDegree));

	if (_onLoopPlayerAngle._myDegree == 360.f||_onLoopPlayerAngle._myDegree ==-360.f)
	{
		_angle = 0.f;
		_physic->Speed.x += 4 * Weight;
		SetPos(_physic->Speed+ _pos);
	}
	else 
	{
		_physic->_gravity = false;

		_pos.x = _currLoopPos.x + (_radius - (100 / 1.8) / 2) * cos(Utils::DegreeToRadian(_onLoopPlayerAngle._WindowDegree));
		_pos.y = _currLoopPos.y + (_radius - (100 / 1.8) / 2) * sin(Utils::DegreeToRadian(_onLoopPlayerAngle._WindowDegree));
		
		_onLoopPlayerAngle += _angleSpeed * deltaTime * Weight;
		
	}
	AdjustAllPixelCollider;
	
	if (_dir == ePixelDirection::P_LEFT)
		AdjustState_Angle_LEFT();
	else if (_dir == ePixelDirection::P_RIGHT)
		AdjustState_Angle_RIGHT();
	return;

}

bool Player::IsLoopFailed()
{
	if (_currLoop != nullptr)
	{
		_IsOnRWall = (Player::CheckCollsion_ColorRef(_RwallPixelCollider->GetPixel(), ColorRef::MANGENTA) &&
			_currLoop->GetIsLoopCoursePassed() == false && _currLoop->GetDirection() == ePixelDirection::P_RIGHT);

		if (_IsOnRWall == true)
		{
			return true;
		}

		_IsOnLWall = (Player::CheckCollsion_ColorRef(_LwallPixelCollider->GetPixel(), ColorRef::CYAN) &&
			_currLoop->GetIsLoopCoursePassed() == false && _currLoop->GetDirection() == ePixelDirection::P_LEFT);

		if (_IsOnLWall == true)
		{
			return true;
		}
	}
	return false;
}


void Player::SetAngleSpeed()
{
	float SpeedVal = abs(_physic->Speed.x);
	if (SpeedVal > 2.3)
		_angleSpeed = 200.f;
	else
		_angleSpeed = 200.f;
}

bool Player::IsOnLoopCircle()
{
	return (_pos - _currLoopPos).Length() <= _radius;
}

void Player::LoopFailedProcess()
{
	_IsOnRWall = (Player::CheckCollsion_ColorRef(_RwallPixelCollider->GetPixel(), ColorRef::MANGENTA) &&
		_currLoop->GetIsLoopCoursePassed() == false && _currLoop->GetDirection() == ePixelDirection::P_RIGHT);

	if (_IsOnRWall == true)
	{
		Vector& Rpixel = _RwallPixelCollider->GetPixel();
		while (CheckCollsion_ColorRef(Rpixel, ColorRef::MANGENTA) == true)
		{
			_pos.x -= 1;
			AdjustAllPixelCollider;
		}
	}

	_IsOnLWall = (Player::CheckCollsion_ColorRef(_LwallPixelCollider->GetPixel(), ColorRef::CYAN) &&
		_currLoop->GetIsLoopCoursePassed() == false && _currLoop->GetDirection() == ePixelDirection::P_LEFT);

	if (_IsOnLWall == true)
	{
		Vector& Lpixel = _LwallPixelCollider->GetPixel();
		while (CheckCollsion_ColorRef(Lpixel, ColorRef::CYAN) == true)
		{
			_pos.x += 1;
			AdjustAllPixelCollider;
		}
	}

}

void Player::OnComponentBeginOverlap_Ground_Pixel(Collider* collider)
{
	PixelCollider* pixelcollider = dynamic_cast<PixelCollider*>(collider);
	switch (pixelcollider->GetPixelColliderType())
	{
	case ePixelColliderType::CEILING : 
		//
		break;
	case ePixelColliderType::GROUND:
		Player::SetGravitationVec(GravitationVec::GROUND);
		_physic->RemoveSpeedY();
		_physic->_gravity = false;
		Player::ModifyGroundMovement();
		Player::SlipMovement();
		_slopeType = _slopeType | SlopeType::GROUND;
		break;
	case ePixelColliderType::WALL:
	{
		_physic->_gravity = false;

		WallPixelCollider* pixel = dynamic_cast<WallPixelCollider*>(collider);
		ePixelDirection _dir = pixel->GetPixelDirection();

		Player::ModifyWallMovement(_dir);
		if (_dir == ePixelDirection::P_LEFT)
			_slopeType = _slopeType | SlopeType::LEFT_WALL;
		else if (_dir == ePixelDirection::P_RIGHT)
			_slopeType = _slopeType | SlopeType::RIGHT_WALL;
		break;
	}
	case ePixelColliderType::PUSH : 

		break;
	case ePixelColliderType::CLIFF:
		// cliff는 픽셀 4개임 
		break;
	}
}

void Player::SetAngle(uint16 type)
{
	if (_onLoopCondition == true)
	{
		#pragma region 점프 각도 세팅 위해서 각도값 수정해야함 
		{
			_angle = Utils::DegreeToRadian(_onLoopPlayerAngle._myDegree);
			return;
		}
	}
	SlopeType currSlopeType = Player::InitAnglePixel();
	if (_anglePixel[0]==nullptr&&_anglePixel[1]==nullptr)
	{
		_angle = 0.f;
		return;
	}
	if (currSlopeType ==SlopeType::GROUND|| currSlopeType ==SlopeType::CEILING)
	{
		uint8 leftpixelIndex = (int)ePixelDirection::P_LEFT;
		uint8 rightpixelIndex = (int)ePixelDirection::P_RIGHT;
		if ((CheckCollsion_ColorRef(*_anglePixel[leftpixelIndex],ColorRef::RED) == true) &&
			CheckCollsion_ColorRef(*_anglePixel[rightpixelIndex], ColorRef::RED) == true)
		{
			_angle = 0.f;
			return;
		}

		//Left가 걸린 경우 
		else if (CheckCollsion_ColorRef(*_anglePixel[leftpixelIndex],ColorRef::RED) == true)
		{
			while (CheckCollsion_ColorRef(*_anglePixel[leftpixelIndex],ColorRef::RED) == true)
				_anglePixel[leftpixelIndex]->y -= 1;
			while (CheckCollsion_ColorRef(*_anglePixel[rightpixelIndex], ColorRef::RED) == false)
			{
				_anglePixel[rightpixelIndex]->y += 1;
			}
		}
		// Right가 걸린 경우 
		else if(CheckCollsion_ColorRef(*_anglePixel[rightpixelIndex], ColorRef::RED) == true)
		{
			while (CheckCollsion_ColorRef(*_anglePixel[rightpixelIndex],ColorRef::RED) == true)
				_anglePixel[rightpixelIndex]->y -= 1;
			while (CheckCollsion_ColorRef(*_anglePixel[leftpixelIndex], ColorRef::RED) == false)
				_anglePixel[leftpixelIndex]->y += 1;
		}
		
		float Xval = (_anglePixel[rightpixelIndex]->x - _anglePixel[leftpixelIndex]->x);
		float Yval = (-1) * (_anglePixel[rightpixelIndex]->y - _anglePixel[leftpixelIndex]->y);
		if (abs(Yval) < 5)
			_angle = 0;
		else 
			_angle = atan2(Yval, Xval);
	}
	else  
	{

		uint8 topPixelIndex = (uint8)ePixelDirection::P_TOP;
		uint8 bottomPixelIndex = (uint8)ePixelDirection::P_BOTTOM;

		if (currSlopeType == SlopeType::LEFT_WALL)
		{
			if (CheckCollsion_ColorRef(*_anglePixel[topPixelIndex],ColorRef::RED) == true &&
				CheckCollsion_ColorRef(*_anglePixel[bottomPixelIndex], ColorRef::RED) == true)
			{
				_angle = 3 * M_PI / 4;
				return;
			}
			// TOP 이 걸린 경우
			else if (CheckCollsion_ColorRef(*_anglePixel[topPixelIndex], ColorRef::RED) == true)
			{
				while (CheckCollsion_ColorRef(*_anglePixel[topPixelIndex], ColorRef::RED) == true)
					_anglePixel[topPixelIndex]->x += 1;
				while (CheckCollsion_ColorRef(*_anglePixel[bottomPixelIndex], ColorRef::RED) == false)
					_anglePixel[bottomPixelIndex]->x -= 1;
			}

			//BOTTOM이 걸린 경우 
			else if (CheckCollsion_ColorRef(*_anglePixel[bottomPixelIndex], ColorRef::RED) == true)
			{
				while (CheckCollsion_ColorRef(*_anglePixel[bottomPixelIndex], ColorRef::RED) == true)
					_anglePixel[bottomPixelIndex]->x += 1;
				while (CheckCollsion_ColorRef(*_anglePixel[topPixelIndex], ColorRef::RED) == false)
					_anglePixel[topPixelIndex]->x -= 1;

			}
		}
		else if (currSlopeType == SlopeType::RIGHT_WALL)
		{
			if (CheckCollsion_ColorRef(*_anglePixel[topPixelIndex], ColorRef::RED) == true &&
				CheckCollsion_ColorRef(*_anglePixel[bottomPixelIndex], ColorRef::RED) == true)
			{
				_angle = M_PI / 4;
				return;
			}
			// Top이 걸린 경우 
			else if (CheckCollsion_ColorRef(*_anglePixel[topPixelIndex], ColorRef::RED) == true)
			{
				while (CheckCollsion_ColorRef(*_anglePixel[topPixelIndex], ColorRef::RED) == true)
					_anglePixel[topPixelIndex]->x -= 1;
				while (CheckCollsion_ColorRef(*_anglePixel[bottomPixelIndex], ColorRef::RED) == false)
					_anglePixel[bottomPixelIndex]->x += 1;
			}

			//BOTTOM이 걸린 경우 
			else if (CheckCollsion_ColorRef(*_anglePixel[bottomPixelIndex], ColorRef::RED) == true)
			{
				while (CheckCollsion_ColorRef(*_anglePixel[bottomPixelIndex], ColorRef::RED) == true)
					_anglePixel[bottomPixelIndex]->x -= 1;
				while (CheckCollsion_ColorRef(*_anglePixel[topPixelIndex], ColorRef::RED) == false)
					_anglePixel[topPixelIndex]->x += 1;
			}
		}

		float Xval = (_anglePixel[topPixelIndex]->x - _anglePixel[bottomPixelIndex]->x);
		float Yval = (-1) * (_anglePixel[topPixelIndex]->y - _anglePixel[bottomPixelIndex]->y);
		if (abs(Yval) < 5)
			_angle = 0;
		else
			_angle = atan2(Yval, Xval);
	}
}

void Player::AdjustState_Angle_LEFT()
{

	float angle = abs(_angle);
	int StandardAngle = (angle - fmod(angle, M_PI / 4)) / (M_PI / 4);

	switch (StandardAngle)
	{
	case 0:
		SetSonicState(SonicState::RUNLEFT_180);
		break;
	case 1:
		SetSonicState(SonicState::RUNLEFT_135);
		break;
	case 2:
		SetSonicState(SonicState::RUNLEFT_90);
		break;
	case 3:
		SetSonicState(SonicState::RUNLEFT_45);
		break;
	case 4:
		SetSonicState(SonicState::RUNLEFT_0);
		break;
	case 5:
		SetSonicState(SonicState::RUNLEFT_315);
		break;
	case 6:
		SetSonicState(SonicState::RUNLEFT_270);
		break;
	case 7:
		SetSonicState(SonicState::RUNLEFT_225);
		break;
	}
}

void Player::AdjustState_Angle_RIGHT()
{
	int StandardAngle = (_angle - fmod(_angle, M_PI / 4)) / (M_PI / 4);

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

SlopeType Player::InitAnglePixel()
{
	BoxCollider* box = dynamic_cast<BoxCollider*>(FindComponent(eComponentType::BOX_COLLIDER));
	assert(box != nullptr);

	uint8 switchCase = 0; 
	uint8 currBit = 1;

	uint8 top		= (uint8)ePixelDirection::P_TOP;
	uint8 bottom	= (uint8)ePixelDirection::P_BOTTOM;
	uint8 left		= (uint8)ePixelDirection::P_LEFT;
	uint8 right		= (uint8)ePixelDirection::P_RIGHT;

	for (int i = 0; i < SLOPETYPE_SIZE; i++, currBit<<=1)
	{
		switchCase = currBit & _slopeType;
		switch (switchCase)
		{
		case SlopeType::AIR:
			_anglePixel[0] = nullptr;
			_anglePixel[1] = nullptr;
			return SlopeType::AIR;
		case SlopeType::GROUND:
			_anglePixel[left] = new Vector(_pos + Vector(-10, box->GetSize().y / 2));
			_anglePixel[right] = new Vector(_pos + Vector(10, box->GetSize().y / 2));
			return SlopeType::GROUND;
		case SlopeType::LEFT_WALL:
			_anglePixel[top] = new Vector(_pos + Vector(-box->GetSize().x / 2, -10));
			_anglePixel[bottom] = new Vector(_pos + Vector(-box->GetSize().x / 2, 10));
			return SlopeType::LEFT_WALL;
		case SlopeType::RIGHT_WALL:
			_anglePixel[top] = new Vector(_pos + Vector(box->GetSize().x / 2, -10));
			_anglePixel[bottom] = new Vector(_pos + Vector(box->GetSize().x / 2, 10));
			return SlopeType::RIGHT_WALL;
		case SlopeType::CEILING:
			_anglePixel[left] = new Vector(_pos + Vector(-10, -box->GetSize().y / 2));
			_anglePixel[right] = new Vector(_pos + Vector(10, -box->GetSize().y / 2));
			return SlopeType::CEILING;
		}
	}
	return SlopeType::AIR;
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
		_onLoopJumped = false;
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
		Player::ModifyGroundMovement();
	
}

void Player::SetGravitationVec(GravitationVec vec)
{
	_rigidBody->GetPhysic()->SetGravity(true);
	switch (vec)
	{
	case GravitationVec::GROUND : 
		_rigidBody->GravitationOnGround();
		break;
	case GravitationVec::LEFT_WALL : 
		_rigidBody->GravitationOnLeftWall();
		break;
	case GravitationVec::RIGHT_WALL :
		_rigidBody->GravitationOnRightWall();
		break;
	case GravitationVec::CEILING : 
		_rigidBody->GravitationOnCeiling();

	}
}

void Player::AdjustMovement()
{
	if (_onLoopCondition == true)
		return;
#pragma region 이동 연산 
	{
		SetPos(_pos + _physic->Speed);
		Player::ModifyGroundMovement();
		AdjustAllPixelCollider;
	}
}
