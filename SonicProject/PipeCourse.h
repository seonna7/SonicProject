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

	virtual bool EnteringCourse()						override;
	virtual bool PassingCourse()						override;
	virtual bool SetColorRef()							override;

	bool CourseMeetingFunction();
private :
	Vector _courseEnterCollideDetect[2];

	Vector _courseEnterSize = { 0,0 };

	float _width		= 0.f;
};

