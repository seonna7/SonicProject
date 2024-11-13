#include "pch.h"
#include "CourseManager.h"
#include "Course.h"
#include "LoopCourse.h"
#include "TunnelCourse.h"
void CourseManager::Init()
{
}

void CourseManager::Update()
{
	for (auto& course : _courses)
	{
		course->Update();
	}
}

void CourseManager::AddCourse(Course* course)
{
	if (find(_courses.begin(), _courses.end(), course) == _courses.end())
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
	for (auto& course : _courses)
	{
		if (course->IsCourseEntered() == true)
		{
			_currContactedCourse = course;
			return _currContactedCourse;
		}
	}

	return _currContactedCourse = nullptr;
}
