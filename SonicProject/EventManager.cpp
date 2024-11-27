#include "pch.h"
#include "EventManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Player.h"

void EventManager::Init()
{
	EventManager::SetCallBacks(eSceneType::DEVSCENE);
}

void EventManager::Update()
{
	_SceneType = GET_SINGLE(SceneManager)->GetSceneType();

	EventManager::SetCallBacks(_SceneType);

	InputEventFunctionExecution();
}

void EventManager::Clear()
{
	RemoveEvents();

	if(_EventActor!=nullptr)
		SAFE_DELETE(_EventActor, "sex");

}

void EventManager::RegisterKeyCallback(const wstring& key, std::function<void()> callback)
{
	Event* event = new Event(key, callback);
	_eventQueue.push(event);
}

void EventManager::InputEventFunctionExecution()
{
	while (!_eventQueue.empty())
	{
		Event* event = _eventQueue.front();
		event->_eventFunc();
		_eventQueue.pop();
	}
}

void EventManager::DevSceneFunc()
{
	if (_EventActor == nullptr)
		return;

	Player* player = dynamic_cast<Player*>(_EventActor);
	
	assert(player != nullptr);

	// W Ű �ݹ� ��� (����)

	//RegisterKeyCallback(L"KeyType::W_Pressed", std::bind(&Player::OnUpPressed, player));
	//
	//// A Ű �ݹ� ��� (���� �̵�)
	//RegisterKeyCallback(L"KeyType::S_Pressed", std::bind(&Player::OnDownPressed, player));
	//
	//// D Ű �ݹ� ��� (������ �̵�)
	//RegisterKeyCallback(L"KeyType::A_Pressed", std::bind(&Player::OnLeftPressed, player));
	//
	//// S Ű �ݹ� ��� (�ɱ�)
	//RegisterKeyCallback(L"KeyType::D_Pressed", std::bind(&Player::OnRightPressed, player));
}

void EventManager::SetCallBacks(eSceneType type)
{
	EventManager::RemoveEvents();

	switch (type)
	{
	case eSceneType::NONE:
		break;
	case eSceneType::DEVSCENE:
		DevSceneFunc();
		break;
	case eSceneType::GAMESCENE:
		break;
	}
}

void EventManager::RemoveEvents()
{
	while (!_eventQueue.empty())
	{
		_eventQueue.pop();
	}

}
