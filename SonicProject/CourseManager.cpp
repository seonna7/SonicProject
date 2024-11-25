#include "pch.h"
#include "CourseManager.h"
#include "Course.h"
#include "LoopCourse.h"
#include "PipeCourse.h"
void CourseManager::Init()
{
	_currContactedCourse = new Course();
}

void CourseManager::Update()
{
	if (_currContactedCourse->GetCourseInfo() == eCourse::NONE)
	{
		for (auto& course : _courses)
		{
			course->Update();

			if (course->GetCourseEntered() == true)
			{
				if (_currContactedCourse->GetCourseInfo() == eCourse::NONE)
				{
					SAFE_DELETE(_currContactedCourse, "Course Delete");
					_currContactedCourse = course;
				}
			}
		}
	}
	else
	{
		_currContactedCourse->Update();
		if (_currContactedCourse->IsState_CourseEscaped() == true)
		{
			_currContactedCourse->InitCourseEnterInfo();
			_currContactedCourse = new Course();
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
	if (_currContactedCourse->GetCourseInfo() == eCourse::NONE)
	{
		return false;
	}
	return _currContactedCourse->GetCourseEntered();
}

bool CourseManager::GetCoursePassed()
{
	if (_currContactedCourse->GetCourseInfo() == eCourse::NONE)
	{
		return false;
	}
	return _currContactedCourse->GetCoursePassed();
}

Course* CourseManager::GetContactedCourse()
{
	if (_currContactedCourse->GetCourseEntered() == true)
		return _currContactedCourse;
	
	return nullptr;
}



