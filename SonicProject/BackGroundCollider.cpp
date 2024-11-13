#include "pch.h"
#include "BackGroundCollider.h"
#include "PixelCollider.h"
#include "TimeManager.h"
#include "Player.h"
BackGroundCollider::BackGroundCollider() : Collider(eColliderType::BACKGROUND)
{
    this->SetComponentType(eComponentType::BACKGROUND_COLLIDER);
}

BackGroundCollider::~BackGroundCollider()
{
}

void BackGroundCollider::BeginPlay()
{
}

void BackGroundCollider::TickComponent()
{
}

void BackGroundCollider::Render(HDC hdc)
{
}

bool BackGroundCollider::CheckCollision(Collider* other)
{
    Player* player = dynamic_cast<Player*>(other->GetOwner());
    if (player == nullptr)
        return false;

    PixelCollider* pixelCollider = dynamic_cast<PixelCollider*>(other);
    if (pixelCollider==nullptr)
        return false;
    ePixelColliderType _type = pixelCollider->GetPixelColliderType();
    switch (_type)
    {
    case ePixelColliderType::GROUND : 
        //player->CheckCollision_Ground();
        return false;
    case ePixelColliderType::WALL :
    {
        return false;
        }
    case ePixelColliderType::CEILING:
        break;
    case ePixelColliderType::PUSH:
        break;
    case ePixelColliderType::CLIFF:
        break;
    }
    return false;
}
