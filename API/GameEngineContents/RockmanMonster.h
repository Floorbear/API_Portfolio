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

	//fsm
protected:
	void ChangeState(MonsterState _State);
	void UpdateState();

	void ChaseStart();
	void ChaseUpdate();

	void AttackStart();
	void AttackUpdate();

private:
	float Speed_;
	float AttackStartRange_; // 공격이 시작하는 사정거리
	float VerSpeed_;
	float AttCoolTime_; //공격 쿨타임
	float CurAttTime_; // 공격하고 나서 흐르는 시간

	float4 WantHoriDir_;
	float4 CurHoriDir_;

	float4 InitVerDir_;
	float4 CurVerDir_;

	float4 AttackPos_;
	float4 AttackStartPos_;

	std::string StateStr_[static_cast<int>(MonsterState::Max)];
	MonsterState CurState_;

	GameEngineRenderer* MonsterRenderer_;
	Player* Player_;
};

