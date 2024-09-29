#include "pch.h"
#include "PixelCollider.h"

PixelCollider::PixelCollider()
	: Collider(eColliderType::PIXEL)
{
	this->SetComponentType(eComponentType::PIXEL_COLLIDER);
}

PixelCollider::PixelCollider(ePixelColliderType _type) 
	: Collider(eColliderType::PIXEL)
{
	this->SetComponentType(eComponentType::PIXEL_COLLIDER);
	this->SetPixelColliderType(_type);
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
}

void PixelCollider::Render(HDC hdc)
{
	Super::Render(hdc);
}

