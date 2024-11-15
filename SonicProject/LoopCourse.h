#pragma once
#include "Course.h"
class LoopCourse : public Course
{
public : 
	using Super = Course;

	LoopCourse(Vector pos, Vector size, Actor* runner);
	~LoopCourse();
	
public  :
	void Init();
	bool Update(bool& entered, bool& passed);

	bool EnteringCourse()							override;
	bool PassingCourse()							override;

	bool CourseMeetingFunction()					override;

	bool SetColorRef();

private :  
	
	float _endLine = 0.f;
	float _beginLine = 0.f;
	float _midLine = 0.f;
};

