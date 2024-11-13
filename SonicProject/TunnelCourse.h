#pragma once
#include "Course.h"
class TunnelCourse : public Course
{
	TunnelCourse(Vector pos, Vector size, Actor* runner);
	~TunnelCourse();

public:
	void Init()				override;
	void Update()			override;

	bool IsCourseEntered()	override;

};

