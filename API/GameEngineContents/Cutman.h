#pragma once
#include "RockmanMonster.h"
class Cutman : public RockmanMonster
{
public:
	Cutman();
	~Cutman();


	Cutman(const Cutman& _Other) = delete;
	Cutman(const Cutman&& _Other) noexcept = delete;
	Cutman& operator=(const Cutman& _Ohter) = delete;
	Cutman& operator=(const Cutman&& _Other) noexcept = delete;
protected:
	void InitMonster() override;
	void InitRenderer() override;
	void ChangeIdleAni() override;
	void SetMonster() override;

	void IdleStart() override;
	void IdleUpdate() override;

	void MoveStart() override;
	void MoveUpdate() override;

	void JumpStart() override;
	void JumpUpdate() override;

private:
	bool CheckPixelCol(float4 _Dir, unsigned long _RGB, bool _CheckOnlyMid);
	void Move(float4 _Dir, float _Speed, unsigned long _RGB, bool _CheckOnlyMid);

private:
	//시간관련
	float CurIdleTime_;
	float MaxIdleTime_;

	float Gravity_;

	//void Hit(BulletType _BulletType) override;
};

