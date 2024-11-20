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
		course->Update();
		if (course->GetCourseEntered() == true)
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

bool CourseManager::GetCourseEntered()
{
	if (_currContactedCourse == nullptr)
	{
		return false;
	}
	return _currContactedCourse->GetCourseEntered();
}

bool CourseManager::GetCoursePassed()
{
	if (_currContactedCourse == nullptr)
	{
		return false;
	}
	return _currContactedCourse->GetCoursePassed();
}

Course* CourseManager::GetContactedCourse()
{
	return _currContactedCourse;
}



