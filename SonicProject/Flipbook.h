#pragma once
#include "ResourceBase.h"
class Texture;

struct FlipbookInfo
{
	Texture* texture = nullptr;
	wstring name;
	Vector size = {};
	int32 start = 0;
	int32 end = 0;
	int32 line = 0;

	float duration = 1.f;
	bool loop = true;

};

class Flipbook : public ResourceBase
{
public:
	Flipbook() ;
	virtual ~Flipbook();

	void SetInfo(const FlipbookInfo& Info) { _Info = Info; }
	const FlipbookInfo GetInfo() { return _Info; }

private :
	FlipbookInfo _Info; 
};

