#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include "RockmanUtility.h"
#include "RockManEnum.h"

class BossEntranceDoor : public GameEngineActor
{
public:
	BossEntranceDoor();
	~BossEntranceDoor();


	BossEntranceDoor(const BossEntranceDoor& _Other) = delete;
	BossEntranceDoor(const BossEntranceDoor&& _Other) noexcept = delete;
	BossEntranceDoor& operator=(const BossEntranceDoor& _Ohter) = delete;
	BossEntranceDoor& operator=(const BossEntranceDoor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;

private:
	void DoorColCheck();
	GameEngineRenderer* DoorRenderer_;
	GameEngineCollision* DoorCol_;


};

