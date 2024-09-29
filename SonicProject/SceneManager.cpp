#include "pch.h"
#include "SceneManager.h"
#include "DevScene.h"
#include "GameScene.h"
#include "EditScene.h"
void SceneManager::Init()
{
}

void SceneManager::Update()
{
	if (_scene)
		_scene->Update();
}

void SceneManager::Render(HDC hdc)
{
	if (_scene)
		_scene->Render(hdc);
}

void SceneManager::Clear()
{
	SAFE_DELETE(_scene,"SceneManager::Clear() :: _scene 삭제 오류 ");
}

void SceneManager::ChangeScene(eSceneType scenetype)
{
	if (scenetype == _sceneType)
		return;

	Scene* newScene = nullptr;

	switch (scenetype)
	{
	case(eSceneType::DEVSCENE) : 
		newScene = new DevScene();
		break;
	case(eSceneType::GAMESCENE) :
		newScene = new GameScene();
		break;
	case(eSceneType::EDITSCENE):
		newScene = new EditScene();
		break;

	}
	if (_scene)
	{
		delete _scene;
		_scene = nullptr;
	}
	_scene = newScene;
	_sceneType = scenetype;

	newScene->Init();
}


