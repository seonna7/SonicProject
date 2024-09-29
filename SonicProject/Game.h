#pragma once
class Game
{
public :
	Game();
	~Game();
public  :
	void	Init(HWND hwnd);
	void	Update();
	void	Render();
private :
	HWND	_Hwnd	= {};
	HDC		_Hdc	= {};

private :
	//window Ã¢ Å©±â 
	//RECT _winRect;


	RECT _rect;
	HDC _HdcBack = {};
	HBITMAP _BmpBack = {};
};

