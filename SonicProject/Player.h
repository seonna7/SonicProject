#pragma once
#include "FlipbookActor.h"
class Flipbook;
class Collider;
class BoxCollider;
class RigidBody;
class Texture;
class CeilingPixelCollider;
class GroundPixelCollider;
class PushPixelCollider;
class WallPixelCollider;
class CliffPixelCollider;
class Physic;
class LoopCollider;
class InputManager;


using namespace ColorRef;
enum GravitationVec 
{
	AIR			= 1,
	GROUND		= 2,
	CEILING		= 4,
	LEFT_WALL	= 8, 
	RIGHT_WALL	= 16,

	//SlopeType
	SLOPETYPE_SIZE		= 5
};
using SlopeType = GravitationVec;

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
	void CheckCollision_Ground();

	bool CheckCollsion_ColorRef(Vector& pos, COLORREF color);
private : 
	//=======================================================
	//						Movement 
	//=======================================================

public : 

	void OnUpPressed();
	void OnLeftPressed();
	void OnRightPressed();
	void OnDownPressed();

private : 
	void AdjustGroundMovement();
	void ModifyWallMovement(ePixelDirection _dir);
	
	void SlipMovement();
	void JumpMovement();
	void LeftMovement();
	void RightMovement();

	void SetMovement();

	bool IsSkiddlingCondition();
	void SkiddlingMovement();

	void SlideSlopeMovement();

	void SetGravitationVec(GravitationVec vec);
private : 
	uint8 _ctrlLockTimer = 0;


private : 
	//=======================================================
	//					  Angle Setting
	//=======================================================
	Vector* _anglePixel[2] = { nullptr, nullptr };
	float	_angle = 0.f;

	void SetAngle(uint16 type);
	void AdjustState_Angle_LEFT();
	void AdjustState_Angle_RIGHT();
	SlopeType InitAnglePixel();

public : 
	float GetAngle() { return _angle; }

	bool GetIsOnGround() { return _IsOnGround; }

private : 
	//=======================================================
	//					  Player State
	//=======================================================
	SonicState		_state		= SonicState::NONE; 
	uint16			_slopeType	= 0;

	void			SetSonicState(SonicState state) { _state = state; }
	void			SetSonicStateOnAir();
	void			SetSonicStateSitting();
	void			JumpStateUpdate();


	bool	_IsOnGround			= false;
	bool	_IsOnRWall			= false;
	bool	_IsOnLWall			= false;
	bool	_IsOnCeiling		= false;
	bool	_IsJumped			= false;

	void	SetPlayerStateOnAir();
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
	
	void		SetLoopInfo(vector<LoopCollider*> loopInfo) { _loopInfo = loopInfo; }


	RigidBody*	_rigidBody		= nullptr;
	Physic*		_physic			= nullptr;
	Texture*	_background		= nullptr;

public :	
	//=======================================================
	//					  PixelCollider
	//=======================================================
	void SetCeilingPixelCollider(CeilingPixelCollider* collider) { _ceilingPixelCollider = collider; }
	CeilingPixelCollider* GetCeilingPixelCollider() { return _ceilingPixelCollider; }

	void SetGroundPixelCollider(GroundPixelCollider* collider) { _groundPixelCollider = collider; }
	GroundPixelCollider* GetGroundPixelCollider() { return _groundPixelCollider; }

	void SetPushPixelCollider(PushPixelCollider* collider) { _pushPixelCollider = collider; }
	PushPixelCollider* GetPushPixelCollider() { return _pushPixelCollider; }

	void SetRWallPixelCollider(WallPixelCollider* collider) { _RwallPixelCollider = collider; }
	WallPixelCollider* GetRWallPixelCollider() { return _RwallPixelCollider; }

	void SetLWallPixelCollider(WallPixelCollider* collider) { _LwallPixelCollider = collider; }
	WallPixelCollider* GetLWallPixelCollider() { return _LwallPixelCollider; }


	void SetCliffPixelCollider(CliffPixelCollider* collider) { _cliffPixelCollider = collider; }
	CliffPixelCollider* GetCliffPixelCollider() { return _cliffPixelCollider; }

private : 
	CeilingPixelCollider*	_ceilingPixelCollider	= nullptr;
	GroundPixelCollider*	_groundPixelCollider	= nullptr;
	PushPixelCollider*		_pushPixelCollider		= nullptr;
	WallPixelCollider*		_RwallPixelCollider		= nullptr;
	WallPixelCollider*		_LwallPixelCollider		= nullptr;
	CliffPixelCollider*		_cliffPixelCollider		= nullptr;

private  :	
	//=======================================================
	//					  LOOP Setting 
	//=======================================================

	vector<LoopCollider*> _loopInfo;

	LoopCollider*	_currLoop = nullptr;
	Vector			_currLoopPos;
	void MovementCallBack
	   (bool(Player::* LoopFunc)(ePixelDirection),
		ePixelDirection _dir,
		void(Player::* SucceedFunc)(ePixelDirection),
		void(Player::* FailedFunc)());

	bool IsMeetingLoopPassCondition(ePixelDirection _dir);
	void LoopMovement(ePixelDirection _dir);

	bool IsLoopFailed();

	void SetAngleSpeed();
	bool IsOnLoopCircle();
	void LoopFailedProcess();

	bool	_onLoopCondition = false;
	float	_radius = 147.f;
	bool	_onLoopJumped = false; 

	float _angleSpeed = 0.f; 
	
	MyDegree				_onLoopPlayerAngle = MyDegree(0);

	//=======================================================
	//					  LOOP Setting 
	//=======================================================
private :
		 
	void GetAccBuff(Vector dir);
};
