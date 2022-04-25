#pragma once
#include <GameEngine/GameEngineActor.h>
#include "RockManEnum.h"
class BunbyHeli : public GameEngineActor
{
public:
	BunbyHeli();
	~BunbyHeli();


	BunbyHeli(const BunbyHeli& _Other) = delete;
	BunbyHeli(const BunbyHeli&& _Other) noexcept = delete;
	BunbyHeli& operator=(const BunbyHeli& _Ohter) = delete;
	BunbyHeli& operator=(const BunbyHeli&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;

	//fsm
private:
	void ChangeState(MonsterState _State);
	void UpdateState();

	void ChaseStart();
	void ChaseUpdate();

	void AttackStart();
	void AttackUpdate();

private:
	MonsterState CurState_;
	GameEngineRenderer* MonsterRenderer_;
};

