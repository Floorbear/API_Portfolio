#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineSound.h>
#include "RockManEnum.h"

class BackGround;
class RockmanStage : public GameEngineLevel
{
public:
	RockmanStage();
	~RockmanStage();


	RockmanStage(const RockmanStage& _Other) = delete;
	RockmanStage(const RockmanStage&& _Other) noexcept = delete;
	RockmanStage& operator=(const RockmanStage& _Ohter) = delete;
	RockmanStage& operator=(const RockmanStage&& _Other) noexcept = delete;

	inline 	std::vector<BackGround*> GetAllBackground() const
	{
		return AllBackground_;
	}

public:

public:
	GameEngineSoundPlayer Bgm_;

protected:
	virtual void Loading() override;
	virtual void Update() override;
	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	virtual void InitColPosNScale() = 0;
	virtual void InitBackground() = 0;
	virtual void ConnectBackground() = 0;
	virtual void InitMonster() = 0;

	void UserResetEnd() override;

private:
	bool IsPlayerSpawn_;

protected:

	std::vector<BackGround*> AllBackground_;

	BackGround* StartBackground_;

};

