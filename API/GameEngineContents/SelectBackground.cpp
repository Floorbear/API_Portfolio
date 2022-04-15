#include "SelectBackground.h"
#include "GameEngineContents/RockManEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include "GameManager.h"
#include "SelectLogo.h"
#include "SelectBossActor.h"

SelectBackground::SelectBackground()
	:BackgroundRenderer_(nullptr),
	Time_Decide_(1.5f),
	IsPress_(false),
	IsOn_(false)
{
}

SelectBackground::~SelectBackground()
{
}

void SelectBackground::Start()
{
	BackgroundRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Background), RenderPivot::LeftTop);
	BackgroundRenderer_->CreateFolderAnimation("SelectFolder", "SelectAni_Decide", 0, 1, 0.15f);
	BackgroundRenderer_->CreateFolderAnimation("SelectFolder", "SelectAni_Fliker_Cutman", 2, 3, 0.3f);
	BackgroundRenderer_->ChangeAnimation("SelectAni_Fliker_Cutman");
}

void SelectBackground::Update()
{


	if (IsPress_ == true)
	{
		Time_Decide_ -= GameEngineTime::GetDeltaTime();
		if (Time_Decide_ <= 0 && IsOn_ == false)//한번만 실행되게
		{
			BackgroundRenderer_->PauseOn();
			IsOn_ = true;
		}
	}

	if (GameEngineInput::GetInst()->IsPress("Jump")
		)
	{
		if (IsPress_ == false)
		{
			//1.5초정도 
			BackgroundRenderer_->ChangeAnimation("SelectAni_Decide");
			//컷맨 액터 생성 >> 이거나중에 콘텐츠 많아지면 바꿔야함
			SelectBossActor* BossActor = GetLevel()->CreateActor<SelectBossActor>(static_cast<int>(GameLayer::Object), "SelectBossActor");
			BossActor->InitSelectActor(BossName::Cutman);
			IsPress_ = true;
		}
	}
}
