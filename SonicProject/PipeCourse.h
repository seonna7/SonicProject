#pragma once
#include "Course.h"
enum Index
{
	NONE = 0,
	FIRST = 1,
	SECOND = 2
};

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

	virtual bool UpdateRunnerState()			override;
	virtual bool IsState_CourseEscaped()								override;
	virtual bool SetColorRef()											override;

	bool IsContactedEnterSection();
	bool IsContactedEnterSection(uint8 index);
	bool IsRunnerInPipeSection();
	bool CourseMeetingFunction();
private :

	uint8	_currEnterSectionIndex;

	Vector	_RectSize	= { 0,0 };
	RECT	_EnterSection[3];
	RECT	_PipeSection;
};

