#pragma once
#include "RockmanMonster.h"

class MonsterBullet;
class Cutman : public RockmanMonster
{
public:
	Cutman();
	~Cutman();


	Cutman(const Cutman& _Other) = delete;
	Cutman(const Cutman&& _Other) noexcept = delete;
	Cutman& operator=(const Cutman& _Ohter) = delete;
	Cutman& operator=(const Cutman&& _Other) noexcept = delete;

	inline int GetHP()
	{
		return CurHP_;
	}
protected:
	void Update() override;
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

	void AttackStart() override;
	void AttackUpdate() override;

	void HitStart() override;
	void HitUpdate() override;
	void HitByBulletCheck() override;
	void Hit(BulletType _BulletType, const float4& _BulletPos) override;
private:
	bool CheckPixelCol(float4 _Dir, unsigned long _RGB, bool _CheckOnlyMid);
	void Move(float4 _Dir, float _Speed, unsigned long _RGB, bool _CheckOnlyMid);
	void CutmanBulletCheck();

private:
	//시간관련
	float CurIdleTime_;
	float MaxIdleTime_;
	float AttackJudgmentTime_;
	float JumpAttackJudgmentTime_;
	float AttackStartWaitTime_;
	float AttackStartCoolTime_;
	float CurHitTime_;
	float CurBlinkTime_;

	float Gravity_;

	bool IsAttacking_;
	bool IsHitAlphaOn_;
	bool IsFirst_;
	std::string HaveWeaponStr_[2];

	//공격관련
	MonsterBullet* CurBullet_;

	GameEngineRenderer* HitEffect_Center_Renderer_;
	GameEngineRenderer* HitEffect_Top_Renderer_;

	//스테이터스
	float CurHPFloat_;

	//void Hit(BulletType _BulletType) override;
};

