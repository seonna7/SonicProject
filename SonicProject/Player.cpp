#include "pch.h"
#include "Player.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "EventManager.h"
#include "SceneManager.h"
#include "CourseManager.h"
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
#include "CollisionManager.h"
#include "LoopCourse.h"
#include "PipeCourse.h"



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

	for (auto& pixel : _pixels)
	{
		pixel.second->TickComponent();
	}
	float deltaTime = GET_SINGLE(TimeManager)->Get_deltaTime();

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::Q))
	{
		Gravity = !Gravity;
	}
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::E))
	{
		Skiddle = !Skiddle;
	}

	if (_isCourseMovementAdjustNeeded == false)
	{
		if (Player::CheckCollision((uint8)e_SlopeType::GROUND) == true ||
			Player::CheckCollision((uint8)e_SlopeType::CEILING) == true ||
			Player::CheckCollision((uint8)e_SlopeType::LEFT_WALL) == true ||
			Player::CheckCollision((uint8)e_SlopeType::RIGHT_WALL) == true)
		{
			Player::AngleFunction();
			_angleSetted = true;
		}
	}
	else if (_isCourseMovementAdjustNeeded == true)
	{
		if (Player::CheckCollision((uint8)e_SlopeType::CEILING) == true ||
			Player::CheckCollision((uint8)e_SlopeType::RIGHT_WALL) == true ||
			Player::CheckCollision((uint8)e_SlopeType::LEFT_WALL) == true ||
			Player::CheckCollision((uint8)e_SlopeType::GROUND) == true)
		{
			if (Player::AngleFunction() == false)
			{
				_angleSetted = false;
			}
			else
			{
				_angleSetted = true;
			}
		}
	}

	Player::CourseMeetingFunction();

	if (Gravity == true)
	{
		Player::SetGravityVector(3 * M_PI / 2);
	}

	if (true)
	{
		Player::UpdateJumpState();
	}

	if (_IsOnGround == true && _physic->_groundSpeed < 0.5)
	{
		SetSonicState(SonicState::PAUSE);
	}

	OnUpPressed();
	OnLeftPressed();
	OnRightPressed();
	OnDownPressed();
	
	if (IsSkiddlingCondition() == true)
	{
		Player::SkiddlingMovement();
	}

	if(_course!=nullptr)
	{
		if (_course->GetCourseInfo() == eCourse::PIPE)
		{
			SetSonicState(SonicState::ROLLING);
		}
	}
	if (_IsOnGround == true)
	{
		//if (_angle > -M_PI / 2 && _angle < M_PI / 2&&
		//	_physic->_groundSpeed<-0.1&& _physic->Speed.x > 0.1 && _isCourseMovementAdjustNeeded == false)
		//{
		//	_physic->_groundSpeed *= -1;
		//}
		if (_isCourseMovementAdjustNeeded == true)
		{
			_physic->Speed.x = _physic->_groundSpeed * -cos(_angle);
			_physic->Speed.y = _physic->_groundSpeed * sin(_angle);
		}
		else
		{
			_physic->Speed.x = _physic->_groundSpeed * cos(_angle);
			_physic->Speed.y = _physic->_groundSpeed * -sin(_angle);
		}
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
			wstring str = std::format(L"Player Angle({0})", (_angle * 180 / M_PI));
			::TextOut(hdc, 10, 110, str.c_str(), static_cast<int32>(str.size()));
		}
		{
			wstring str = std::format(L"Player onGround({0})", _IsOnGround);
			::TextOut(hdc, 10, 130, str.c_str(), static_cast<int32>(str.size()));
		}
		{
			wstring str = std::format(L"Speed Vector({0}, {1})", _physic->Speed.x, _physic->Speed.y);
			::TextOut(hdc, 10, 150, str.c_str(), static_cast<int32>(str.size()));
		}
		{
			wstring str = std::format(L"groundSpeed({0})", _physic->_groundSpeed);
			::TextOut(hdc, 10, 170, str.c_str(), static_cast<int32>(str.size()));
		}
		{
			wstring str = std::format(L"Gravity : Q  ({0})", Gravity);
			::TextOut(hdc, 10, 190, str.c_str(), static_cast<int32>(str.size()));
		}
		{
			wstring str = std::format(L"Skiddle : E ({0})", Skiddle);
			::TextOut(hdc, 10, 210, str.c_str(), static_cast<int32>(str.size()));
		}
		{
			wstring str = std::format(L"canJump({0})", _canJump);
			::TextOut(hdc, 10, 230, str.c_str(), static_cast<int32>(str.size()));
		}

		{
			wstring str = std::format(L"courseColorRef({0})", _courseColorRef);
			::TextOut(hdc, 10, 250, str.c_str(), static_cast<int32>(str.size()));
		}
		{
			wstring str = std::format(L"_isCourseMovementAdjustNeeded({0})", _isCourseMovementAdjustNeeded);
			::TextOut(hdc, 10, 270, str.c_str(), static_cast<int32>(str.size()));
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

bool Player::CheckCollision(uint8 dir)
{
	// 픽셀 감지 상한선 
	uint8 Size = 3; 

	switch (dir)
	{
	case (uint8)e_SlopeType::GROUND : 
	{
		Vector LBottom = _Left_Bottom->GetPos() + Vector(0, Size);
		Vector RBottom = _Right_Bottom->GetPos() + Vector(0, Size);


		if ((DetectCollision_ColorRef(LBottom, ColorRef::RED) && DetectCollision_ColorRef(RBottom, ColorRef::RED)) ||
			(DetectCollision_ColorRef(LBottom, _courseColorRef) && DetectCollision_ColorRef(RBottom, _courseColorRef)))
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
			return true;
		}

		else if (DetectCollision_ColorRef(LBottom, ColorRef::RED)|| DetectCollision_ColorRef(LBottom, _courseColorRef))
		{
			_IsOnGround = true;
			_Left_Bottom->SetIsCollided(true);
			_Right_Bottom->SetIsCollided(false);
			_currCheckedPixel = _Left_Bottom->GetDir();
			_pixelDoubleChecked = false;
			_slopeType = e_SlopeType::GROUND;
			return true;
		}

		else if (DetectCollision_ColorRef(RBottom, ColorRef::RED)|| DetectCollision_ColorRef(RBottom,_courseColorRef))
		{
			_IsOnGround = true;
			_Left_Bottom->SetIsCollided(false);
			_Right_Bottom->SetIsCollided(true);
			_currCheckedPixel = _Right_Bottom->GetDir();
			_pixelDoubleChecked = false;
			_slopeType = e_SlopeType::GROUND;
			return true;
		}
		else
		{
			_IsOnGround = false;
			_Left_Bottom->SetIsCollided(false);
			_Right_Bottom->SetIsCollided(false);
			_pixelDoubleChecked = false;
			_slopeType = e_SlopeType::AIR;
			return false;
		}
		break;
	}
	case (uint8)e_SlopeType::LEFT_WALL : 
	{
		Vector LBottom = _Left_Bottom->GetPos() + Vector(-Size, 0);
		Vector LTop = _Left_Top->GetPos() + Vector(-Size, 0);


		if ((DetectCollision_ColorRef(LBottom, ColorRef::RED) && DetectCollision_ColorRef(LTop, ColorRef::RED)) ||
			(DetectCollision_ColorRef(LBottom, _courseColorRef) && DetectCollision_ColorRef(LTop, _courseColorRef)))

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
			return true;
		}


		else if (DetectCollision_ColorRef(LBottom, ColorRef::RED) || DetectCollision_ColorRef(LBottom, _courseColorRef))
		{
			_IsOnGround = true;
			_Left_Bottom->SetIsCollided(true);
			_Left_Top->SetIsCollided(false);
			_currCheckedPixel = _Left_Bottom->GetDir();
			_pixelDoubleChecked = false;
			_slopeType = e_SlopeType::LEFT_WALL;
			return true;
		}

		else if (DetectCollision_ColorRef(LTop, ColorRef::RED)|| DetectCollision_ColorRef(LTop, _courseColorRef))
		{
			_IsOnGround = true;
			_Left_Bottom->SetIsCollided(false);
			_Left_Top->SetIsCollided(true);
			_currCheckedPixel = _Left_Top->GetDir();
			_pixelDoubleChecked = false;
			_slopeType = e_SlopeType::LEFT_WALL;
			return true;
		}
		else
		{
			_IsOnGround = false;
			_Left_Bottom->SetIsCollided(false);
			_Left_Top->SetIsCollided(false);
			_pixelDoubleChecked = false;
			_slopeType = e_SlopeType::AIR;
			return false;
		}
		break;
	}

	case (uint8)e_SlopeType::CEILING:
	{
		Vector RTop = _Right_Top->GetPos() + Vector(0, -Size);
		Vector LTop = _Left_Top->GetPos() + Vector(0, -Size);


		if ((DetectCollision_ColorRef(RTop, ColorRef::RED) && DetectCollision_ColorRef(LTop, ColorRef::RED)) ||
			(DetectCollision_ColorRef(RTop, _courseColorRef) && DetectCollision_ColorRef(LTop, _courseColorRef)))
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
			return true;
		}


		else if (DetectCollision_ColorRef(RTop, ColorRef::RED)|| DetectCollision_ColorRef(RTop, _courseColorRef))
		{
			_IsOnGround = true;
			_Right_Top->SetIsCollided(true);
			_Left_Top->SetIsCollided(false);
			_currCheckedPixel = _Right_Top->GetDir();
			_pixelDoubleChecked = false;
			_slopeType = e_SlopeType::CEILING;
			return true;
		}

		else if (DetectCollision_ColorRef(LTop, ColorRef::RED)|| DetectCollision_ColorRef(LTop, _courseColorRef))
		{
			_IsOnGround = true;
			_Right_Top->SetIsCollided(false);
			_Left_Top->SetIsCollided(true);
			_currCheckedPixel = _Left_Top->GetDir();
			_pixelDoubleChecked = false;
			_slopeType = e_SlopeType::CEILING;
			return true;
		}
		else
		{
			_IsOnGround = false;
			_Right_Top->SetIsCollided(false);
			_Left_Top->SetIsCollided(false);
			_pixelDoubleChecked = false;
			_slopeType = e_SlopeType::AIR;
			return false;
		}
		break;
	}
	case (uint8)e_SlopeType::RIGHT_WALL:
	{
		Vector RBottom = _Right_Bottom->GetPos() + Vector(Size, 0);
		Vector RTop = _Right_Top->GetPos() + Vector(Size, 0);


		if ((DetectCollision_ColorRef(RBottom, ColorRef::RED) && DetectCollision_ColorRef(RTop, ColorRef::RED)) ||
			(DetectCollision_ColorRef(RBottom, _courseColorRef) && DetectCollision_ColorRef(RTop, _courseColorRef)))
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
			return true;
		}


		else if (DetectCollision_ColorRef(RBottom, ColorRef::RED)|| DetectCollision_ColorRef(RBottom, _courseColorRef))
		{
			_IsOnGround = true;
			_Right_Bottom->SetIsCollided(true);
			_Right_Top->SetIsCollided(false);
			_currCheckedPixel = _Right_Bottom->GetDir();
			_pixelDoubleChecked = false;
			_slopeType = e_SlopeType::RIGHT_WALL;
			return true;
		}

		else if (DetectCollision_ColorRef(RTop, ColorRef::RED)|| DetectCollision_ColorRef(RTop, _courseColorRef))
		{
			_IsOnGround = true;
			_Right_Bottom->SetIsCollided(false);
			_Right_Top->SetIsCollided(true);
			_currCheckedPixel = _Right_Top->GetDir();
			_pixelDoubleChecked = false;
			_slopeType = e_SlopeType::RIGHT_WALL;
			return true;
		}
		else
		{
			_IsOnGround = false;
			_Right_Bottom->SetIsCollided(false);
			_Right_Top->SetIsCollided(false);
			_pixelDoubleChecked = false;
			_slopeType = e_SlopeType::AIR;
			return false;
		}
		break;
	}

	}
	return false;
}


