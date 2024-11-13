#pragma once
#include "Course.h"
class LoopCourse : public Course
{
public : 
	LoopCourse(Vector pos, Vector size, Actor* runner);
	~LoopCourse();
	
public  :
	void Init()										override;
	bool Update(bool& entered, bool& passed)		override;

	bool IsCourseEntered()							override;
	bool IsCoursePassed()							override;

	bool CourseMeetingFunction()					override;

	bool SetColorRef(bool Entered);
	COLORREF GetColorRef() { return _colorRef; }
private :  
	bool _courseEntered = false;
	bool _coursePassed = false;

	bool _flag = false; // false = MAG, true = CYAN
	
	float _endLine = 0.f;
	float _beginLine = 0.f;
	float _midLine = 0.f;


	COLORREF	_colorRef = ColorRef::RED;
};

