#pragma once
#include "RockmanMonster.h"
class SuperCutterSpawner : public RockmanMonster
{
public:
	SuperCutterSpawner();
	~SuperCutterSpawner();


	SuperCutterSpawner(const SuperCutterSpawner& _Other) = delete;
	SuperCutterSpawner(const SuperCutterSpawner&& _Other) noexcept = delete;
	SuperCutterSpawner& operator=(const SuperCutterSpawner& _Ohter) = delete;
	SuperCutterSpawner& operator=(const SuperCutterSpawner&& _Other) noexcept = delete;

protected:
	void InitMonster() override;
	void InitRenderer() override;
	void ChangeIdleAni() override;
	void SetMonster() override;

	void IdleStart() override;
	void IdleUpdate() override;

private:
	float CurAttackTickTime_;
	float MaxAttackTickTime_;

};

