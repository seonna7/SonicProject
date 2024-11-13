#include "pch.h"
#include "LoopCourse.h"
#include "Course.h"
#include "Actor.h"

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

void LoopCourse::Update()
{
	if (IsCourseEntered() == true)
	{
		LoopCourse::CourseMeetingFunction();
	}
	else if (IsCourseEntered() == false)
	{
		return;
	}
}

bool LoopCourse::IsCourseEntered()
{
	Vector runnerPos = _runner->GetPos();

	if (runnerPos.x >= _beginLine && runnerPos.x < _midLine)
	{
		if (_flag == false && _workIn == false)
		{
			return false; // ���� ���� ����  
		}
		else if (_flag == true && _workIn == false)
		{
			_workIn = true; // ���� �ڽ� ���� 
		}
		else if (_flag == true && _workIn == true)
		{
			return true; // ���� ��������
		}
		else if (_flag == false && _workIn == true)
		{
			if (_coursePassed == false)
			{
				_coursePassed = true;
				_flag = true; // ���� �÷��� ���� 
			}
			else
			{
				_coursePassed = false;
			}
		}
	}
	else if (runnerPos.x >= _midLine && runnerPos.x < _endLine)
	{
		if (_flag == false && _workIn ==false)
		{
			_workIn = true; // ���� �ڽ� ���� 
		}
		else if (_flag == true && _workIn == false)
		{
			return false; // ���� ���� ���� 
		}
		else if (_flag == false && _workIn == true)
		{
			return true; // ���� ��������
		}
		else if (_flag == true && _workIn == true)
		{
			if (_coursePassed == false)
			{
				_coursePassed = true;
				_flag = false; // ���� �÷��� ���� 
			}
			else
			{
				_coursePassed = false;
			}
		}
	}

	return _workIn;

}

bool LoopCourse::CourseMeetingFunction()
{
	if (SetColorRef(_workIn) == true)
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
