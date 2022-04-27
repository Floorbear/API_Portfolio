#pragma once
#include <GameEngine/GameEngineActor.h>
#include "RockManEnum.h"
#include <GameEngine/GameEngineRenderer.h>

class PlayerDieEffect : public GameEngineActor
{
public:
	PlayerDieEffect();
	~PlayerDieEffect();


	PlayerDieEffect(const PlayerDieEffect& _Other) = delete;
	PlayerDieEffect(const PlayerDieEffect&& _Other) noexcept = delete;
	PlayerDieEffect& operator=(const PlayerDieEffect& _Ohter) = delete;
	PlayerDieEffect& operator=(const PlayerDieEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;

private:
	float LevelChangeTimer_;

	GameEngineRenderer* CenterRenderer_;

	//4방향 렌더러
	GameEngineRenderer * Dir4Renderer_[4]; //0이 위, 시계방향
	//8방향 렌더러
	GameEngineRenderer* Dir8Renderer_[8];

	//4방향 벡터
	float4 Dir4Vector_[4];

	//8방향 벡터
	float4 Dir8Vector_[8];

	float Speed_;
};

