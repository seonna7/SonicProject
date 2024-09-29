#pragma once
#include "Scene.h"
class Actor;
class GameObject;
class LoopCollider;

struct BackGroundInfo
{
	Actor* background = nullptr;
	vector<Vector> loopPos;
};
class DevScene : public Scene
{
public:
	DevScene();
	virtual ~DevScene()			   override;

	virtual void Init()			   override;
	virtual void Update()		   override;
	virtual void Render(HDC hdc)	override;

	void AddActor(Actor* actor) { _actors.push_back(actor); }
	void RemoveActor(Actor* actor);



protected : 
	vector<Actor*> _actors;
	vector<Actor*> _backgrounds;
	vector<LoopCollider*> _LoopColliders; 
};