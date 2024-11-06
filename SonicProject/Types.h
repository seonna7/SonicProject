#pragma once


using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;


extern uint32 GWinSizeX;
extern uint32 GWinSizeY;




struct Stat
{
	int32 _hp	 = 0; 
	int32 _maxhp = 0;
	float _speed = 0; 
};

struct Vector
{
	Vector() {}
	Vector(float len) : x(len), y(len) {}
	Vector(float x, float y) : x(x), y(y) {}
	Vector(POINT p) : x((float)p.x), y((float)p.y) {}

	Vector operator + (const Vector& other)
	{
		Vector ret;
		ret.x = x + other.x;
		ret.y = y + other.y;
		return ret;
	}

	Vector operator - (const Vector& other)
	{
		Vector ret;
		ret.x = x - other.x;
		ret.y = y - other.y;
		return ret;
	}
	
	Vector operator*(float value)
	{
		Vector ret;
		ret.x = x * value;
		ret.y = y * value;
		return ret;
	}

	Vector operator/(float value)
	{
		Vector ret;
		ret.x = x / value;
		ret.y = y / value;
		return ret;
	}

	bool operator == (Vector other)
	{
		return this->x == other.x && this->y == other.y;
	}

	void operator+=(const Vector& other)
	{
		x += other.x;
		y += other.y;
	}
	void operator-=(const Vector& other)
	{
		x -= other.x;
		y -= other.y;
	}
	void operator*=(float value)
	{
		x *= value;
		y *= value;
	}
	void operator/=(float value)
	{
		x /= value;
		y /= value;
	}

	float LengthSquared()
	{
		return x * x + y * y;
	}

	float Length()
	{
		//sqrt 비용이 크므로 크기 비교는 squared로 진행한다.

		return ::sqrt(LengthSquared());
	}

	void Normalize()
	{
		float len =  Length();
		if (len < 0.00000001f)
			return;
		x /= len;
		y /= len;
	}
	
	float Dot(Vector other)
	{
		return x * other.x + y * other.y;
	}

	float Cross(Vector other)
	{
		return x * other.y - other.x * y;
	}

	float x;
	float y;


};
using Pos = Vector;	


struct Pixel
{
	Pixel(BYTE R, BYTE G, BYTE B, BYTE A) :
		R(R), G(G), B(B), A(A) {}
	BYTE R;
	BYTE G;
	BYTE B;
	BYTE A;
};

struct MyDegree
{
	MyDegree() {};
	MyDegree(float degree) : _myDegree(degree) { ConvertMyDegreeToWinDegree(); };
	float _myDegree = 0.f;
	float _WindowDegree = 0.f;

	void operator+=(float value) { _WindowDegree -= value; _myDegree += value;}
	void operator-=(float value) { _WindowDegree += value; _myDegree -= value;}

	MyDegree operator= (float &degree)
	{
		MyDegree ret = {};
		ret._myDegree = degree;
		ret._WindowDegree = 450 - ret._myDegree;
		return ret;
	}
	MyDegree operator+(float &degree)
	{
		MyDegree ret = {};
		ret._myDegree = _myDegree - degree;
		ret._WindowDegree = 450 - ret._myDegree - degree;
		return ret;
	}

	MyDegree operator-(float degree)
	{
		MyDegree ret = {};
		ret._myDegree = _myDegree + degree;
		ret._WindowDegree = 450 - ret._myDegree + degree;
		return ret;
	}


	void ConvertMyDegreeToWinDegree()
	{
		_WindowDegree = 450 - _myDegree;
	}

};