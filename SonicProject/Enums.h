#pragma once

enum class KeyState
{
	None,
	Press,
	Down,
	Up,

	End
};

enum class KeyType
{
	MouseLeft = VK_LBUTTON,
	MouseRight = VK_RBUTTON,

	Up = VK_UP,
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
	P_LEFT = 0,
	P_RIGHT = 1,
	P_BOTTOM = 0,
	P_TOP = 1,
};

namespace ColorRef
{
	static COLORREF RED			= RGB(255, 0, 0);
	static COLORREF GREEN		= RGB(0, 255, 0);
	static COLORREF BLUE		= RGB(0, 0, 255);
	static COLORREF MANGENTA	= RGB(255, 0, 255);
	static COLORREF CYAN		= RGB(0, 255, 255);
	static COLORREF BLACK		= RGB(0, 0, 0);
};