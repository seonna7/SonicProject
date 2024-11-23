#pragma once
#include "FlipbookActor.h"
class Flipbook;
class Collider;
class BoxCollider;
class RigidBody;
class Texture;
class PixelCollider;
class Physic;
class LoopCollider;
class InputManager;
class Course;


using namespace ColorRef;

enum e_SlopeType 
{
	AIR			= 1,
	GROUND		= 2,
	CEILING		= 4,
	LEFT_WALL	= 8, 
	RIGHT_WALL	= 16,

	//SlopeType
	SLOPETYPE_SIZE		= 5
};



// 왼쪽 오른쪽에 대한 결정을 최상위 비트로 결정하기 어떰?
enum class SonicState
{
	NONE = 0,
	PAUSE,
	RUNLEFT_0,
	RUNLEFT_45,
	RUNLEFT_90,
	RUNLEFT_135,
	RUNLEFT_180,
	RUNLEFT_225,
	RUNLEFT_270,
	RUNLEFT_315,
	RUNRIGHT_0,
	RUNRIGHT_45,
	RUNRIGHT_90,
	RUNRIGHT_135,
	RUNRIGHT_180,
	RUNRIGHT_225,
	RUNRIGHT_270,
	RUNRIGHT_315,
	ROLLING,
	JUMPING,
	SKIDDLING_LEFT,
	SKIDDLING_RIGHT,
	SITTING,
	RUNLEFT_90ANGLE,
	RUNRIGHT_90ANGLE,

};

class Player : public FlipbookActor
{
	using Super = FlipbookActor;
public : 
	Player();
	virtual ~Player()						override;

	virtual void BeginPlay()				override;
	virtual void Tick()						override;
	virtual void Render(HDC hdc)			override;
	void FinalRender(HDC hdc);
	void FlipbookRender();

	//=======================================================
	//					Collision OverLap
	//=======================================================
	virtual void	OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void			OnComponentBeginOverlap_Ground_Pixel(Collider* collider);

	virtual void	OnComponentEndOverlap(Collider* collider, Collider* other) override;

public : 
	//=======================================================
	//					Collision Detect 
	//=======================================================
	void AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2);
	
	// 얘는 y좌표땜에 냄겨두기 
	bool CheckCollision(uint8 dir);

	bool DetectCollision_ColorRef(Vector& pos, COLORREF color);
private : 
	//=======================================================
	//						Movement 
	//=======================================================

public : 
	bool Gravity = true;

	bool Skiddle = true;

	void OnUpPressed();
	void OnLeftPressed();
	void OnRightPressed();
	void OnDownPressed();

private : 
	bool AdjustMovement();
	
	void JumpMovement();
	void LeftMovement();
	void RightMovement();

	bool SetMovement();

	bool IsSkiddlingCondition();
	void SkiddlingMovement();


	void SetGravitationVec(e_SlopeType vec);
private : 
	uint8 _ctrlLockTimer = 0;


private : 
	//=======================================================
	//					  Angle Setting
	//=======================================================
	float	_angle = 0.f;

	void AngleFunction();
	bool AngleCalc(Vector pos1, Vector pos2, bool CollideFlag);
	void SonicFlipBookAngleMatch(uint8 dir);
	Vector* _A_Left_Top		= nullptr;
	Vector* _A_Right_Top	= nullptr;
	Vector* _A_Left_Bottom	= nullptr;
	Vector* _A_Right_Bottom = nullptr;

	void SetAnglePixel(Vector *v1, Vector *v2);
	Vector* _A_Pixel[2]		= { nullptr,nullptr };
public : 
	float GetAngle() { return _angle; }

	bool GetIsOnGround() { return _IsOnGround; }

	bool SetAngle(float &ref, float Yval, float Xval);

private : 
	//=======================================================
	//					  Player State
	//=======================================================
	SonicState		_state		= SonicState::NONE; 
	e_SlopeType		_slopeType = e_SlopeType::AIR;

	bool			_pixelDoubleChecked	= false;
	uint8			_currCheckedPixel	= 0; 

	void			SetSonicState(SonicState state) { _state = state; }
	void			SetSonicStateOnAir();
	void			SetSonicStateSitting();
	void			UpdateJumpState();


	bool	_IsOnGround			= false;
	bool	_canJump			= false;

private : 
	//=======================================================
	//					  FlipBook Info
	//=======================================================
	Flipbook* _flipbook_Pause					= nullptr;

	Flipbook* _flipbookSkiddling_Left			= nullptr;
	Flipbook* _flipbookSkiddling_Right			= nullptr;

	Flipbook* _flipbook_RunningLeft_0				= nullptr;
	Flipbook* _flipbook_RunningLeft_45				= nullptr;
	Flipbook* _flipbook_RunningLeft_90				= nullptr;
	Flipbook* _flipbook_RunningLeft_135				= nullptr;
	Flipbook* _flipbook_RunningLeft_180				= nullptr;
	Flipbook* _flipbook_RunningLeft_225				= nullptr;
	Flipbook* _flipbook_RunningLeft_270				= nullptr;
	Flipbook* _flipbook_RunningLeft_315				= nullptr;

	Flipbook* _flipbook_RunningRight_0				= nullptr;
	Flipbook* _flipbook_RunningRight_45				= nullptr;
	Flipbook* _flipbook_RunningRight_90				= nullptr;
	Flipbook* _flipbook_RunningRight_135			= nullptr;
	Flipbook* _flipbook_RunningRight_180			= nullptr;
	Flipbook* _flipbook_RunningRight_225			= nullptr;
	Flipbook* _flipbook_RunningRight_270			= nullptr;
	Flipbook* _flipbook_RunningRight_315			= nullptr;

	Flipbook* _flipbook_Rolling					= nullptr;
	Flipbook* _flipbook_Sitting					= nullptr;

public : 
	//=======================================================
	//				  Player Setting (외부 접근)
	//=======================================================

	void		SetBackGround(Texture* background) { _background = background; }
	Texture*	GetBackGround() { return _background; }

	void		SetRigidBody(RigidBody* rigidbody) { _rigidBody = rigidbody; }
	RigidBody*	GetRigidBody() { return _rigidBody; }
	


	RigidBody*	_rigidBody		= nullptr;
	Physic*		_physic			= nullptr;
	Texture*	_background		= nullptr;

public :	
	Vector&		GetRestDoubleCheckedPixel(uint8 currDir);


private : 
	//=======================================================
	//						Pixel
	//=======================================================

	unordered_map<uint8, PixelCollider*> _pixels;

	void			RenewPixelLocation();

	uint8 _left		= static_cast<uint8>(ePixelDirection::P_LEFT);
	uint8 _right	= static_cast<uint8>(ePixelDirection::P_RIGHT);
	uint8 _bottom	= static_cast<uint8>(ePixelDirection::P_BOTTOM);
	uint8 _top		= static_cast<uint8>(ePixelDirection::P_TOP);
	//GroundCheck
	PixelCollider*	_Right_Bottom		= nullptr;
	PixelCollider*	_Left_Bottom		= nullptr;

	//WallCheck 
	PixelCollider* _Left_Top			= nullptr;
	PixelCollider* _Right_Top			= nullptr;

	uint8	_pixelDist = 0;

private :
	void GetAccBuff(Vector dir);


public : 
	//=======================================================
	//						Course
	//=======================================================
	bool IsCourseContacted();
	bool CourseMeetingFunction();

	bool _courseMovementFlag	= false; // 파이프 코스 이동 조정

	bool _isCourseMovementAdjustNeeded= false;
	
	Course* _course				= nullptr;

	COLORREF _courseColorRef	= ColorRef::RED;
};
