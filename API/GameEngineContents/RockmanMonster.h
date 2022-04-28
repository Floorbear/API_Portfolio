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

public:
	inline int GetAttackDmg() const
	{
		return AttackDamage_;
	}

	void SetIndex(int _Index) //몬스터가 활동할 백그라운드의 Index
	{
		Index_ = _Index;
	}

	void SetSpawnPos(const float4& _Pos)
	{
		SpawnPos_ = _Pos;
		SetPosition(_Pos);
	}

protected:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void InitMonster(); //몬스터의 스텟 파라미터를 초기화하는 함수
	virtual void InitRenderer(); //몬스터의 렌더러를 초기화하는 함수
	virtual void ChangeIdleAni(); //몬스터의 Idle애니메이션으로 체인지해주는 함수
	virtual void SetMonster(); //스타트 시점에 초기화 해주는 함수


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

	void DropItem(); //확률계산(아이템을 드랍할꺼냐 안할꺼냐)을해서 아이템을 드랍하는 함수

private:
	//스테이터스
	int CurHP_;
	int MaxHP_;
	int AttackDamage_;

	//스폰 관련
	size_t Index_;
	float4 SpawnPos_;
	float4 DeletePos_;
	float Default_DeathTimer_;
	float DeathTimer_;
	bool CanActivate; //몬스터가 화면 안에 있으나, 활동을 정지하고 싶을 때

	float Default_Speed_;
	float Speed_;
	float AttackStartRange_; // 공격이 시작하는 사정거리
	float VerSpeed_;


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

