#pragma once
#include <GameEngine/GameEngineLevel.h>
class ClearLevel : public GameEngineLevel
{
public:
	ClearLevel();
	~ClearLevel();


	ClearLevel(const ClearLevel& _Other) = delete;
	ClearLevel(const ClearLevel&& _Other) noexcept = delete;
	ClearLevel& operator=(const ClearLevel& _Ohter) = delete;
	ClearLevel& operator=(const ClearLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void Update() override;

};

