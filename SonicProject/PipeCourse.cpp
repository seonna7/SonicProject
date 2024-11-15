#include "pch.h"
#include "Course.h"
#include "PipeCourse.h"
#include "Actor.h"
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
	if (_flag == false)
	{
		if (_courseEntered == false)
		{

		}
		else if (_courseEntered == true)
		{

		}
	}
	else if (_flag == true)
	{
		if (_courseEntered == false)
		{

		}
		else if (_courseEntered == true)
		{

		}
	}


	return false;
}

bool PipeCourse::PassingCourse()
{
	return false;
}

bool PipeCourse::CourseMeetingFunction()
{
	return false;
}