bool Player::DetectCollision_ColorRef(Vector& pos, COLORREF color)
{
	if (_background->GetPixel(pos.x, pos.y) == color)
		return true;
	return false;
}

void Player::OnUpPressed()
{
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::W) && _canJump == true)
	{
		Player::JumpMovement();
		SetSonicState(SonicState::JUMPING);
	}
}

void Player::OnLeftPressed()
{
	if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::A))
	{
		LeftMovement();

		if (_IsOnGround == true)
		{
			SonicFlipBookAngleMatch(_left);
		}
	}
}

void Player::OnRightPressed()
{
	if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::D))
	{
		RightMovement();

		if (_IsOnGround == true)
		{
			SonicFlipBookAngleMatch(_right);
		}
	}
}

void Player::OnDownPressed()
{
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::S))
	{
		Player::SetSonicStateSitting();
	}
}

bool Player::AdjustMovement()
{
	if (_IsOnGround == false && _isCourseMovementAdjustNeeded == false)
	{
		return false;
	}
	if (_currCheckedPixel == 0)
	{
		return false;
	}
	
	Vector* pixel = &_pixels[_currCheckedPixel]->GetPos();
	
	
	while (DetectCollision_ColorRef(*pixel, _courseColorRef) ||
		DetectCollision_ColorRef(*pixel, ColorRef::RED))
	{
		_pos.x -= sin(_angle);
		_pos.y -= cos(_angle);
		Player::RenewPixelLocation();
	}
	if (_pixelDoubleChecked == true)
	{

	}
	return true;
}



