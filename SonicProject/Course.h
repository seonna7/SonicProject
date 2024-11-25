#pragma once
class Actor;
class Course
{
public : 
	Course();
	Course(Vector pos, Vector size, Actor* runner);
	virtual ~Course();

	void Init();
	bool Update();
	bool CourseMeetingFunction();

	virtual bool IsState_CourseEscaped() { return false; }
	virtual bool UpdateRunnerState() { return false; }
	virtual bool SetColorRef() { return false; }

	inline void InitCourseEnterInfo() { _courseEntered = false;	_coursePassed = false; }
public : 

	eCourse GetCourseInfo() { return _courseInfo; }

	bool GetCourseEntered() { return _courseEntered; }

	bool GetCoursePassed() { return _coursePassed; }

	COLORREF GetColorRef() { return _colorRef; }

protected : 
	bool _courseEntered = false;
	bool _coursePassed = false;

protected :
	bool _flag = false; // false = MAG, true = CYAN

	Vector _pos		= {};
	Vector _size	= {};

	Actor* _runner			= nullptr;
	eCourse _courseInfo;
	COLORREF	_colorRef	= ColorRef::RED;

};

