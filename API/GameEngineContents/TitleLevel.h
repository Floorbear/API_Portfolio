#pragma once
#include <GameEngine/GameEngineLevel.h>

class TitleLevel : public GameEngineLevel
{
public:
	TitleLevel();
	~TitleLevel();


	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(const TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Ohter) = delete;
	TitleLevel& operator=(const TitleLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update()	override;
	void LevelChangeStart() override;
	void LevelChangeEnd() override;
};

