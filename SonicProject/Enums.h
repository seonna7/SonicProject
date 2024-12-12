#pragma once

enum class KeyState
{
	None,
	Press,
	Down,
	UP,

	End
};

enum class KeyType
{
	MouseLeft = VK_LBUTTON,
	MouseRight = VK_RBUTTON,

	UP = VK_UP,
	DOWN = VK_DOWN,
	LEFT = VK_LEFT,
	RIGHT = VK_RIGHT,
	SPACE = VK_SPACE,

	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',

	Q = 'Q',
	E = 'E'
};

enum
{
	e_Pixel_Len = 15	
};

enum class eSceneType
{
	NONE,
	DEVSCENE,
	GAMESCENE,
	EDITSCENE
};

enum class eColliderType : uint8
{
	BOX,
	SPHERE,
	PIXEL,
	LOOP,
	BACKGROUND
};

enum class eComponentType : uint8
{
	NONE,
	CAMERA,
	RIGIDBODY,
	BOX_COLLIDER,
	SPHERE_COLLIDER,
	PIXEL_COLLIDER,
	LOOP,
	BACKGROUND_COLLIDER,
};
enum class ePixelColliderType : uint8
{
	CEILING,
	GROUND,
	PUSH,
	WALL,
	CLIFF,
};

enum COLLISION_LAYER_TYPE
{
	CLT_OBJECT,
	CLT_GROUND,
	CLT_WALL
};


enum class ePixelDirection : uint8
{
	P_LEFT = 1,
	P_RIGHT = 2,
	P_BOTTOM = 4,
	P_TOP = 8
};

namespace ColorRef
{
	static COLORREF WHITE		= RGB(255, 255, 255);
	static COLORREF RED			= RGB(255, 0, 0);
	static COLORREF GREEN		= RGB(0, 255, 0);
	static COLORREF BLUE		= RGB(0, 0, 255);
	static COLORREF MAGENTA		= RGB(255, 0, 255);
	static COLORREF CYAN		= RGB(0, 255, 255);
	static COLORREF BLACK		= RGB(0, 0, 0);
};


enum class eCourse
{
	NONE = 0,
	LOOP,
	PIPE,
};