#pragma once
#include "ResourceBase.h"
class Texture;

class Sprite : public ResourceBase
{

public : 
	Sprite(Texture* texture, int32 x, int32 y, int32 cx, int32 cy);
	virtual ~Sprite();

	HDC GetDC();
	int32 GetTransparent();

	Vector GetPos()		{ return Pos(_x, _y); }
	Vector GetSize()	{ return Pos(_cx, _cy); }

	Texture* GetTexture() { return texture; }


	
private : 
	Texture* texture = nullptr;
	int32 _x;
	int32 _y;
	int32 _cx;
	int32 _cy;

};

