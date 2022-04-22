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
	void ChangeBackground(BackgroundDir _Dir, const float4& _MoveDir); //_Dir : 이동하고 싶은 백그라운드가 이전, 다음인지를 셋팅, _MoveDir : 이동하고 싶은 백그라운드가 위, 아래에 있는지 셋팅

protected:
	virtual void Loading() override;
	virtual void Update() override;
	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	virtual void InitColPosNScale() = 0;

private:

protected:
	int CurBackgroundIndex_;
	int MaxBackgroundIndex_;
	GameEngineSoundPlayer Bgm_;
	//std::vector<GameEngineImage*> AllBackgroundImages_;
	//std::vector<GameEngineImage*> AllBackgroundColImages_;
	std::vector<BackGround*> AllBackground_;
	std::vector<float4> AllMoveUPColPos_;
	std::vector<float4> AllMoveDOWNColPos_;
	std::vector<float4> AllMoveUPColScale_;
	std::vector<float4> AllMoveDOWNColScale_;
	std::vector<std::map<std::string,std::vector<float4>>> AllRockmanCol_;
};

