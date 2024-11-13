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
}

bool LoopCourse::Update(bool& entered, bool& passed)
{
	if (IsCourseEntered() == true)
	{
		LoopCourse::CourseMeetingFunction();

		entered = true;
	}
	else if (IsCoursePassed() == true)
	{
		passed = true;
	}
	else
	{
		entered = false;
		passed = false;
	}
	return false;
}

bool LoopCourse::IsCourseEntered()
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
			_courseEntered = true; // 루프 코스 시작 
		}
		else if (_flag == true && _courseEntered == true)
		{
			return true; // 루프 진행중임
		}
		else if (_flag == false && _courseEntered == true)
		{
			if (_coursePassed == false)
			{
				_flag = true; // 루프 플래그 변경 
				_coursePassed = true;
			}
		}
	}
	else if (runnerPos.x >= _midLine && runnerPos.x < _endLine)
	{
		if (_flag == false && _courseEntered ==false)
		{
			_courseEntered = true; // 루프 코스 시작 
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
			if (_coursePassed == false)
			{
				_coursePassed = true;
				_flag = false; // 루프 플래그 변경 
			}
		}
	}

	return _courseEntered == true;
}

bool LoopCourse::IsCoursePassed()
{
	if (_flag == true && _coursePassed == true)
	{
		if (_runner->GetPos().x > _pos.x)
		{
			return _coursePassed != true;
		}
	}
	else if (_flag == false && _coursePassed == true)
	{
		if (_runner->GetPos().x < _pos.x)
		{
			return _coursePassed != true;
		}
	}
	return _coursePassed = false;
}

bool LoopCourse::CourseMeetingFunction()
{
	if (SetColorRef(_courseEntered) == true)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

bool LoopCourse::SetColorRef(bool Entered)
{
	if (Entered == false)
	{
		return false;
	}

	if (_flag == false)
	{
		_colorRef = ColorRef::MANGENTA;
	}
	else if (_flag == true)
	{
		_colorRef = ColorRef::CYAN;
	}
	return true;
}
