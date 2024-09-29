#pragma once
class Collider;

class CollisionManager
{
	CREATE_SINGLE(CollisionManager);

public : 
	void Init();
	void Update();

	void AddCollider(Collider* collider);
	void RemoveCollider(Collider* collider);
	
	bool Is_Src_Dst_SameOwner(Collider* c1, Collider* c2);


private : 
	vector<Collider*> _colliders;
};

