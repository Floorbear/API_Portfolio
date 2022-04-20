#pragma once

enum class PlayerState
{
	Idle,
	Move,
	Jump,
	Climb,
	Max
};

enum class GameLayer
{
	Background,
	Object,
	Monster,
	Bullet,
	Player,
	UI,
	Max
};

enum class BossName
{
	Cutman,
	Max
};

