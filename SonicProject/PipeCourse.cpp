#include "pch.h"
#include "Course.h"
#include "PipeCourse.h"
#include "Actor.h"
#include "Player.h"
#include "RigidBody.h"
PipeCourse::PipeCourse(Vector pos, Vector size, Actor* runner) : 
	Course(pos,size,runner)
{
	_courseInfo = eCourse::PIPE;

	_PipeSection = RECT(pos.x - size.x/2,
						pos.y - size.y/2,
						pos.x + size.x/2,
						pos.y + size.y/2);

	_currEnterSectionIndex = Index::NONE;
}

PipeCourse::~PipeCourse()
{
}

void PipeCourse::SetSensorsInfo(Vector* vec, Vector size, float flagSwitcher)
{
	_RectSize = size;
	_EnterSection[1] = RECT(vec[0].x - _RectSize.x,
							vec[0].y - _RectSize.y,
							vec[0].x + _RectSize.x,
							vec[0].y + _RectSize.y);
	_EnterSection[2] = RECT(vec[1].x - _RectSize.x,
							vec[1].y - _RectSize.y,
							vec[1].x + _RectSize.x,
							vec[1].y + _RectSize.y);
	_flagSwitcher = flagSwitcher;
}

void PipeCourse::Init()
{
	Super::Init();
}

bool PipeCourse::Update(bool& entered, bool& passed)
{
	if (Super::Update() == true)
	{
		return true;
	}
	return false;
}

bool PipeCourse::UpdateRunnerState()
{
	Vector runnerPos = _runner->GetPos();
	Player* player = dynamic_cast<Player*>(_runner);

	if (IsContactedEnterSection() == true)
	{
		// 진입 시작 	
	}

	if (_courseEntered == false)
	{
		if (IsContactedEnterSection(_currEnterSectionIndex) == false)
		{
			_currEnterSectionIndex = Index::NONE;

			if (IsRunnerInPipeSection() == true)
			{
				_courseEntered = true;
				_colorRef = ColorRef::MAGENTA;
			}
			else 
			{
				_courseEntered = false;
				_coursePassed = false;
			}
		}
	}
	else if (_courseEntered == true)
	{
		if (IsRunnerInPipeSection() == false)
		{
			_courseEntered = false;
		}
		Player* player = dynamic_cast<Player*>(_runner);

		if (IsContactedEnterSection() == true)
		{
			_coursePassed = true;
		}
		if (_coursePassed == true && IsContactedEnterSection() == false)
		{
			if (IsRunnerInPipeSection() == true)
			{
				//코스 수행 실패
				_courseEntered = true;
				_coursePassed = false;
			}
		}
	}
	return true;
}

bool PipeCourse::IsState_CourseEscaped()
{
	if ((_courseEntered == false && _coursePassed == false) || 
		(_courseEntered == true && _coursePassed == true))
	{
		if (IsContactedEnterSection() == false)
			return true;
	}
	return false;
}

bool PipeCourse::SetColorRef()
{
	Player* player = dynamic_cast<Player*>(_runner);

	if (player == nullptr)
		return false;

	Vector runnerPos = _runner->GetPos();
	if (runnerPos.y < _flagSwitcher)
	{
		_colorRef = ColorRef::MAGENTA;
	}
	else
	{
		_colorRef = ColorRef::CYAN;
	}
	
	return true;
}

bool PipeCourse::IsContactedEnterSection()
{
	RECT intersect = {};

	Vector runnerPos = _runner->GetPos();

	RECT _runner = RECT(runnerPos.x - e_Pixel_Len,
		runnerPos.y - e_Pixel_Len,
		runnerPos.x + e_Pixel_Len,
		runnerPos.y + e_Pixel_Len);

	if (IntersectRect(&intersect, &_EnterSection[1], &_runner))
	{
		_currEnterSectionIndex = Index::FIRST;
		return true;
	}
	else if (IntersectRect(&intersect, &_EnterSection[2], &_runner))
	{
		_currEnterSectionIndex = Index::SECOND;
		return true;
	}
	return false;
}

bool PipeCourse::IsContactedEnterSection(uint8 index)
{
	RECT intersect = {};

	Vector runnerPos = _runner->GetPos();

	RECT _runner = RECT(runnerPos.x - e_Pixel_Len,
		runnerPos.y - e_Pixel_Len,
		runnerPos.x + e_Pixel_Len,
		runnerPos.y + e_Pixel_Len);

	if (IntersectRect(&intersect, &_EnterSection[index], &_runner))
	{
		return true;
	}
	return false;
}

bool PipeCourse::IsRunnerInPipeSection()
{
	RECT intersect = {};

	Vector runnerPos = _runner->GetPos();

	RECT _runner = RECT(runnerPos.x - e_Pixel_Len,
		runnerPos.y - e_Pixel_Len,
		runnerPos.x + e_Pixel_Len,
		runnerPos.y + e_Pixel_Len);

	if (IntersectRect(&intersect, &_PipeSection, &_runner))
	{
		return true;
	}
	return false;
}

bool PipeCourse::CourseMeetingFunction()
{
	// SetColorRef() 호출 코드 
	return Super::CourseMeetingFunction();
}

bool PipeCourse::IsRunnerCorrectlyInPipeSection()
{
	RECT intersect = {};

	Vector runnerPos = _runner->GetPos();

	RECT _runner = RECT(runnerPos.x - e_Pixel_Len,
		runnerPos.y - e_Pixel_Len,
		runnerPos.x + e_Pixel_Len,
		runnerPos.y + e_Pixel_Len);

	if (_runner.left > _PipeSection.left &&
		_runner.right < _PipeSection.right &&
		_runner.top > _PipeSection.top &&
		_runner.bottom < _PipeSection.bottom)
		return true;
	return false;
}

