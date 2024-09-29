#pragma once

class InputManger;
class Actor;

struct Event
{ 
	Event(wstring name, std::function<void()>func)  :
		_name(name),
		_eventFunc(func)	{}

	wstring _name;
	std::function<void()> _eventFunc;
	// 추가할게 있을 까 
};


class EventManager
{
	CREATE_SINGLE(EventManager);
public  :
	void Init();
	void Update();
	void Clear();

public:
	void RegisterKeyCallback(const wstring& key, std::function<void()> callback);
	void InputEventFunctionExecution();

	void SetCallBacks(eSceneType type);

	void RemoveEvents();

	void SetEventActor(Actor* actor) { _EventActor = actor; }

	void DevSceneFunc();

private :
	eSceneType _SceneType;
	std::queue<Event*> _eventQueue;
	Actor* _EventActor = nullptr;
};

