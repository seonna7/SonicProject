#pragma once


class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Init()			   abstract ;
	virtual void Update()		   abstract ;
	virtual void Render(HDC hdc) abstract ;

	virtual bool RenderOnBackground(const wstring& key);

protected : 

};

