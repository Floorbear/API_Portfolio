#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineSound.h>

class BackGround;
class Stage1 : public GameEngineLevel
{
public:
	Stage1();
	~Stage1();


	Stage1(const Stage1& _Other) = delete;
	Stage1(const Stage1&& _Other) noexcept = delete;
	Stage1& operator=(const Stage1& _Ohter) = delete;
	Stage1& operator=(const Stage1&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	void InitBackground();

private:
	GameEngineSoundPlayer Bgm_;
	std::vector<GameEngineImage*> AllBackgroundImages_[2];
	std::vector<GameEngineImage*> AllBackgroundColImages_[2];
	std::vector<BackGround*> AllBackground_[2];
	
};

