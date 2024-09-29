#include "pch.h"
#include "LineMesh.h"
#include "Utils.h"
#include <fstream>
void LineMesh::Save(wstring path)
{
	wofstream file;
	file.open(path);


	int32 maxX = INT32_MIN;
	int32 minX = INT32_MAX;
	int32 maxY = INT32_MIN;
	int32 minY = INT32_MAX;

	for (auto& line : _lines)
	{
		POINT from = line.first;
		POINT to = line.second;

		minX = min(min(minX, from.x), to.x);
		maxX = max(max(maxX, from.x), to.x);
		minY = min(min(minY, from.y), to.y);
		maxY = max(max(maxY, from.y), to.y);
	}

	int32 midX = (minX + maxX) / 2;
	int32 midY = (minY + maxY) / 2;

	file << static_cast<int32>(_lines.size()) << endl;
	for (auto& line : _lines)
	{
		POINT from = line.first;
		POINT to = line.second;

		from.x -= midX;
		to.x -= midX;
 

		wstring str = std::format(L"({0},{1})->({2},{3})", from.x, from.y, to.x, to.y);
		file << str << endl;
	}
	file.close();
}

void LineMesh::Load(wstring path)
{
	wifstream file;
	file.open(path);

	int32 lineCnt;
	file >> lineCnt;

	_lines.clear();

	for (int32 i = 0; i < lineCnt; i++)
	{
		POINT pt1;
		POINT pt2;

		wstring str;
		file >> str;

		::swscanf_s(str.c_str(), L"(%d,%d)->(%d,%d)", &pt1.x, &pt1.y, &pt2.x, &pt2.y);
		_lines.push_back(make_pair(pt1, pt2));
	}
	file.close();
}

void LineMesh::Render(HDC hdc,Pos pos) const 
{ 
	for (auto& line : _lines)
	{
		POINT pt1 = line.first;
		POINT pt2 = line.second;

		Pos pos1;
		pos1.x =pos.x + static_cast<float>(pt1.x);
		pos1.y =pos.y + static_cast<float>(pt1.y);

		Pos pos2;
		pos2.x = pos.x + static_cast<float>(pt2.x);
		pos2.y = pos.y + static_cast<float>(pt2.y);

		Utils::DrawLine(hdc, pos1, pos2);
	}
}
