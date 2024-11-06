#pragma once
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <queue>
#include <string.h>
#include <cassert>
#include <functional>
#include "Types.h"
#include "Defines.h"
#include "Enums.h"
#include "Global.h"
#include <format>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

#pragma comment(lib,"msimg32.lib")

#define _CRTDEBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif



