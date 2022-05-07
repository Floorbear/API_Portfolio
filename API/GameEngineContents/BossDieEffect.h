#pragma once
#include <GameEngine/GameEngineActor.h>
#include "RockManEnum.h"
#include <GameEngine/GameEngineRenderer.h>


class BossDieEffect : public GameEngineActor
{
public:
	BossDieEffect();
	~BossDieEffect();


	BossDieEffect(const BossDieEffect& _Other) = delete;
	BossDieEffect(const BossDieEffect&& _Other) noexcept = delete;
	BossDieEffect& operator=(const BossDieEffect& _Ohter) = delete;
	BossDieEffect& operator=(const BossDieEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;

private:
	float DeathTimer_;

	GameEngineRenderer* CenterRenderer_;

	//4방향 렌더러
	GameEngineRenderer* Dir4Renderer_[4]; //0이 위, 시계방향
	//8방향 렌더러
	GameEngineRenderer* Dir8Renderer_[8];

	//4방향 벡터
	float4 Dir4Vector_[4];

	//8방향 벡터
	float4 Dir8Vector_[8];

	float Speed_;

	bool IsDie_;
};

