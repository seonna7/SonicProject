#include "pch.h"
#include "TunnelCourse.h"

TunnelCourse::TunnelCourse(Vector pos, Vector size, Actor* runner) : 
	Course(pos,size,runner)
{
	_courseInfo = eCourse::TUNNEL;
}

TunnelCourse::~TunnelCourse()
{
}

void TunnelCourse::Init()
{
}

void TunnelCourse::Update()
{
}

bool TunnelCourse::IsCourseEntered()
{
	return false;
}
