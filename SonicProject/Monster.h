#pragma once
#include "Object.h"
class Monster : public Object
{
public : 
	Monster();
	virtual ~Monster();

	void Init() override;
	void Update() override;
	void Render(HDC hdc) override;


private : 
	Vector _start	= {300,100};
	Vector _end		= {600,250};
};

