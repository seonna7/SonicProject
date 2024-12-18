#include "pch.h"
#include "DevScene.h"
#include "Utils.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "EventManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Texture.h"
#include "Sprite.h"
#include "Actor.h"
#include "SpriteActor.h"
#include "Flipbook.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "PixelCollider.h"
#include "BackGroundCollider.h"
#include "AccelObj.h"
#include "CourseManager.h"
#include "LoopCourse.h"
#include "PipeCourse.h"

extern uint32 GWinSizeX;
extern uint32 GWinSizeY;

DevScene::DevScene()
{
}

DevScene::~DevScene()
{
}

void DevScene::Init()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"Stage01", L"Sprite\\MAP\\Stage01.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Map1", L"Sprite\\MAP\\greenhillzone.bmp");
	//GET_SINGLE(ResourceManager)->LoadTexture(L"map1", L"Sprite\\MAP\\map1.bmp",RGB(0,0,0));
	// 뒷배경 
	GET_SINGLE(ResourceManager)->LoadTexture(L"mapview", L"Sprite\\MAP\\mapview.bmp");
	//테스트용 
	GET_SINGLE(ResourceManager)->LoadTexture(L"maptest1", L"Sprite\\MAP\\maptest1.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"maptest2", L"Sprite\\MAP\\maptest2.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"fuck", L"Sprite\\MAP\\fuck.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"maptest4", L"Sprite\\MAP\\maptest4.bmp");

	GET_SINGLE(ResourceManager)->LoadTexture(L"loop", L"Sprite\\MAP\\loop.bmp");

	GET_SINGLE(ResourceManager)->LoadTexture(L"Sonic_Standing", L"Sprite\\Player\\Sonic_Standing.bmp", RGB(0, 255, 0));
	
	GET_SINGLE(ResourceManager)->LoadTexture(L"Sonic_Running_Left_0", L"Sprite\\Player\\Sonic_Running_Left_0.bmp", RGB(0, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Sonic_Running_Left_45", L"Sprite\\Player\\Sonic_Running_Left_45.bmp", RGB(0, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Sonic_Running_Left_90", L"Sprite\\Player\\Sonic_Running_Left_90.bmp", RGB(0, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Sonic_Running_Left_135", L"Sprite\\Player\\Sonic_Running_Left_135.bmp", RGB(0, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Sonic_Running_Left_180", L"Sprite\\Player\\Sonic_Running_Left_180.bmp", RGB(0, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Sonic_Running_Left_225", L"Sprite\\Player\\Sonic_Running_Left_225.bmp", RGB(0, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Sonic_Running_Left_270", L"Sprite\\Player\\Sonic_Running_Left_270.bmp", RGB(0, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Sonic_Running_Left_315", L"Sprite\\Player\\Sonic_Running_Left_315.bmp", RGB(0, 255, 0));


	GET_SINGLE(ResourceManager)->LoadTexture(L"Sonic_Running_Right_0", L"Sprite\\Player\\Sonic_Running_Right_0.bmp", RGB(0, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Sonic_Running_Right_45", L"Sprite\\Player\\Sonic_Running_Right_45.bmp", RGB(0, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Sonic_Running_Right_90", L"Sprite\\Player\\Sonic_Running_Right_90.bmp", RGB(0, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Sonic_Running_Right_135", L"Sprite\\Player\\Sonic_Running_Right_135.bmp", RGB(0, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Sonic_Running_Right_180", L"Sprite\\Player\\Sonic_Running_Right_180.bmp", RGB(0, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Sonic_Running_Right_225", L"Sprite\\Player\\Sonic_Running_Right_225.bmp", RGB(0, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Sonic_Running_Right_270", L"Sprite\\Player\\Sonic_Running_Right_270.bmp", RGB(0, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Sonic_Running_Right_315", L"Sprite\\Player\\Sonic_Running_Right_315.bmp", RGB(0, 255, 0));
	
	GET_SINGLE(ResourceManager)->LoadTexture(L"Sonic_Rolling", L"Sprite\\Player\\Sonic_Rolling.bmp", RGB(0, 255, 0));
	
	GET_SINGLE(ResourceManager)->LoadTexture(L"Sonic_Skiddling_Left", L"Sprite\\Player\\Sonic_Skiddling_Left.bmp", RGB(0, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Sonic_Skiddling_Right", L"Sprite\\Player\\Sonic_Skiddling_Right.bmp", RGB(0, 255, 0));
	
	GET_SINGLE(ResourceManager)->LoadTexture(L"Sonic_Sitting", L"Sprite\\Player\\Sonic_Sitting.bmp", RGB(0, 255, 0));


	GET_SINGLE(ResourceManager)->CreateSprite(L"Stage01", GET_SINGLE(ResourceManager)->GetTexture(L"Stage01"));
	//GET_SINGLE(ResourceManager)->CreateSprite(L"map1", GET_SINGLE(ResourceManager)->GetTexture(L"map1"));
	
	
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Sonic_Standing");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Standing");
		fb->SetInfo({ texture, L"FB_Standing", {32, 48}, 0, 3, 0, 5.0f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Sonic_Running_Left_0");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Running_Left_0");
		fb->SetInfo({ texture, L"FB_Running_Left_0", {37, 48}, 0, 4, 0, 0.1f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Sonic_Running_Left_45");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Running_Left_45");
		fb->SetInfo({ texture, L"FB_Running_Left_45", {42, 48}, 0, 4, 0, 0.2f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Sonic_Running_Left_90");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Running_Left_90");
		fb->SetInfo({ texture, L"FB_Running_Left_90", {48, 37}, 0, 4, 0, 0.1f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Sonic_Running_Left_135");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Running_Left_135");
		fb->SetInfo({ texture, L"FB_Running_Left_135", {42, 48}, 0, 4, 0, 0.2f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Sonic_Running_Left_180");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Running_Left_180");
		fb->SetInfo({ texture, L"FB_Running_Left_180", {37, 48}, 0, 4, 0, 0.1f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Sonic_Running_Left_225");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Running_Left_225");
		fb->SetInfo({ texture, L"FB_Running_Left_225", {42, 48}, 0, 4, 0, 0.2f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Sonic_Running_Left_270");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Running_Left_270");
		fb->SetInfo({ texture, L"FB_Running_Left_270", {48, 37}, 0, 4, 0, 0.1f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Sonic_Running_Left_315");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Running_Left_315");
		fb->SetInfo({ texture, L"FB_Running_Left_315", {48, 42}, 0, 4, 0, 0.2f });
	}
	
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Sonic_Running_Right_0");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Running_Right_0");
		fb->SetInfo({ texture, L"FB_Running_Right_0", {37, 48}, 0, 4, 0, 0.1f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Sonic_Running_Right_45");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Running_Right_45");
		fb->SetInfo({ texture, L"FB_Running_Right_45", {42, 48}, 0, 4, 0, 0.2f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Sonic_Running_Right_90");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Running_Right_90");
		fb->SetInfo({ texture, L"FB_Running_Right_90", {48, 37}, 0, 4, 0, 0.1f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Sonic_Running_Right_135");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Running_Right_135");
		fb->SetInfo({ texture, L"FB_Running_Right_135", {42, 48}, 0, 4, 0, 0.2f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Sonic_Running_Right_180");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Running_Right_180");
		fb->SetInfo({ texture, L"FB_Running_Right_180", {37, 48}, 0, 4, 0, 0.1f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Sonic_Running_Right_225");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Running_Right_225");
		fb->SetInfo({ texture, L"FB_Running_Right_225", {48, 42}, 0, 4, 0, 0.2f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Sonic_Running_Right_270");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Running_Right_270");
		fb->SetInfo({ texture, L"FB_Running_Right_270", {48, 37}, 0, 4, 0, 0.1f });
	}
	{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Sonic_Running_Right_315");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Running_Right_315");
		fb->SetInfo({ texture, L"FB_Running_Right_315", {42, 48}, 0, 4, 0, 0.2f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Sonic_Skiddling_Right");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Skiddling_Right");
		fb->SetInfo({ texture, L"FB_Skiddling_Right", {32, 48}, 0, 1, 0, 0.3f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Sonic_Skiddling_Left");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Skiddling_Left");
		fb->SetInfo({ texture, L"FB_Skiddling_Left", {32, 48}, 0, 1, 0, 0.3f });
	}

	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Sonic_Rolling");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Rolling");
		fb->SetInfo({ texture, L"FB_Rolling", {32, 48}, 0, 3, 0, 0.1f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Sonic_Sitting");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Sitting");
		fb->SetInfo({ texture, L"FB_Sitting", {32, 48}, 0, 0, 0, 3.0f });
	}


	_player = new Player();
	
	GET_SINGLE(EventManager)->SetEventActor(_player);
	BoxCollider* boxCollider = new BoxCollider();
		// 박스 콜라이더 
	{
		boxCollider->SetOwner(_player);
		boxCollider->SetSize(Vector(40, 40));
		boxCollider->SetCollisionLayerType(CLT_OBJECT);

		boxCollider->AddCollisionFlagLayer(CLT_WALL);
		boxCollider->AddCollisionFlagLayer(CLT_GROUND);
		GET_SINGLE(CollisionManager)->AddCollider(boxCollider);
		_player->AddComponent(boxCollider);
	}

	//{
	//	Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(L"mapview");
	//	GET_SINGLE(ResourceManager)->CreateSprite(L"mapview", tex, 0, 0, 0, 0);
	//	Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"mapview");
	//	SpriteActor* background = new SpriteActor();
	//
	//	const Vector size = sprite->GetSize();
	//
	//	// 포지션 변경 
	//	background->SetPos(Vector(size.x / 2, size.y / 2));
	//
	//	background->SetSprite(sprite);
	//
	//	_backgrounds.push_back(background);
	//}
#if 1

	Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(L"maptest4");
	GET_SINGLE(ResourceManager)->CreateSprite(L"maptest4", tex, 0, 0, 0, 0);
	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"maptest4");
		SpriteActor* background = new SpriteActor();

		const Vector size = sprite->GetSize();

		// 포지션 변경 
		background->SetPos(Vector(size.x/2, size.y/2));

		background->SetSprite(sprite);

		_backgrounds.push_back(background);
	}

	if(true)
	{
		Actor* test = new Actor();
		test->SetPos(Pos(830, 300));
		AccelObj* accObj = new AccelObj(Vector(1,0));
		{
			accObj->SetOwner(test);
			accObj->SetSize(Vector(50, 50));
			accObj->SetCollisionLayerType(CLT_GROUND);
			uint32 flag = 0;

			GET_SINGLE(CollisionManager)->AddCollider(accObj);
			test->AddComponent(accObj);
		}
		AddActor(test);
	}

	if (true)
	{
		Texture* loopTexture = GET_SINGLE(ResourceManager)->GetTexture(L"loop");
		GET_SINGLE(ResourceManager)->CreateSprite(L"loop", loopTexture, 0, 0, 0, 0);
		Sprite* loopSprite = GET_SINGLE(ResourceManager)->GetSprite(L"loop");
		SpriteActor* loopSpriteActor = new SpriteActor();

		const Vector lsize = loopSprite->GetSize();
		loopSpriteActor->SetPos(Vector(300, 400));
		loopSpriteActor->SetSprite(loopSprite);
		_backgrounds.push_back(loopSpriteActor);
		LoopCourse* loopCourse = new LoopCourse(Vector(300, 205), Vector(600), _player);
		GET_SINGLE(CourseManager)->AddCourse(loopCourse);
	}



#elif 0
	Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(L"maptest1");
	GET_SINGLE(ResourceManager)->CreateSprite(L"maptest1", tex, 0, 0, 0, 0);
	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"maptest1");
		SpriteActor* background = new SpriteActor();
		
		const Vector size = sprite->GetSize();

		background->SetPos(Vector(size.x / 2, size.y / 2));
		background->SetSprite(sprite);
		_backgrounds.push_back(background);		
	}

	Actor* test = new Actor();
	test->SetPos(Pos(830, 300));
	AccelObj* accObj = new AccelObj(Vector(1, 1));
	{
		accObj->SetOwner(test);
		accObj->SetSize(Vector(50, 50));
		accObj->SetCollisionLayerType(CLT_GROUND);
		uint32 flag = 0;

		GET_SINGLE(CollisionManager)->AddCollider(accObj);
		test->AddComponent(accObj);
	}
	AddActor(test);
#else 
	Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(L"fuck");
	GET_SINGLE(ResourceManager)->CreateSprite(L"fuck", tex, 0, 0, 0, 0);
	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"fuck");
		SpriteActor* background = new SpriteActor();

		const Vector size = sprite->GetSize();

		// 포지션 변경 
		background->SetPos(Vector(size.x / 2, size.y / 2));

		background->SetSprite(sprite);

		_backgrounds.push_back(background);

	}
#endif


	if(true)
	{
		LoopCourse* loopCourse = new LoopCourse(Vector(4505, 790), Vector(600), _player);
		GET_SINGLE(CourseManager)->AddCourse(loopCourse);
	}
	else 
	{
		PipeCourse* pipeCourse = new PipeCourse(Vector(582, 459), Vector(304, 548), _player);
		Vector info[2] = { Vector(442, 282), Vector(732, 600) };
		pipeCourse->SetSensorsInfo(info, Vector(2),450);
		GET_SINGLE(CourseManager)->AddCourse(pipeCourse);
	}
	
	_player->SetBackGround(tex);
	AddActor(_player);
	_player->BeginPlay();
	//{
	//	Actor* test = new Actor();
	//	test->SetPos(Pos(500, 500));
	//	BoxCollider* boxCollider = new BoxCollider();
	//	{
	//		boxCollider->SetOwner(test);
	//		boxCollider->SetSize(Vector(100,100));
	//		boxCollider->SetCollisionLayerType(CLT_GROUND);
	//		uint32 flag = 0;
	//		
	//		GET_SINGLE(CollisionManager)->AddCollider(boxCollider);
	//		test->AddComponent(boxCollider);
	//	}
	//	AddActor(test);
	//}
	
	GET_SINGLE(CourseManager)->Init();
}

void DevScene::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->Get_deltaTime();
	
	GET_SINGLE(CollisionManager)->Update();

	for (Actor* actor : _actors)
 		actor->Tick();
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SPACE))
		exit(0);
	GET_SINGLE(CourseManager)->Update();

	//GET_SINGLE(EventManager)->Update();
}

void DevScene::Render(HDC hdc)
{
	Vector mousePos = GET_SINGLE(InputManager)->GetMousePos();
	for (Actor* actor : _backgrounds)
		actor->Render(hdc);
	for (Actor* actor : _actors)
		actor->Render(hdc);
}

void DevScene::RemoveActor(Actor* actor)
{

}

bool DevScene::RenderOnBackground(const wstring& key)
{
	Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(key);
	GET_SINGLE(ResourceManager)->CreateSprite(key, tex, 0, 0, 0, 0);
	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(key);
		SpriteActor* background = new SpriteActor();

		const Vector size = sprite->GetSize();

		// 포지션 변경 
		background->SetPos(Vector(size.x / 2, size.y / 2));

		background->SetSprite(sprite);

		_backgrounds.push_back(background);
	}
	return false;
}
