#include "pch.h"
#include "Game.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "EventManager.h"

Game::Game()
{

}
Game::~Game()
{
	GET_SINGLE(SceneManager)->Clear();
	_CrtDumpMemoryLeaks();
	GET_SINGLE(ResourceManager)->Clear();
	GET_SINGLE(EventManager)->Clear();
}

void Game::Init(HWND hwnd)
{
	_Hwnd = hwnd;
	_Hdc = ::GetDC(hwnd);

	::GetClientRect(_Hwnd, &_rect);



	//Hdc와 호환되는 DC를 생성
	_HdcBack = ::CreateCompatibleDC(_Hdc);

	//Hdc와 호환되는 비트맵 생성 
	_BmpBack = ::CreateCompatibleBitmap(_Hdc, _rect.right, _rect.bottom);

	//DC와 BMP 연결 
	HBITMAP prev = (HBITMAP)::SelectObject(_HdcBack, _BmpBack);
	::DeleteObject(prev);

	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(InputManager)->Init(_Hwnd);
	GET_SINGLE(SceneManager)->Init();
	GET_SINGLE(ResourceManager)->Init(_Hwnd, fs::path(L"C:\\Workspace\\SonicProject\\SonicProject\\Resources"));

	GET_SINGLE(SceneManager)->ChangeScene(eSceneType::DEVSCENE);
	GET_SINGLE(EventManager)->Init();

}

void Game::Update()
{
	GET_SINGLE(TimeManager)->Update();
	GET_SINGLE(InputManager)->Update();
	GET_SINGLE(SceneManager)->Update();
	GET_SINGLE(EventManager)->Update();
	
}

void Game::Render()
{
	//::Rectangle(_Hdc, 200, 100, 300, 400);

	uint32 fps = GET_SINGLE(TimeManager)->Get_FPS();
	float deltaTime = GET_SINGLE(TimeManager)->Get_deltaTime();
	
	GET_SINGLE(SceneManager)->Render(_HdcBack);

	//마우스 표시
	{
		POINT MousePos = GET_SINGLE(InputManager)->GetMousePos();
		wstring str = std::format(L"MOUSE({0}, {1})", MousePos.x, MousePos.y);
		::TextOut(_HdcBack, 10, 10, str.c_str(), static_cast<int32>(str.size()));
	}
	
	// 프레임 표시
	{
		wstring str = std::format(L"FPS({0}), DT({1} ms)", fps, static_cast<int32>(deltaTime * 1000));
		::TextOut(_HdcBack, 10, 40, str.c_str(), static_cast<int32>(str.size()));
	}
		

	// 고속 복사 
	::BitBlt(_Hdc, 0, 0, _rect.right, _rect.bottom, _HdcBack, 0, 0, SRCCOPY); 
	::PatBlt(_HdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}