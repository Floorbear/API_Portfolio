#pragma once

enum class PlayerState
{
	Idle,
	Move,
	Jump,
	Climb,
	Hit,
	Die,
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

enum class MonsterState
{
	Chase,
	Attack,
	Max
};

enum class BulletType
{
	Normal,
	Max
};

