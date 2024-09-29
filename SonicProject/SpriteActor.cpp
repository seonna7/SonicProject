#include "pch.h"
#include "SpriteActor.h"
#include "Sprite.h"
#include "SceneManager.h"
#include "Texture.h"


SpriteActor::SpriteActor()
{
}

SpriteActor::~SpriteActor()
{
}

void SpriteActor::BeginPlay()
{
	Super::BeginPlay();
}

void SpriteActor::Tick()
{
	Super::Tick();
}

void SpriteActor::Render(HDC hdc)
{
	Super::Render(hdc);
	if (_sprite == nullptr)
		return;

	Vector size = _sprite->GetSize();

	Vector cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	//BLENDFUNCTION bf = {};
	//bf.BlendOp = AC_SRC_OVER;
	//bf.BlendFlags = 0;
	//bf.AlphaFormat = AC_SRC_ALPHA;
	//bf.SourceConstantAlpha = 0;
	//
	//bool res = GdiAlphaBlend(hdc,
	//	((int32)_pos.x - size.x / 2 - ((int32)cameraPos.x) + GWinSizeX / 2),
	//	((int32)_pos.y - size.y / 2 - ((int32)cameraPos.y) + GWinSizeY / 2),
	//	size.x*2,
	//	size.y*2,
	//	_sprite->GetDC(),
	//	_sprite->GetPos().x,
	//	_sprite->GetPos().y,
	//	_sprite->GetSize().x,
	//	_sprite->GetSize().y,
	//	bf);


#pragma region 고속복사 형태 
	
	StretchBlt(hdc,
		((int32)_pos.x - size.x / 2 - ((int32)cameraPos.x) + GWinSizeX / 2),
		((int32)_pos.y - size.y / 2 - ((int32)cameraPos.y) + GWinSizeY / 2),
		size.x,
		size.y,
		_sprite->GetDC(),
		_sprite->GetPos().x,
		_sprite->GetPos().y,
		_sprite->GetSize().x,
		_sprite->GetSize().y,
		SRCCOPY);
	//else
	//	TransparentBlt(hdc,
	//		((int32)_pos.x - size.x / 2 - ((int32)cameraPos.x) + GWinSizeX / 2),
	//		((int32)_pos.y - size.y / 2 - ((int32)cameraPos.y) + GWinSizeY / 2),
	//		size.x * 2,
	//		size.y * 2,
	//		_sprite->GetDC(),
	//		_sprite->GetPos().x,
	//		_sprite->GetPos().y,
	//		_sprite->GetSize().x,
	//		_sprite->GetSize().y,
	//		_sprite->GetTransparent());

}
