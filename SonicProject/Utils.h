#pragma once

class Utils
{
public : 
	static void Drawtext(HDC hdc, Pos pos, const wstring& str);
	
	static void DrawRect(HDC hdc, Pos pos, int32 w, int32 h);
	
	static void DrawCircle(HDC hdc, Pos pos, int32 radius);
	
	static void DrawLine(HDC hdc, Pos from, Pos to);

	// °è»ê¿ë

	static float ConvertToMyDegreeValue(float degree);

	static float ConvertToStandardDegreValue(float degree);

	static float RadianToDegree(float radian);

	static float DegreeToRadian(float degree);
};

