#pragma once
#include "RockmanMonster.h"
class SuperCutter : public RockmanMonster
{
public:
	SuperCutter();
	~SuperCutter();


	SuperCutter(const SuperCutter& _Other) = delete;
	SuperCutter(const SuperCutter&& _Other) noexcept = delete;
	SuperCutter& operator=(const SuperCutter& _Ohter) = delete;
	SuperCutter& operator=(const SuperCutter&& _Other) noexcept = delete;

	void SetSuperCutter();

protected:
	void InitMonster() override;
	void InitRenderer() override;
	void ChangeIdleAni() override;
	void SetMonster() override;

	void IdleStart() override;
	void IdleUpdate() override;

private:
	float Gravity_;
	bool IsSet_;

};

