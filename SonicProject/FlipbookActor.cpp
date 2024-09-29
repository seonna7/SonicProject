#include "pch.h"
#include "FlipbookActor.h"
#include "Flipbook.h"
#include "Sprite.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Texture.h"

extern uint32 GWinSizeX;

FlipbookActor::FlipbookActor()
{
}

FlipbookActor::~FlipbookActor()
{
}

void FlipbookActor::BeginPlay()
{
	Super::BeginPlay();
}

void FlipbookActor::Tick()
{
	Super::Tick();
	if (_flipbook == nullptr)
		return;

	const FlipbookInfo& info = _flipbook->GetInfo();
	if (info.loop == false && _idx == info.end)
		return;

	float deltaTime = GET_SINGLE(TimeManager)->Get_deltaTime();

	_sumTime += deltaTime;
	 
	int32 frameCnt = (info.end - info.start + 1);
	float delta = info.duration / frameCnt;

	if (_sumTime >= delta)
	{
		_sumTime = 0.f;
		_idx = (_idx + 1) % frameCnt;
	}
}

void FlipbookActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_flipbook == nullptr)
		return;


	Vector cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
	const FlipbookInfo& info = _flipbook->GetInfo();

	::TransparentBlt(
		hdc,
		(int32)_pos.x - info.size.x / 2 - ((int32)cameraPos.x) + GWinSizeX / 2,
		(int32)_pos.y - info.size.y / 2 - ((int32)cameraPos.y) + GWinSizeY / 2,
		info.size.x,
		info.size.y,
		info.texture->GetDC(),
		(info.start + _idx) * info.size.x,
		info.line * info.size.y,
		info.size.x,
		info.size.y,
		info.texture->GetTransparent()
	);
}

void FlipbookActor::setFlipbook(Flipbook* fb)
{
	if (fb && _flipbook == fb)
		return;
	_flipbook = fb; 
	Reset();
}

void FlipbookActor::Reset()
{
	_sumTime = 0.f;
	_idx = _flipbook->GetInfo().start;
}
