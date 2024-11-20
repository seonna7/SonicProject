#include "pch.h"
#include "Course.h"
#include "PipeCourse.h"
#include "Actor.h"
#include "Player.h"
#include "RigidBody.h"
PipeCourse::PipeCourse(Vector pos, Vector size, Actor* runner) : 
	Course(pos,size,runner)
{
	_courseInfo = eCourse::PIPE;

	_width = 2 * e_Pixel_Len;
}

PipeCourse::~PipeCourse()
{
}

void PipeCourse::Init()
{
	Super::Init();
}

bool PipeCourse::Update(bool& entered, bool& passed)
{
	if (Super::Update(entered, passed) == true)
	{
		return true;
	}
	return false;
}

bool PipeCourse::EnteringCourse()
{
	Vector runnerPos = _runner->GetPos();
	RECT _runner	= RECT(runnerPos.x - e_Pixel_Len,
						runnerPos.y - e_Pixel_Len,
						runnerPos.x + e_Pixel_Len,
						runnerPos.y + e_Pixel_Len);
	RECT Rect1		= RECT(_courseEnterCollideDetect[0].x - _width, 
							_courseEnterCollideDetect[0].y - _width,
							_courseEnterCollideDetect[0].x + _width, 
							_courseEnterCollideDetect[0].y + _width);
	RECT Rect2		= RECT(_courseEnterCollideDetect[1].x - _width, 
							_courseEnterCollideDetect[1].y - _width,
							_courseEnterCollideDetect[1].x + _width, 
							_courseEnterCollideDetect[1].y + _width);

	if (_courseEntered == false)
	{
		if (abs(_runner.bottom - Rect1.bottom) < 5)
		{
			RECT intersect = {};
			if (IntersectRect(&intersect, &Rect1, &_runner)||
				IntersectRect(&intersect, &Rect2, &_runner))
				return _courseEntered = true;
		}

	}
	else if (_courseEntered == true && _coursePassed == false)
	{
		if (abs(_runner.bottom - Rect1.bottom) < 5)
		{
			RECT intersect = {};
			if (IntersectRect(&intersect, &Rect1, &_runner) ||
				IntersectRect(&intersect, &Rect2, &_runner))
				_coursePassed = true;
				return _courseEntered = true;
		}
	}
	return _courseEntered == true;
}

bool PipeCourse::PassingCourse()
{
	return (_coursePassed == true) && (_courseEntered == true);
}

bool PipeCourse::SetColorRef()
{
	Player* runner = dynamic_cast<Player*>(_runner);

	if (runner == nullptr)
		return false;
	Physic* physic = runner->GetRigidBody()->GetPhysic();
	if (physic->_groundSpeed >= 0)
	{
		_colorRef = ColorRef::MAGENTA;
	}
	else if (physic->_groundSpeed < 0)
	{
		_colorRef = ColorRef::CYAN;
	}
}

bool PipeCourse::CourseMeetingFunction()
{
	return Super::CourseMeetingFunction();
}

