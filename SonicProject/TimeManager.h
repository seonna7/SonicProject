#pragma once
class TimeManager
{
	CREATE_SINGLE(TimeManager);

public : 
	void Init();
	void Update();

	uint32 Get_FPS() { return _FPS; }
	float Get_deltaTime() { return _deltaTime; }



private :
	uint64 _frequency = 0;
	uint64 _prevCount = 0;
	float _deltaTime = 0.f;

private :
	uint32 _frameCount = 0;
	float _frameTime = 0.f;
	uint32 _FPS = 0;
};

