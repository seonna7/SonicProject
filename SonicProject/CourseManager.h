#pragma once
class Course;

class CourseManager
{
	CREATE_SINGLE(CourseManager);

public : 
	void Init();
	void Update();

	void AddCourse(Course* course);
	
	bool GetCourseEntered() { return _courseEntered; }
	bool GetCoursePassed()	{ return _coursePassed; }

	Course* GetContactedCourse();

	template <typename T>
	T* GetCurrCourse()
	{
		T* currCourse = dynamic_cast<T*>(_currContactedCourse);
		return currCourse;
	}

private : 
	bool	_courseEntered = false;
	bool	_coursePassed = false;
	Course* _currContactedCourse = nullptr;
	vector<Course*> _courses;
};

