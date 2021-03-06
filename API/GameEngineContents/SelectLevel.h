#pragma once
#include <GameEngine/GameEngineLevel.h>

class SelectLevel : public GameEngineLevel
{
public:
	SelectLevel();
	~SelectLevel();


	SelectLevel(const SelectLevel& _Other) = delete;
	SelectLevel(const SelectLevel&& _Other) noexcept = delete;
	SelectLevel& operator=(const SelectLevel& _Ohter) = delete;
	SelectLevel& operator=(const SelectLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void Update() override;
};

