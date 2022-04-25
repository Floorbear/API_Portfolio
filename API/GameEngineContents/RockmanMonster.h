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
	MonsterState CurState_;
	GameEngineRenderer* MonsterRenderer_;
	Player* Player_;
};

