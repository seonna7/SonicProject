#pragma once
#include "Component.h"

class Actor;
class CameraComponent : public Component
{
public : 
	CameraComponent(Actor* owner);
	virtual ~CameraComponent();
	void BeginPlay() override;
	void TickComponent() override;
	void Render(HDC hdc) override;

};

