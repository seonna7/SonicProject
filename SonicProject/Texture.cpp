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

    // ���� ��Ʈ���� �ε�
    _hdc = ::CreateCompatibleDC(hdc);
    _bitmap = (HBITMAP)LoadImage(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

    if (_bitmap == NULL) {
        ::MessageBox(hwnd, path.c_str(), L"Image Load Failed", NULL);
        return nullptr;
    }

    // ��Ʈ�� ���� ��������
    BITMAP bit = {};
    ::GetObject(_bitmap, sizeof(BITMAP), &bit);

    // ���� ��Ʈ�� ũ�� ����
    _size.x = bit.bmWidth;
    _size.y = bit.bmHeight;

    // ȸ�� ���� ���� (�������� ��ȯ)
    float radians = angle * (3.14159265359f / 180.0f);
    float cosAngle = std::cos(radians);
    float sinAngle = std::sin(radians);

    // ȸ���� ��Ʈ���� ũ�� ���
    int newWidth = static_cast<int>(std::abs(_size.x * cosAngle) + std::abs(_size.y * sinAngle));
    int newHeight = static_cast<int>(std::abs(_size.x * sinAngle) + std::abs(_size.y * cosAngle));

    // ȸ���� �̹����� ���� �޸� DC�� ��Ʈ�� ����
    HDC hdcRotated = ::CreateCompatibleDC(hdc);
    HBITMAP rotatedBitmap = ::CreateCompatibleBitmap(hdc, newWidth, newHeight);
    HBITMAP oldRotatedBitmap = (HBITMAP)::SelectObject(hdcRotated, rotatedBitmap);

    // ���� �������� ȸ���� �� �ֵ��� ��ȯ ����
    XFORM xForm;
    xForm.eM11 = cosAngle;
    xForm.eM12 = sinAngle;
    xForm.eM21 = -sinAngle;
    xForm.eM22 = cosAngle;
    xForm.eDx = (FLOAT)newWidth / 2.0f;
    xForm.eDy = (FLOAT)newHeight / 2.0f;

    // �׷��� ��� ���� �� ��ȯ ����
    ::SetGraphicsMode(hdcRotated, GM_ADVANCED);
    ::SetWorldTransform(hdcRotated, &xForm);

    // ���� ��Ʈ���� ȸ���� ��Ʈ������ ����
    HBITMAP oldBitmap = (HBITMAP)::SelectObject(_hdc, _bitmap);
    ::BitBlt(hdcRotated, -(int)(_size.x / 2), -(int)(_size.y / 2), _size.x, _size.y, _hdc, 0, 0, SRCCOPY);

    // ȸ���� ��Ʈ���� _bitmap�� ����
    ::SelectObject(_hdc, oldBitmap);
    ::DeleteObject(_bitmap);  // ���� ��Ʈ�� ����
    _bitmap = rotatedBitmap;  // ȸ���� ��Ʈ���� _bitmap�� �Ҵ�

    // DC ����
    ::SelectObject(hdcRotated, oldRotatedBitmap);
    ::DeleteDC(hdcRotated);
    ::ReleaseDC(hwnd, hdc);

    // ȸ���� ũ�⸦ _size�� �ݿ�
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