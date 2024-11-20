#include "pch.h"
#include "Course.h"

Course::Course() : _courseInfo(eCourse::NONE)
{

}

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

bool Course::Update()
{
	UpdateRunnerState(_courseEntered,_coursePassed);
	if(_courseEntered== true)
	{
		CourseMeetingFunction();
	}
	
	if (IsState_CourseEscaped() == true)
	{
		_courseEntered = false;
		_coursePassed = false;
	}
	return true;
}

bool Course::CourseMeetingFunction()
{
	if (_courseEntered == false)
	{
		return false;
	}
	else 
	{
		SetColorRef();
	}
	return true;
}
