#pragma once
#include <GameEngine/GameEngineActor.h>
#include "RockManEnum.h"

class Player;
class RockmanMonster : public GameEngineActor
{
	//몬스터를 상속받은 액터가 오버라이드 해야 할 내용 : InitMonster~SetCol , 몬스터의 사망 애니메이션의 이름은 무조건 Die
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

	virtual void SetDir(const float4& _Dir) {}; //CurDir을 변경하고 추가 조치를 취해주는 함수


protected:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void InitMonster() = 0; //몬스터의 스텟 파라미터를 초기화하는 함수
	virtual void InitRenderer() = 0; //몬스터의 렌더러를 생성하고, TransColor를 지정해주고,  애니메이션을 생성하고, 초기 애니메이션으로 Change해주는 함수
	virtual void ChangeIdleAni() = 0; //몬스터의 Idle애니메이션으로 체인지해주는 함수
	virtual void SetMonster() = 0; //스타트 시점에 실행되는 함수



	//fsm
protected:
	void ChangeState(MonsterState _State);
	void UpdateState();

	virtual void IdleStart() =0;
	virtual void IdleUpdate() = 0;

	virtual void AttackStart() {};
	virtual void AttackUpdate() {};

	virtual void MoveStart() {};
	virtual void MoveUpdate() {};

	virtual void JumpStart() {};
	virtual void JumpUpdate() { };

	virtual void Hit(BulletType _BulletType);
	void Die();
private:
	//Col Check
	void HitByBulletCheck(); //MonsterContactCol_에 총알이 닿았는지 확인하는 함수



	void DropItem(); //확률계산(아이템을 드랍할꺼냐 안할꺼냐)을해서 아이템을 드랍하는 함수


protected:
	//스테이터스
	int CurHP_;
	int MaxHP_;
	int AttackDamage_;
	int DropScore_; //이 몬스터가 죽을경우 얻는 점수

	//스폰 관련
	int Index_;
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

