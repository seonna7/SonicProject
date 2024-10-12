#include "pch.h"
#include "AccelObj.h"

AccelObj::AccelObj(Vector dir) : 
	BoxCollider()
{
	_dir = dir;
}

void AccelObj::BeginPlay()
{
	Super::BeginPlay();
}

void AccelObj::TickComponent()
{
	Super::TickComponent();
}

void AccelObj::Render(HDC hdc)
{
	Super::Render(hdc);
}

bool AccelObj::CheckCollision(Collider* other)
{
	return Super::CheckCollision(other);
}
