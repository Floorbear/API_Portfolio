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

	void SetIndex(int _Index) //���Ͱ� Ȱ���� ��׶����� Index
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
	virtual void InitMonster(); //������ ���� �Ķ���͸� �ʱ�ȭ�ϴ� �Լ�
	virtual void InitRenderer(); //������ �������� �ʱ�ȭ�ϴ� �Լ�
	virtual void ChangeIdleAni(); //������ Idle�ִϸ��̼����� ü�������ִ� �Լ�
	virtual void SetMonster(); //��ŸƮ ������ �ʱ�ȭ ���ִ� �Լ�


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

	void DropItem(); //Ȯ�����(�������� ����Ҳ��� ���Ҳ���)���ؼ� �������� ����ϴ� �Լ�

private:
	//�������ͽ�
	int CurHP_;
	int MaxHP_;
	int AttackDamage_;

	//���� ����
	size_t Index_;
	float4 SpawnPos_;
	float4 DeletePos_;
	float Default_DeathTimer_;
	float DeathTimer_;
	bool CanActivate; //���Ͱ� ȭ�� �ȿ� ������, Ȱ���� �����ϰ� ���� ��

	float Default_Speed_;
	float Speed_;
	float AttackStartRange_; // ������ �����ϴ� �����Ÿ�
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

