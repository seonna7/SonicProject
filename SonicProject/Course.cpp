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

	if (_courseEntered == true)
	{
		entered = true;
	}
	else if (_coursePassed == true)
	{
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
