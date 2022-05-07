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

	//4���� ������
	GameEngineRenderer* Dir4Renderer_[4]; //0�� ��, �ð����
	//8���� ������
	GameEngineRenderer* Dir8Renderer_[8];

	//4���� ����
	float4 Dir4Vector_[4];

	//8���� ����
	float4 Dir8Vector_[8];

	float Speed_;

	bool IsDie_;
};

