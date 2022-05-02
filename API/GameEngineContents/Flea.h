#pragma once
#include "RockmanMonster.h"
class Flea : public RockmanMonster
{
public:
	Flea();
	~Flea();


	Flea(const Flea& _Other) = delete;
	Flea(const Flea&& _Other) noexcept = delete;
	Flea& operator=(const Flea& _Ohter) = delete;
	Flea& operator=(const Flea&& _Other) noexcept = delete;

protected:
	void InitMonster() override;
	void InitRenderer() override;
	void ChangeIdleAni() override;
	void SetMonster() override;

	void IdleStart() override;
	void IdleUpdate() override;

	void AttackStart() override;
	void AttackUpdate() override;

private:
	float Gravity_;
	float CurIdleWaitTime_;
	float MaxIdleWaitTime_;
};

