#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Flipbook.h"

ResourceManager::~ResourceManager()
{
	Clear();

	for (auto& i : _textures)
		SAFE_DELETE(i.second, "texture delete");
	_textures.clear();

	for (auto& i : _sprites)
		SAFE_DELETE(i.second, "sprite delete");
	_sprites.clear();
	
	for (auto& i : _flipbooks)
		SAFE_DELETE(i.second, "flipbook delete");
	_flipbooks.clear();
	
}


void ResourceManager::Init(HWND hwnd, fs::path resourcePath)
{
	_hwnd = hwnd;
	_resourcePath = resourcePath;
}
void ResourceManager::Clear()
{
	for (auto& i : _textures)
	{
		SAFE_DELETE(i.second, "texture not deleted");
	}
	_textures.clear();
}



Texture* ResourceManager::LoadTexture(const wstring& key, const wstring& path, uint32 transparent,float angle)
{
	if (_textures.find(key) != _textures.end())
		return _textures[key];
	
	
	fs::path fullPath;
	if (path[0] == L'C')
		fullPath = path;
	else 
		fullPath = _resourcePath / path;

	Texture* texture = new Texture();

	if (angle == 0)
		texture->LoadBitMap(_hwnd, fullPath.c_str());
	else
		texture->LoadBitMapLotated(_hwnd, fullPath.c_str(), angle);
	
	texture->SetTransparent(transparent);

	_textures[key] = texture;
	return texture;

}

Sprite* ResourceManager::CreateSprite(const wstring& key,Texture* texture, int32 x, int32 y, int32 cx, int32 cy)
{
	if (_sprites.find(key) != _sprites.end())
		return _sprites[key];

	if (cx == 0)
		cx = texture->GetSize().x;

	if (cy == 0)
		cy = texture->GetSize().y;

	Sprite* sprite = new Sprite(texture, x, y, cx, cy);
	_sprites[key] = sprite;
	return sprite;
}

Flipbook* ResourceManager::CreateFlipbook(const wstring& key)
{
	if (_flipbooks.find(key) != _flipbooks.end())
		return _flipbooks[key];

	Flipbook* fb = new Flipbook();
	_flipbooks[key] = fb;
	
	return fb;
}

bool ResourceManager::LoadTexture_Sprite(const wstring& path)
{
	Texture* openFileTexture = GET_SINGLE(ResourceManager)->LoadTexture(path, path, 0, 0);
	Sprite *temp = GET_SINGLE(ResourceManager)->CreateSprite(path, openFileTexture, 0, 0, 0, 0);

	if (temp != nullptr)
		return true;

	return false;
}

