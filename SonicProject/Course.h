#pragma once
class Actor;
class Course
{
public : 
	Course(Vector pos, Vector size, Actor* runner);
	~Course();

	virtual void Init()						abstract;
	virtual void Update()					abstract;

	virtual bool IsCourseEntered()			abstract;

	virtual bool CourseMeetingFunction()	abstract;

	eCourse GetCourseInfo() { return _courseInfo; }

protected :
	Vector _pos		= {};
	Vector _size	= {};
	Actor* _runner = nullptr;
	eCourse _courseInfo;
};
