#pragma once
#include <GameEngine/GameEngineActor.h>
#include "RockManEnum.h"
#include <GameEngineBase/GameEngineSound.h>

class SelectBossActor : public GameEngineActor
{
public:
	SelectBossActor();
	~SelectBossActor();


	SelectBossActor(const SelectBossActor& _Other) = delete;
	SelectBossActor(const SelectBossActor&& _Other) noexcept = delete;
	SelectBossActor& operator=(const SelectBossActor& _Ohter) = delete;
	SelectBossActor& operator=(const SelectBossActor&& _Other) noexcept = delete;
public:
	void InitSelectActor(BossName _BossName);
protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	BossName BossName_;
	GameEngineRenderer* Renderer_;
	float Gravity_;
	float AccGravity_;
	float Speed_;
	float Time_; //점프 애니메이션의 시간
	float IdleTime_;
	bool IsLand_;
	bool IsIdleEnd_;
	float SoundTime_; //사운드 지속 시간
	GameEngineSoundPlayer EnemyChosenSound_;
	
	

};

