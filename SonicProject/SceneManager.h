#pragma once
class SceneManager
{
	CREATE_SINGLE(SceneManager);
public : 
	void Init();
	void Update();
	void Render(HDC hdc);

	void Clear();

public : 
	void ChangeScene(eSceneType scenetype);
	eSceneType GetSceneType() { return _sceneType;}



	void AddBackGround(const wstring& key);
private :
	class Scene* _scene = nullptr;
	eSceneType _sceneType =eSceneType::NONE;


public : 
	Vector GetCameraPos() { return _cameraPos; }
	void SetCameraPos(Vector pos) { _cameraPos = pos; }

private : 

	Vector _cameraPos = { 0,0 };
};

