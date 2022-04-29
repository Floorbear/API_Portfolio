#pragma once
#include "RockmanMonster.h"
class BunbyHeli : public RockmanMonster
{
public:
	BunbyHeli();
	~BunbyHeli();


	BunbyHeli(const BunbyHeli& _Other) = delete;
	BunbyHeli(const BunbyHeli&& _Other) noexcept = delete;
	BunbyHeli& operator=(const BunbyHeli& _Ohter) = delete;
	BunbyHeli& operator=(const BunbyHeli&& _Other) noexcept = delete;

protected:
	void InitMonster() override;
	void InitRenderer() override;
	void ChangeIdleAni() override;
	void SetMonster() override;

	void IdleStart() override;
	void IdleUpdate() override;

	void AttackStart() override;
	void AttackUpdate() override;

};

