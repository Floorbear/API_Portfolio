#pragma once
#include <GameEngine/GameEngineActor.h>
#include "RockManEnum.h"

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

};


