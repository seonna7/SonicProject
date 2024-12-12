    // SonicProject.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "SonicProject.h"
#include "Game.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Utils.h"
#include "SceneManager.h"
#define MAX_LOADSTRING 100

// 전역 변수:Utils
HINSTANCE hInst;                              
WCHAR szTitle[MAX_LOADSTRING];                
WCHAR szWindowClass[MAX_LOADSTRING];          
HWND _Ghwnd;


uint32 GWinSizeX = 860;
uint32 GWinSizeY = 640;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SONICPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SONICPROJECT));

    MSG msg = {};
    uint64 prevTick = 0;
    Game game;
    game.Init(_Ghwnd);

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, 0, 0, NULL, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            uint64 now = GetTickCount64();
            if (now - prevTick >= 10)
            {
                game.Update();
                game.Render();
                prevTick = now;
            }
        }
    }
    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SONICPROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SONICPROJECT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; 

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   _Ghwnd = hWnd;

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case OPEN_FILE : 
                OPENFILENAME OFN;
                TCHAR filePathName[400] = L"";
                TCHAR lpstrFile[400] = L"";
                static TCHAR filter[] = L"모든 파일\0*.*\0텍스트 파일\0*.txt\0fbx 파일\0*.fbx";

                memset(&OFN, 0, sizeof(OPENFILENAME));
                OFN.lStructSize = sizeof(OPENFILENAME);
                OFN.hwndOwner = hWnd;
                OFN.lpstrFilter = filter;
                OFN.lpstrFile = lpstrFile;
                OFN.nMaxFile = 100;
                OFN.lpstrInitialDir = L".";

                if (GetOpenFileName(&OFN) != 0) {
                    // 안전한 문자열 복사 함수 wcscpy_s 사용
                    wcscpy_s(filePathName, MAX_PATH, OFN.lpstrFile);

                    // MessageBox에 파일 경로만 표시
                    MessageBox(hWnd, filePathName, L"열기 선택", MB_OK);

                    // Utils를 사용해 파일 경로를 std::string으로 변환
                    std::string t = Utils::ToString(OFN.lpstrFile);

                    // ResourceManager와 SceneManager에 파일 경로 전달
                    GET_SINGLE(ResourceManager)->LoadTexture_Sprite(filePathName);
                    GET_SINGLE(SceneManager)->AddBackGround(filePathName);
                }
                break;
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
