#pragma once
#include <GameEngine/GameEngineActor.h>
#include "RockManEnum.h"

class Player;
class RockmanMonster : public GameEngineActor
{
public:
	RockmanMonster();
	~RockmanMonster();


	RockmanMonster(const RockmanMonster& _Other) = delete;
	RockmanMonster(const RockmanMonster&& _Other) noexcept = delete;
	RockmanMonster& operator=(const RockmanMonster& _Ohter) = delete;
	RockmanMonster& operator=(const RockmanMonster&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void InitMonster();
	virtual void InitRenderer();
	virtual void SetMonster();

	//fsm
protected:
	void ChangeState(MonsterState _State);
	void UpdateState();

	void ChaseStart();
	void ChaseUpdate();

	void AttackStart();
	void AttackUpdate();

private:
	//Col Check
	void HitByBulletCheck();

	void Hit(BulletType _BulletType);
	void Die();

private:
	size_t Index_;
	float DeathTimer_;

	float Default_Speed_;
	float Speed_;
	float AttackStartRange_; // 공격이 시작하는 사정거리
	float VerSpeed_;

	int CurHealth_;
	int MaxHealth_;

	float4 WantHoriDir_;
	float4 CurHoriDir_;

	float4 InitVerDir_;
	float4 CurVerDir_;

	float4 AttackPos_;
	float4 AttackStartPos_;

	std::string StateStr_[static_cast<int>(MonsterState::Max)];
	MonsterState CurState_;

	GameEngineCollision* MonsterContactCol_;
	GameEngineRenderer* MonsterRenderer_;
	Player* Player_;
};

