#pragma once
#include "RockmanMonster.h"

class OctopusBattery : public RockmanMonster
{
public:
	OctopusBattery();
	~OctopusBattery();

	OctopusBattery(const OctopusBattery& _Other) = delete;
	OctopusBattery(const OctopusBattery&& _Other) noexcept = delete;
	OctopusBattery& operator=(const OctopusBattery& _Ohter) = delete;
	OctopusBattery& operator=(const OctopusBattery&& _Other) noexcept = delete;

	void SetDir(bool _IsVerType) //True : VerType, False : HoriType_
	{
		if (_IsVerType == true)
		{
			IsVerType_ = true;
		}
		else
		{
			IsHoriType_ = true;
		}
	}

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
	float CurIdleTime_;
	float MaxIdleTime_;//Idle상태가 지속되는 시간

	bool IsVerType_;
	bool IsHoriType_;

	float4 MoveDir_;
};

