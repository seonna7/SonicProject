#include "pch.h"
#include "Course.h"

Course::Course(Vector pos, Vector size, Actor* runner) : 
	_pos(pos), _size(size), _runner(runner)
{
}

Course::~Course()
{
}
