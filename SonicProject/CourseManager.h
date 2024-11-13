#pragma once
class Course;

class CourseManager
{
	CREATE_SINGLE(CourseManager);

public : 
	void Init();
	void Update();

	void AddCourse(Course* course);
	
	Course* GetContactedCourse();

	template <typename T>
	T* GetCurrCourse()
	{
		T* currCourse = dynamic_cast<T*>(_currContactedCourse);
		return currCourse;
	}


private : 
	Course* _currContactedCourse = nullptr;
	vector<Course*> _courses;
};