void Player::JumpMovement()
{
	float deltaTime = GET_SINGLE(TimeManager)->Get_deltaTime();
	if (_IsOnGround == true && _angle == 0)
		_pos.y -= 10;
	else
	{
		_pos.x += 20 * sin(_angle);
		_pos.y -= 20 * cos(_angle);
	}

	_physic->RemoveSpeedY();

	_canJump = false;

	_physic->_gravity = true;

	_IsOnGround = false;

	_rigidBody->Jump();


	Player::AdjustMovement();
	return;
}

void Player::LeftMovement()
{
	_rigidBody->MoveLeft();
}

void Player::RightMovement()
{
	_rigidBody->MoveRight();
}

bool Player::IsSkiddlingCondition()
{
	if (Skiddle == false)
	{
		return false;
	}
	if ((GET_SINGLE(InputManager)->GetButtonNone(KeyType::D) &&
		GET_SINGLE(InputManager)->GetButtonNone(KeyType::A)) &&
		(_IsOnGround == true))
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

bool Player::IsCourseContacted()
{
	Course* course = GET_SINGLE(CourseManager)->GetContactedCourse();
	if (course!= nullptr)
	{
		return true;
	}
	return false;
}

bool Player::CourseMeetingFunction()
{
	if (GET_SINGLE(CourseManager)->GetContactedCourse()==nullptr)
	{
		_isCourseMovementAdjustNeeded = false;
		Gravity = true;
		_course = new Course();
		return false;
	}
	_course = GET_SINGLE(CourseManager)->GetContactedCourse();
	
	if (_course->GetCourseInfo() ==eCourse::NONE)
	{
		_isCourseMovementAdjustNeeded = false;
		Gravity = true;
		return false;
	}


	_courseColorRef = _course->GetColorRef();

	eCourse info = _course->GetCourseInfo();

	switch (info)
	{
	case eCourse::PIPE : 
	{
		PipeCourse* pipe = dynamic_cast<PipeCourse*>(_course);
		if (_courseColorRef == ColorRef::MAGENTA)
		{
			if (pipe->IsRunnerCorrectlyInPipeSection() == true)
				_isCourseMovementAdjustNeeded = true;
			Player::SetGravityVector(M_PI / 3);
		}
		else if (_courseColorRef == ColorRef::CYAN)
		{
			_isCourseMovementAdjustNeeded = false;
			Player::SetGravityVector(M_PI);
		}
	}
		
		break;
	case eCourse::LOOP :
		if (_canJump == false)
		{
			Gravity = true;
		}
		else
		{
			Gravity = false;
		}
		_courseMovementFlag = false;
		_isCourseMovementAdjustNeeded = false;

		
	}
	return true;
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
		Player::SetGravityVector(3*M_PI/2);
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

bool Player::AngleFunction()
{
	bool LParamCollideCheck = false;
	bool RParamCollideCheck = true;
	if (_currCheckedPixel == _Left_Bottom->GetDir())
	{
		{
			if (AngleCalc(_Left_Bottom->GetPos(), _Right_Bottom->GetPos(),LParamCollideCheck)==true)
			{
				SetAnglePixel(_A_Left_Bottom, _A_Right_Bottom);
				return true;
			}
			else if (AngleCalc(_Left_Top->GetPos(), _Left_Bottom->GetPos(),RParamCollideCheck) == true)
			{
				SetAnglePixel(_A_Left_Top, _A_Left_Bottom);
				return true;
			}
			else
			{
				_angle = 0;
				return false;
			}
		}
	}
	else if (_currCheckedPixel == _Right_Bottom->GetDir())
	{
		{
			if (AngleCalc(_Left_Bottom->GetPos(), _Right_Bottom->GetPos(), RParamCollideCheck) == true)
			{
				SetAnglePixel(_A_Left_Bottom, _A_Right_Bottom);
				return true;
			}
			else if (AngleCalc(_Right_Bottom->GetPos(), _Right_Top->GetPos(),LParamCollideCheck) == true)
			{
				SetAnglePixel(_A_Right_Bottom, _A_Right_Top);
				return true;
			}
			else
			{
				_angle = 0;
				return false;
			}
		}
	}
	else if (_currCheckedPixel == _Right_Top->GetDir())
	{
		{
			if (AngleCalc(_Right_Bottom->GetPos(), _Right_Top->GetPos(), RParamCollideCheck) == true)
			{
				SetAnglePixel(_A_Right_Bottom, _A_Right_Top);
				return true;
			}
			else if (AngleCalc(_Right_Top->GetPos(), _Left_Top->GetPos(),LParamCollideCheck) == true)
			{
				SetAnglePixel(_A_Right_Top, _A_Left_Top);
				return true;
			}
			else
			{
				_angle = 0;
				return false;
			}
		}
	}
	else if (_currCheckedPixel == _Left_Top->GetDir())
	{
		{
			if (AngleCalc(_Right_Top->GetPos(), _Left_Top->GetPos(), RParamCollideCheck) == true)
			{
				SetAnglePixel(_A_Right_Top, _A_Left_Top);
				return true;
			}
			else if (AngleCalc(_Left_Top->GetPos(), _Left_Bottom->GetPos(), LParamCollideCheck) == true)
			{
				SetAnglePixel(_A_Left_Top, _A_Left_Bottom);
				return true;
			}
			else
			{
				_angle = 0;
				return false;
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
				while (DetectCollision_ColorRef(*LeftTop, _courseColorRef) == false &&
					DetectCollision_ColorRef(*LeftTop, ColorRef::RED) ==false)
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
				while (DetectCollision_ColorRef(*RightTop, _courseColorRef) == false &&
					DetectCollision_ColorRef(*RightTop, ColorRef::RED) ==false)
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
			
			if (!SetAngle(_angle, YVal, XVal))
			{
				return false;
			}
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
				while (DetectCollision_ColorRef(*RightBottom, _courseColorRef) == false &&
					DetectCollision_ColorRef(*RightBottom, ColorRef::RED) == false)
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
				while (DetectCollision_ColorRef(*LeftBottom, _courseColorRef) == false &&
					DetectCollision_ColorRef(*LeftBottom, ColorRef::RED) == false)
				{
					bool first = DetectCollision_ColorRef(*LeftBottom, _courseColorRef) == false;
					bool second = DetectCollision_ColorRef(*LeftBottom, ColorRef::RED) == false;
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

			if (!SetAngle(_angle, YVal, XVal))
			{
				return false;
			}
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
				while (DetectCollision_ColorRef(*LeftBottom, _courseColorRef) == false &&
					DetectCollision_ColorRef(*LeftBottom, ColorRef::RED) == false)
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
				while (DetectCollision_ColorRef(*LeftTop, _courseColorRef) == false &&
					DetectCollision_ColorRef(*LeftTop, ColorRef::RED) == false)
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

			if (!SetAngle(_angle, YVal, XVal))
			{
				return false;
			}
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
				while (DetectCollision_ColorRef(*RightTop, _courseColorRef) == false &&
					DetectCollision_ColorRef(*RightTop, ColorRef::RED) == false)
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
				while (DetectCollision_ColorRef(*RightBottom, _courseColorRef) == false &&
					DetectCollision_ColorRef(*RightBottom, ColorRef::RED) == false)
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

			if (!SetAngle(_angle, YVal, XVal))
			{
				return false;
			}
			return true;
		}
	}
	return false;
}

void Player::SonicFlipBookAngleMatch(uint8 dir)
{
	float MyAngle = _angle;
	if (MyAngle < 0.f)
	{
		MyAngle += 2 * M_PI;
	}

	int StandardAngle = (MyAngle) / (M_PI / 4);


	if(dir == _left)
	{
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
	else if (dir == _right)
	{
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
}



void Player::SetAnglePixel(Vector* v1, Vector* v2)
{
	_A_Pixel[0] = v1;
	_A_Pixel[1] = v2;
}

bool Player::SetAngle(float& ref, float Yval, float Xval)
{
	if (Yval == 0.f && Xval == 0.f)
	{
		return false;
	}
	ref = atan2(Yval, Xval);

	float DegreeRef = ref * 180 / M_PI;

	if (DegreeRef > -7.f && DegreeRef < 7.f)
	{
		ref = 0.f;
	}
	else if (DegreeRef > 83 && DegreeRef < 97)
	{
		ref = M_PI / 2;
	}

	else if (DegreeRef > -93 && DegreeRef < -87)
	{
		ref = -M_PI / 2;
	}

	
	return true;
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

void Player::UpdateJumpState()
{
	if (_course!=nullptr)
	{
		if(_course->GetCourseInfo() == eCourse::PIPE)
		{
			_canJump = false;
			return;
		}
	}
	if (_IsOnGround == true)
	{
		_canJump = true;
	}
}

void Player::SkiddlingMovement()
{
	_rigidBody->LowerGroundSpeed();


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
}

bool Player::SetGravityVector(float radian)
{
	_rigidBody->SetGravityVector(radian);
	return true;
}

bool Player::SetMovement()
{
	SetPos(_pos + _physic->Speed);
	
	Player::AdjustMovement();

	Player::RenewPixelLocation();

	return true;
}

Vector& Player::GetRestDoubleCheckedPixel(uint8 currDir)
{
	Vector vector;
	return vector;
	// TODO: 여기에 return 문을 삽입합니다.
}

void Player::RenewPixelLocation()
{
	for (auto& i : _pixels)
	{
		i.second->SetPixelPos();
	}
}