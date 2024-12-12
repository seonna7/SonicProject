#pragma once
class Texture;
class Sprite;
class Flipbook;
  
class ResourceManager
{
public : 
	CREATE_SINGLE(ResourceManager);
	~ResourceManager();
public : 
	void Init(HWND hwnd, fs::path resourcePath);
	void Clear(); 

	const fs::path& getResorucePath() { return _resourcePath; }

	Texture*	GetTexture(const wstring& key) { return _textures[key]; }
	Texture*	LoadTexture(const wstring& key, const wstring& path, uint32 transparent = RGB(255,0,255),float angle = 0);

	Sprite*		GetSprite(const wstring& key) { return _sprites[key]; }
	Sprite*		CreateSprite(const wstring& key, Texture* texture, int32 x = 0, int32 y = 0, int32 cx = 0, int32 cy = 0);

	Flipbook*	GetFlipbook(const wstring& key) { return _flipbooks[key]; }
	Flipbook*	CreateFlipbook(const wstring& key);

	bool		LoadTexture_Sprite(const wstring& path);

private : 
	HWND _hwnd;
	fs::path _resourcePath;
	
	unordered_map<wstring, Texture*> _textures;
	unordered_map<wstring, Sprite *> _sprites;
	unordered_map<wstring, Flipbook*> _flipbooks;
};

