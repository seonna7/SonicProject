#include "pch.h"
#include "EditScene.h"
#include "InputManager.h"
#include "Utils.h"
#include "LineMesh.h"
#include "ResourceManager.h"
#include "Actor.h"
#include "SpriteActor.h"
#include "Sprite.h"
#include <fstream>
EditScene::EditScene()
{
}
EditScene::~EditScene()
{
}
void EditScene::Init()
{
}

void EditScene::Update()
{
	if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::LEFT))
	{
		for (Actor* actor : _backgrounds)
			actor->SetPos(actor->GetPos() + Vector(-1, 0));
	}
	if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::RIGHT))
	{
		for (Actor* actor : _backgrounds)
			actor->SetPos(actor->GetPos() + Vector(1, 0));
	}
	if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::UP))
	{
		for (Actor* actor : _backgrounds)
			actor->SetPos(actor->GetPos() + Vector(0, -1));
	}
	if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::DOWN))
	{
		for (Actor* actor : _backgrounds)
			actor->SetPos(actor->GetPos() + Vector(0, +1));
	}

	for (Actor* actor : _backgrounds)
		actor->Tick();
	for (Actor* actor : _actors)
		actor->Tick();
}

void EditScene::Render(HDC hdc)
{
	Vector mousePos = GET_SINGLE(InputManager)->GetMousePos();
	for (Actor* actor : _backgrounds)
		actor->Render(hdc);
	for (Actor* actor : _actors)
		actor->Render(hdc);
}

bool EditScene::RenderOnBackground(const wstring& key)
{
	Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(key);
	GET_SINGLE(ResourceManager)->CreateSprite(key, tex, 0, 0, 0, 0);
	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(key);
		SpriteActor* background = new SpriteActor();

		const Vector size = sprite->GetSize();

		// 포지션 변경 
		background->SetPos(Vector(size.x / 2, size.y / 2));

		background->SetSprite(sprite);

		_backgrounds.push_back(background);
	}
	return false;
}
