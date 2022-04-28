#include "PlayerDieEffect.h"
#include "RockmanUtility.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameManager.h"
#include "Player.h"
#include "RockmanStage.h"

PlayerDieEffect::PlayerDieEffect()
	:CenterRenderer_(nullptr),
	Speed_(180.0f),
	LevelChangeTimer_(3.0f)
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

PlayerDieEffect::~PlayerDieEffect()
{
}

void PlayerDieEffect::Start()
{
	//플레이어 센터
	CenterRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Player));
	CenterRenderer_->CreateAnimation("RockMan_Die.bmp", "RockMan_Die", 0, 1, 0.1f, false);
	CenterRenderer_->SetTransColor(TransColor);
	CenterRenderer_->ChangeAnimation("RockMan_Die");

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
		Dir8Vector_[3] = float4(1,1);
		Dir8Vector_[3].Normal2D();
		Dir8Vector_[4] = float4::DOWN;
		Dir8Vector_[5] = float4(-1,1);
		Dir8Vector_[5].Normal2D();
		Dir8Vector_[6] = float4::LEFT;
		Dir8Vector_[7] = float4(-1,-1);
		Dir8Vector_[7].Normal2D();
	}

	//4방향 렌더러
	{
		for (int i = 0; i < 4; i++)
		{
			Dir4Renderer_[i] = CreateRenderer(static_cast<int>(GameLayer::Player), RenderPivot::CENTER, Dir4Vector_[i] * 10);
			Dir4Renderer_[i]->CreateAnimation("RockMan_Die.bmp", "RockMan_DieGo", 3, 4, 0.07f, true);
			Dir4Renderer_[i]->SetTransColor(TransColor);
			Dir4Renderer_[i]->ChangeAnimation("RockMan_DieGo");
		}
	}

	//8방향 렌더러
	{
		for (int i = 0; i < 8; i++)
		{
			Dir8Renderer_[i] = CreateRenderer(static_cast<int>(GameLayer::Player), RenderPivot::CENTER, Dir8Vector_[i] * 20);
			Dir8Renderer_[i]->CreateAnimation("RockMan_Die.bmp", "RockMan_DieGo", 3, 4, 0.07f, true);
			Dir8Renderer_[i]->SetTransColor(TransColor);
			Dir8Renderer_[i]->ChangeAnimation("RockMan_DieGo");
		}
	}
}

void PlayerDieEffect::Update()
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
		Dir8Renderer_[i]->SetPivot(Dir8Renderer_[i]->GetPivot() + Dir8Vector_[i] * Speed_*2.5f * GameEngineTime::GetDeltaTime());
	}

	LevelChangeTimer_ -= GameEngineTime::GetDeltaTime();
	if (LevelChangeTimer_ <= 0)
	{	
		RockmanStage* CurStage = dynamic_cast<RockmanStage*>(GetLevel());
		CurStage->PlayerRespawn();
		Death();
	}		
}
