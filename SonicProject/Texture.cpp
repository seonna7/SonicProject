#include "pch.h"
#include "Texture.h"

Texture::Texture()
{
}

Texture::~Texture()
{
}



Texture* Texture::LoadBitMap(HWND hwnd, const wstring& path)
{
	HDC hdc = ::GetDC(hwnd);

	_hdc = ::CreateCompatibleDC(hdc);
	_bitmap = (HBITMAP)LoadImage(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	
	if (_bitmap == NULL)
		::MessageBox(hwnd, path.c_str(), L"Image Load Failed", NULL);

	HBITMAP prev = (HBITMAP)SelectObject(_hdc, _bitmap);
	DeleteObject(prev);

	BITMAP bit = {};
	::GetObject(_bitmap, sizeof(BITMAP), &bit);

	_size.x = bit.bmWidth;
	_size.y = bit.bmHeight;

	return this;	
}


Texture* Texture::LoadBitMapLotated(HWND hwnd, const wstring& path, float angle)
{
    HDC hdc = ::GetDC(hwnd);

    // 원본 비트맵을 로드
    _hdc = ::CreateCompatibleDC(hdc);
    _bitmap = (HBITMAP)LoadImage(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

    if (_bitmap == NULL) {
        ::MessageBox(hwnd, path.c_str(), L"Image Load Failed", NULL);
        return nullptr;
    }

    // 비트맵 정보 가져오기
    BITMAP bit = {};
    ::GetObject(_bitmap, sizeof(BITMAP), &bit);

    // 원본 비트맵 크기 저장
    _size.x = bit.bmWidth;
    _size.y = bit.bmHeight;

    // 회전 각도 설정 (라디안으로 변환)
    float radians = angle * (3.14159265359f / 180.0f);
    float cosAngle = std::cos(radians);
    float sinAngle = std::sin(radians);

    // 회전된 비트맵의 크기 계산
    int newWidth = static_cast<int>(std::abs(_size.x * cosAngle) + std::abs(_size.y * sinAngle));
    int newHeight = static_cast<int>(std::abs(_size.x * sinAngle) + std::abs(_size.y * cosAngle));

    // 회전된 이미지를 위한 메모리 DC와 비트맵 생성
    HDC hdcRotated = ::CreateCompatibleDC(hdc);
    HBITMAP rotatedBitmap = ::CreateCompatibleBitmap(hdc, newWidth, newHeight);
    HBITMAP oldRotatedBitmap = (HBITMAP)::SelectObject(hdcRotated, rotatedBitmap);

    // 원점 기준으로 회전할 수 있도록 변환 설정
    XFORM xForm;
    xForm.eM11 = cosAngle;
    xForm.eM12 = sinAngle;
    xForm.eM21 = -sinAngle;
    xForm.eM22 = cosAngle;
    xForm.eDx = (FLOAT)newWidth / 2.0f;
    xForm.eDy = (FLOAT)newHeight / 2.0f;

    // 그래픽 모드 설정 및 변환 적용
    ::SetGraphicsMode(hdcRotated, GM_ADVANCED);
    ::SetWorldTransform(hdcRotated, &xForm);

    // 원본 비트맵을 회전된 비트맵으로 복사
    HBITMAP oldBitmap = (HBITMAP)::SelectObject(_hdc, _bitmap);
    ::BitBlt(hdcRotated, -(int)(_size.x / 2), -(int)(_size.y / 2), _size.x, _size.y, _hdc, 0, 0, SRCCOPY);

    // 회전된 비트맵을 _bitmap에 저장
    ::SelectObject(_hdc, oldBitmap);
    ::DeleteObject(_bitmap);  // 기존 비트맵 삭제
    _bitmap = rotatedBitmap;  // 회전된 비트맵을 _bitmap에 할당

    // DC 정리
    ::SelectObject(hdcRotated, oldRotatedBitmap);
    ::DeleteDC(hdcRotated);
    ::ReleaseDC(hwnd, hdc);

    // 회전된 크기를 _size에 반영
    _size.x = newWidth;
    _size.y = newHeight;

    return this;
}


HDC Texture::GetDC()
{
 	return _hdc;
}

COLORREF Texture::GetPixel(int x, int y)
{
	return ::GetPixel(GetDC(), x, y);
}