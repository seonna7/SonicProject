#include "pch.h"
#include "Monster.h"
#include "Utils.h"
#include "InputManager.h"
Monster::Monster(): Object(ObjectType::MONSTER)
{
}

Monster::~Monster()
{
}

void Monster::Init()
{
	stat._hp = 1;
	stat._maxhp = 1;
	stat._speed = 1000;
}

void Monster::Update()
{
	//start -> end 
	Vector mousePos = GET_SINGLE(InputManager)->GetMousePos();
	Vector v1 = _end - _start;

	float maxLength = v1.Length();
	// start ->mousepos 
	Vector v2 = mousePos - _start;
	v1.Normalize();
	float dot = v1.Dot(v2);

	Pos pos = _start + v1 * dot;
	
	if (dot<0 || dot>maxLength)
		return;
	_pos = pos;
}

void Monster::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, 10);

	HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 125, 255));
	HPEN oldpen = (HPEN)SelectObject(hdc, pen);
	{
		Utils::DrawLine(hdc, _start, _end); 
	}
	::SelectObject(hdc, oldpen);
	::DeleteObject(pen);
}
