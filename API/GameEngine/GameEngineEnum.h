#pragma once

enum class RenderPivot
{
	LeftTop,
	CENTER,
	BOT,
};

enum class RenderScaleMode
{
	Image,
	User,
};

enum class CollisionType
{
	Point,
	Circle,
	Rect,
	Max //배열의 초기화를 위해 사용됨
};

enum class EngineMax
{
	RENDERORDERMAX = 2147483647,
};

