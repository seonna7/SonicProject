#pragma once
#include "Course.h"
class TunnelCourse : public Course
{
	TunnelCourse(Vector pos, Vector size, Actor* runner);
	~TunnelCourse();

public:
	void Init()									override;
	bool Update(bool& entered, bool& passed)	override;

};

