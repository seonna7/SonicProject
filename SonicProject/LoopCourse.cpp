#include "pch.h"
#include "LoopCourse.h"
#include "Course.h"
#include "Actor.h"
#include "CourseManager.h"

LoopCourse::LoopCourse(Vector pos, Vector size, Actor* runner) :
	Course(pos,size,runner)
{
	_courseInfo = eCourse::LOOP;
	_endLine = pos.x + size.x / 2;
	_beginLine = pos.x - size.x / 2;
	_midLine = pos.x;
}

LoopCourse::~LoopCourse()
{
}

void LoopCourse::Init()
{
	Super::Init();
}

bool LoopCourse::Update(bool& entered, bool& passed)
{
	if (Super::Update(entered, passed) == true)
	{
		return true;
	}
	return false;
}

bool LoopCourse::EnteringCourse()
{
	Vector runnerPos = _runner->GetPos();

	if (runnerPos.x >= _beginLine && runnerPos.x < _midLine)
	{
		if (_flag == false && _courseEntered == false)
		{
			return false; // 루프 시작 전임  
		}
		else if (_flag == true && _courseEntered == false)
		{
			return _courseEntered = true; // 루프 코스 시작 
		}
		else if (_flag == true && _courseEntered == true)
		{
			return true; // 루프 진행중임
		}
		else if (_flag == false && _courseEntered == true)
		{
			if (runnerPos.y < _pos.y)
			{
				_flag = !_flag;
				_coursePassed = true;
			}
		}
	}
	else if (runnerPos.x >= _midLine && runnerPos.x < _endLine)
	{
		if (_flag == false && _courseEntered ==false)
		{
			return _courseEntered = true; // 루프 코스 시작 
		}
		else if (_flag == true && _courseEntered == false)
		{
			return false; // 루프 시작 전임 
		}
		else if (_flag == false && _courseEntered == true)
		{
			return true; // 루프 진행중임
		}
		else if (_flag == true && _courseEntered == true)
		{
			if (runnerPos.y < _pos.y)
			{
				_flag = !_flag;
				_coursePassed = true;
			}
		}
	}
	return _courseEntered == true;
}

bool LoopCourse::PassingCourse()
{
	if (_flag == true && _coursePassed == true)
	{
		if (_runner->GetPos().x > _pos.x)
		{
			return  true;
		}
	}
	else if (_flag == false && _coursePassed == true)
	{
		if (_runner->GetPos().x < _pos.x)
		{
			return true;
		}
	}
	return false;
}

bool LoopCourse::CourseMeetingFunction()
{
	return Super::CourseMeetingFunction();
}

bool LoopCourse::SetColorRef()
{
	if (_flag == false)
	{
		_colorRef = ColorRef::MAGENTA;
	}
	else if (_flag == true)
	{
		_colorRef = ColorRef::CYAN;
	}
	return true;
}
