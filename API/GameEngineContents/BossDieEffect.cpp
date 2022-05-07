#include "BossDieEffect.h"
#include "RockmanUtility.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameManager.h"
#include "Player.h"
#include "RockmanStage.h"

BossDieEffect::BossDieEffect()
	:CenterRenderer_(nullptr),
	Speed_(180.0f),
	DeathTimer_(3.0f),
	IsDie_(false)
{
	for (int i = 0; i < 8; i++)
	{
		Dir8Renderer_[i] = nullptr;
	}

	for (int i = 0; i < 4; i++)
	{
		Dir4Renderer_[i] = nullptr;
	}

}

BossDieEffect::~BossDieEffect()
{
}

void BossDieEffect::Start()
{
	//사망 효과음
	GameEngineSound::SoundPlayOneShot("PlayerDeath.mp3");
	//플레이어 센터
	CenterRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Player));
	CenterRenderer_->CreateAnimation("Explosion.bmp", "Die", 0, 3, 0.1f, false);
	CenterRenderer_->SetTransColor(TransColor);
	CenterRenderer_->ChangeAnimation("Die");

	//4방향 벡터
	{
		Dir4Vector_[0] = float4::UP;
		Dir4Vector_[1] = float4::RIGHT;
		Dir4Vector_[2] = float4::DOWN;
		Dir4Vector_[3] = float4::LEFT;
	}

	//8방향 벡터
	{
		Dir8Vector_[0] = float4::UP;
		Dir8Vector_[1] = float4(1, -1);
		Dir8Vector_[1].Normal2D();
		Dir8Vector_[2] = float4::RIGHT;
		Dir8Vector_[3] = float4(1, 1);
		Dir8Vector_[3].Normal2D();
		Dir8Vector_[4] = float4::DOWN;
		Dir8Vector_[5] = float4(-1, 1);
		Dir8Vector_[5].Normal2D();
		Dir8Vector_[6] = float4::LEFT;
		Dir8Vector_[7] = float4(-1, -1);
		Dir8Vector_[7].Normal2D();
	}

	//4방향 렌더러
	{
		for (int i = 0; i < 4; i++)
		{
			Dir4Renderer_[i] = CreateRenderer(static_cast<int>(GameLayer::Player), RenderPivot::CENTER, Dir4Vector_[i] * 10);
			Dir4Renderer_[i]->CreateAnimation("Explosion.bmp", "Die", 0, 3, 0.07f, true);
			Dir4Renderer_[i]->SetTransColor(TransColor);
			Dir4Renderer_[i]->ChangeAnimation("Die");
		}
	}

	//8방향 렌더러
	{
		for (int i = 0; i < 8; i++)
		{
			Dir8Renderer_[i] = CreateRenderer(static_cast<int>(GameLayer::Player), RenderPivot::CENTER, Dir8Vector_[i] * 20);
			Dir8Renderer_[i]->CreateAnimation("Explosion.bmp", "Die", 0, 3, 0.07f, true);
			Dir8Renderer_[i]->SetTransColor(TransColor);
			Dir8Renderer_[i]->ChangeAnimation("Die");
		}
	}
}

void BossDieEffect::Update()
{
	if (CenterRenderer_->IsEndAnimation() == true)
	{
		CenterRenderer_->Off();
	}

	//4방향 렌더러를 멀리멀리 가게
	for (int i = 0; i < 4; i++)
	{
		Dir4Renderer_[i]->SetPivot(Dir4Renderer_[i]->GetPivot() + Dir4Vector_[i] * Speed_ * GameEngineTime::GetDeltaTime());
	}

	for (int i = 0; i < 8; i++)
	{
		Dir8Renderer_[i]->SetPivot(Dir8Renderer_[i]->GetPivot() + Dir8Vector_[i] * Speed_ * 2.5f * GameEngineTime::GetDeltaTime());
	}

	DeathTimer_ -= GameEngineTime::GetDeltaTime();
	if (DeathTimer_ <= 0 && IsDie_ == false)
	{
		IsDie_ = true;
		Death();
	}
}
