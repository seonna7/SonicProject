#pragma once
#include "Component.h"
class BoxCollider;
class SphereCollider;
class Collider : public Component
{
public  :
	Collider() {};
	Collider(eColliderType type);
	~Collider();
	// Component을(를) 통해 상속됨
	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

	virtual bool CheckCollision(Collider* other);

	eColliderType GetColliderType() { return _colliderType; }

	void SetShowDebug(bool show) { _showDebug = show;}

	static bool CheckCollisionBoxToBox(BoxCollider* b1, BoxCollider* b2);
	static bool CheckCollisionSphereToSphere(SphereCollider* s1, SphereCollider* s2);
	static bool CheckCollisionSphereToBox(SphereCollider* s1, BoxCollider* b1);

	unordered_set<Collider*>& GetCollisionMap() { return _collisionMap; }

	void SetCollisionLayerType(COLLISION_LAYER_TYPE type) { _collisionLayer = type; }
	COLLISION_LAYER_TYPE GetCollisonLayerType() { return _collisionLayer;}

	void SetCollisionFlag(uint32 flag) { _collisionFlag = flag; }
	uint32 GetCollisionFlag() { return _collisionFlag; }
	
	void ResetCollisionFlag() { _collisionFlag = 0; }
	void AddCollisionFlagLayer(COLLISION_LAYER_TYPE layer);
	void RemoveCollisionFlagLayer(COLLISION_LAYER_TYPE layer);


protected  :
	eColliderType _colliderType;
	bool _showDebug = true; // 디버그 모드에서 보여줄지 판단 

public : 
	COLLISION_LAYER_TYPE _collisionLayer = COLLISION_LAYER_TYPE::CLT_OBJECT;
	
	unordered_set<Collider*> _collisionMap;

	// 충돌 오브젝트 허용에 대한 비트연산
	uint32 _collisionFlag = 0; 
};

