#pragma once
#include "Scene.h"
class Actor;
class EditScene : public Scene
{
public:

	EditScene();
	virtual ~EditScene()			 override;

	virtual void Init()				 override;
	virtual void Update()		     override;
	virtual void Render(HDC hdc)	 override;

	virtual bool RenderOnBackground(const wstring& key) override;
private : 
	vector<Actor*> _actors;
	vector<Actor*> _backgrounds;

	Player* _player = nullptr;
};


