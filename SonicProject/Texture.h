#pragma once
#include "ResourceBase.h"
class Texture : public ResourceBase
{
public : 
	Texture();
	virtual ~Texture(); 

	Texture*	LoadBitMap(HWND hwnd, const wstring& path);

	Texture*	LoadBitMapLotated(HWND hwnd, const wstring& path, float angle);

	HDC			GetDC();

	void		SetSize(Vector vec)				{ _size = vec; }

	Vector		GetSize()						{ return _size; }

	void		SetTransparent(uint32 value)	{ _transparent = value; }
	uint32		GetTransparent()				{ return _transparent; }

	COLORREF GetPixel(int x, int y);
private  :
	HDC			_hdc			= {};
	HBITMAP		_bitmap			= {};
	Vector		_size			= {};
	uint32		_transparent	= RGB(255, 0, 255);
};

