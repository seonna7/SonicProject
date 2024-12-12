#pragma once
class Player;


enum
{
	KEY_TYPE_COUNT = static_cast<int32>(UINT8_MAX) + 1,
	KEY_STATE_COUNT = static_cast<int32>(KeyState::End)
};
class InputManager
{
	CREATE_SINGLE(InputManager);

public : 
	void Init(HWND hwnd);
	void Update();

public : 
	//������ ���� ��
	bool GetButtonPress(KeyType type) { return GetState(type) == KeyState::Press; }

	//�� ó�� ������ ��
	bool GetButtonDown(KeyType type) { return GetState(type) == KeyState::Down; }
	//��ư�� ���� �� 
	bool GetButtonUp(KeyType type) { return GetState(type) == KeyState::UP; }

	bool GetButtonNone(KeyType type) { return GetState(type) == KeyState::None; }

	POINT GetMousePos() { return _MousePos; }


private : 
	KeyState GetState(KeyType key) { return _States[static_cast<uint8>(key)]; }

private : 


	HWND _Hwnd;
	vector<KeyState> _States;
	POINT _MousePos;
};

