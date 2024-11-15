#include "pch.h"
#include "CourseManager.h"
#include "Course.h"
#include "LoopCourse.h"
#include "PipeCourse.h"
void CourseManager::Init()
{
}

void CourseManager::Update()
{
	for (auto& course : _courses)
	{
		course->Update(_courseEntered, _coursePassed);
		if (_courseEntered == true)
		{
			_currContactedCourse = course;
		}
	}
}

void CourseManager::AddCourse(Course* course)
{
	if (find(_courses.begin(), _courses.end(), course) != _courses.end())
	{
		return;
	}
	else
	{
		_courses.push_back(course);
	}
}

Course* CourseManager::GetContactedCourse()
{
	return _currContactedCourse;
}



