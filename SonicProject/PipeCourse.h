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
	void SetSenorInfo(Vector vec[2], Vector size);
	void Init();
	bool Update(bool& entered, bool& passed);

	virtual bool UpdateRunnerState(bool& entered, bool& passed)			override;
	virtual bool IsState_CourseEscaped()								override;
	virtual bool SetColorRef()											override;

	bool CourseMeetingFunction();
private :
	Vector _courseEnterCollideDetect[2] = { {0,0},{0,0} };
	Vector _courseEnterSize				= { 0,0 };
	float _width						= 0.f;

	bool _contactFlag					= false;
};

