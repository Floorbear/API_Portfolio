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

public:

	void PlayerRespawn();

public:
	//void ChangeBackground(BackgroundDir _Dir, const float4& _MoveDir); //_Dir : �̵��ϰ� ���� ��׶��尡 ����, ���������� ����, _MoveDir : �̵��ϰ� ���� ��׶��尡 ��, �Ʒ��� �ִ��� ����

protected:
	virtual void Loading() override;
	virtual void Update() override;
	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	virtual void InitColPosNScale() = 0;
	virtual void InitBackground() = 0;
	virtual void ConnectBackground() = 0;
	virtual void InitMonster() = 0;

private:
	bool IsPlayerSpawn_;

protected:
	GameEngineSoundPlayer Bgm_;
	std::vector<BackGround*> AllBackground_;

	BackGround* StartBackground_;

};

