#pragma once
#include "Course.h"
class PipeCourse : public Course
{
public : 
	using Super = Course;
public : 

	PipeCourse(Vector pos, Vector size, Actor* runner);
	~PipeCourse();

public : 
	void Init();
	bool Update(bool& entered, bool& passed);

	bool EnteringCourse()						override;
	bool PassingCourse()						override;
	bool CourseMeetingFunction()				override;

private :
	Vector _enterPos	= { 0,0 };
	Vector _endPos		= { 0,0 };

	float _width		= 0.f;
};

