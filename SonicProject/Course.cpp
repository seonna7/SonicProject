#include "pch.h"
#include "Course.h"

Course::Course(Vector pos, Vector size, Actor* runner) : 
	_pos(pos), _size(size), _runner(runner)
{
}

Course::~Course()
{
}

void Course::Init()
{
}

bool Course::Update(bool& entered, bool& passed)
{
	CourseMeetingFunction();
	_courseEntered = EnteringCourse();
	_coursePassed = PassingCourse();

	if (_courseEntered == true && _coursePassed == false)
	{
		entered = true;
	}
	else if (_courseEntered==true &&_coursePassed == true)
	{
		entered = false;
		passed = true;
		passed = true;
	}
	else
	{
		entered = false;
		passed = false;
		_courseEntered = false;
		_coursePassed = false;
	}
	return false;
}

bool Course::CourseMeetingFunction()
{
	if (_coursePassed == true)
	{
		return false;
	}
	SetColorRef();
	return true;
}
