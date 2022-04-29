#pragma once
#include <GameEngine/GameEngineActor.h>

class Scoreboard : public GameEngineActor
{
public:
	Scoreboard();
	~Scoreboard();


	Scoreboard(const Scoreboard& _Other) = delete;
	Scoreboard(const Scoreboard&& _Other) noexcept = delete;
	Scoreboard& operator=(const Scoreboard& _Ohter) = delete;
	Scoreboard& operator=(const Scoreboard&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	GameEngineRenderer* ScoreNumberRenderer_[7];
	int NumberIndex[7];

};

