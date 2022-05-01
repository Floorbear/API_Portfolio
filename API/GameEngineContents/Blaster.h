#pragma once
#include "RockmanMonster.h"

class Blaster : public RockmanMonster
{
public:
	Blaster();
	~Blaster();


	Blaster(const Blaster& _Other) = delete;
	Blaster(const Blaster&& _Other) noexcept = delete;
	Blaster& operator=(const Blaster& _Ohter) = delete;
	Blaster& operator=(const Blaster&& _Other) noexcept = delete;

	void SetDir(const float4& _Dir) override;

protected:
	void InitMonster() override;
	void InitRenderer() override;
	void ChangeIdleAni() override;
	void SetMonster() override;

	void IdleStart() override;
	void IdleUpdate() override;

	void AttackStart() override;
	void AttackUpdate() override;

	void Hit(BulletType _BulletType) override;

private:
	float CurIdleTime_;
	float DefaultIdleTime_;//Idle상태가 지속되는 시간

	int MaxAttackCount_;
	int CurAttackCount_;
	float CurAttackTickTime_;
	float MaxAttackTickTime_;
};

