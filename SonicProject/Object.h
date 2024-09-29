#pragma once
enum class ObjectType
{
	NONE,
	PLAYER,
	MONSTER,
	PROJECTTILE

};
class Object
{
public : 
	Object();
	Object(ObjectType type);
	virtual ~Object();

	virtual void Init()		abstract;
	virtual void Update()	abstract;
	virtual void Render(HDC hdc)	abstract;

	ObjectType GetObjectType()	{ return _type; }
	Pos	 GetPos()				{ return _pos; }
	void SetPos(Pos pos)		{ _pos = pos; }

protected :
	ObjectType	_type = ObjectType::NONE;
	Pos			_pos = {};
	Stat		stat ={};
};