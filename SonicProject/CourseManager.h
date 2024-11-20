#pragma once
class Course;

class CourseManager
{
	CREATE_SINGLE(CourseManager);

public : 
	void Init();
	void Update();

	void AddCourse(Course* course);
	
	bool GetCourseEntered();
	bool GetCoursePassed();

	Course* GetContactedCourse();

private : 
	bool	_courseEntered = false;
	bool	_coursePassed = false;
	Course* _currContactedCourse = nullptr;
	vector<Course*> _courses;
};

