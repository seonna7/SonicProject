#include "pch.h"
#include "PixelCollider.h"
#include "Actor.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Utils.h"

PixelCollider::PixelCollider(Actor* owner, ePixelColliderType _type, uint8 dir,Vector dist)
	: Collider(eColliderType::PIXEL), _dist(dist), _dir(dir)
{
	this->SetComponentType(eComponentType::PIXEL_COLLIDER);
	this->SetPixelColliderType(_type);
	this->SetOwner(owner);
	owner->AddComponent(this);
	GET_SINGLE(CollisionManager)->AddCollider(this);

	SetDirVector(dir);
}

PixelCollider::~PixelCollider()
{
}


void PixelCollider::BeginPlay()
{
	Super::BeginPlay();
}

void PixelCollider::TickComponent()
{
	Super::TickComponent();
	PixelCollider::SetPos();
}

void PixelCollider::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_showDebug == false)
		return;

	Vector cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	Vector pixel = _pos;

	{
		pixel.x -= (cameraPos.x - GWinSizeX / 2);
		pixel.y -= (cameraPos.y - GWinSizeY / 2);
		Utils::DrawCircle(hdc, pixel, PixelSize);
	}
}

void PixelCollider::SetDirVector(uint8 dir)
{
	uint8 currCheck = 1;
	
	for (int i = 0; i < 4; i++)
	{
		if(currCheck&dir)
		{
			switch (i)
			{
			case 0:
				_dirVector += {-1, 0};
				break;
			case 1:
				_dirVector += {1, 0};
				break;
			case 2:
				_dirVector += {0, 1};
				break;
			case 3:
				_dirVector += {0, -1};
				break;
			}
		}
		currCheck = currCheck << 1;
	}
}

bool PixelCollider::CheckCollision(Collider* other)
{
	return false;
}

void PixelCollider::SetPos()
{
	float x = _dirVector.x * _dist.x;
	float y = _dirVector.y * _dist.y;

	Actor* owner = GetOwner();
	_pos = Vector(owner->GetPos().x + x, owner->GetPos().y + y);
}