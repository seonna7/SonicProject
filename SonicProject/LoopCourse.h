#pragma once
#include "Course.h"
class LoopCourse : public Course
{
public : 
	LoopCourse(Vector pos, Vector size, Actor* runner);
	~LoopCourse();
	
public  :
	void Init()				override;
	void Update()			override;

	bool IsCourseEntered()	override;

	bool CourseMeetingFunction()	override;

	bool SetColorRef(bool Entered);
	COLORREF GetColorRef() { return _colorRef; }
private : 
	bool _workIn = false;
	bool _flag = false; // false = MAG, true = CYAN

	float _endLine = 0.f;
	float _beginLine = 0.f;
	float _midLine = 0.f;

	bool _coursePassed = false;

	COLORREF	_colorRef = ColorRef::RED;
};
