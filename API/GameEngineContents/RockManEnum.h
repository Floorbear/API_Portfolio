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
	Monster,
	Object,
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
	Idle,
	Attack,
	Move,
	Jump,
	Hit,
	Max
};

enum class BulletType
{
	Normal,
	Max
};

enum class MonsterBulletType
{
	Red,
	Orange,
	CutmanBullet,
	Max
};

enum class ItemType
{
	SmallEnergy,
	BigEnergy,
	RedBonusBall,
	ClearItem,
	Max
};

