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
		// 키 입력값이 존재하는 경우 
		if (asciiKeys[key] & 0X80)
		{
			// 방금 눌렀거나, 이미 누르고 있는 경우 
			if (state == KeyState::Press || state == KeyState::Down)
				state = KeyState::Press;
			else
				state = KeyState::Down;
		}
		// 키를 뗐다거나 애초에 키입력을 하지 않았던 경우 
		else
		{
			if (state == KeyState::Press || state == KeyState::Down)
				state = KeyState::UP;
			else
				state = KeyState::None;
		}
	}

	// 마우스
	::GetCursorPos(&_MousePos);
	::ScreenToClient(_Hwnd, &_MousePos);
}
