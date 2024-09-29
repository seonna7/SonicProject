#include "pch.h"
#include "Sprite.h"
#include "Texture.h"

Sprite::Sprite(Texture* texture, int32 x, int32 y, int32 cx, int32 cy)
	: texture(texture), _x(x),_y(y),_cx(cx),_cy(cy)
{
	
}

Sprite::~Sprite()
{
}

HDC Sprite::GetDC()
{
	return texture->GetDC();
}

int32 Sprite::GetTransparent()
{
	return texture->GetTransparent();
}


