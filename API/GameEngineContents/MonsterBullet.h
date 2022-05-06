#pragma once
#include <GameEngine/GameEngineActor.h>
#include "RockManEnum.h"

class Cutman;
class MonsterBullet : public GameEngineActor
{
public:
	MonsterBullet();
	~MonsterBullet();


	MonsterBullet(const MonsterBullet& _Other) = delete;
	MonsterBullet(const MonsterBullet&& _Other) noexcept = delete;
	MonsterBullet& operator=(const MonsterBullet& _Ohter) = delete;
	MonsterBullet& operator=(const MonsterBullet&& _Other) noexcept = delete;

public:
	void SetBullet(const float4& _Pos, const float4& _Dir,int _Dmg ,MonsterBulletType _BulletType = MonsterBulletType::Red);
	inline MonsterBulletType GetBulletType() const
	{
		return Type_;
	}

	inline int GetBulletDmg()
	{
		return Dmg_;
	}

	inline void SetCutman(Cutman* _Cutman)
	{
		Cutman_ = _Cutman;
	}

	inline bool GetIsReturn()
	{
		return IsReturn_;
	}



protected:
	void Start() override;
	void Update() override;

private:
	bool HaveDir_;
	float DeathTime_;
	float Speed_;
	int Dmg_;
	float4 Dir_;
	MonsterBulletType Type_;

	GameEngineRenderer* Renderer_;


	//ÄÆ¸Ç¿ë
	Cutman* Cutman_;
	bool IsReturn_;
	float4 StartPos_;

};


