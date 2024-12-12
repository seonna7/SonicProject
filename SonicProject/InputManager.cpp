#include "pch.h"
#include "InputManager.h"

void InputManager::Init(HWND hwnd)
{
	_Hwnd = hwnd;
	_States.resize(KEY_TYPE_COUNT, KeyState::None);
}

void InputManager::Update()
{
	BYTE asciiKeys[KEY_TYPE_COUNT] = {};
	if (::GetKeyboardState(asciiKeys) == false)
		return;

	for (uint32 key = 0; key < KEY_TYPE_COUNT; key++)
	{
		KeyState& state = _States[key];
		// Ű �Է°��� �����ϴ� ��� 
		if (asciiKeys[key] & 0X80)
		{
			// ��� �����ų�, �̹� ������ �ִ� ��� 
			if (state == KeyState::Press || state == KeyState::Down)
				state = KeyState::Press;
			else
				state = KeyState::Down;
		}
		// Ű�� �ôٰų� ���ʿ� Ű�Է��� ���� �ʾҴ� ��� 
		else
		{
			if (state == KeyState::Press || state == KeyState::Down)
				state = KeyState::UP;
			else
				state = KeyState::None;
		}
	}

	// ���콺
	::GetCursorPos(&_MousePos);
	::ScreenToClient(_Hwnd, &_MousePos);
}
