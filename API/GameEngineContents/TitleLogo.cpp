#include "TitleLogo.h"
#include "RockManEnum.h"
#include "GameEngine/GameEngineRenderer.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include "GameManager.h"

TitleLogo::TitleLogo()
	:BackGroundRender_(nullptr),
	Time_(3.0f),
	IsPress_(false)
{
}

TitleLogo::~TitleLogo()
{
}

void TitleLogo::Start()
{
	BackGroundRender_ = CreateRenderer(static_cast<int>(GameLayer::Background), RenderPivot::LeftTop);
	BackGroundRender_->CreateAnimation("Title.bmp", "TitleAni", 0, 1, 0.13f);
	BackGroundRender_->ChangeAnimation("TitleAni");
	BackGroundRender_->PauseOn();
}

void TitleLogo::Update()
{
	//아무 키나 눌렸으면 타이틀 애니메이션이 실행되고, 3초 뒤 셀렉트 레벨로 진입한다.
	if (IsPress_ == false)
	{
		//내가 설정한 키중에 아무키나 눌렸으면
		if (GameEngineInput::GetInst()->IsPress("Jump") ||
			GameEngineInput::GetInst()->IsPress("MoveLeft") ||
			GameEngineInput::GetInst()->IsPress("MoveRight") 
			)
		{
			BackGroundRender_->PauseOff();
			IsPress_ = true;
		}
	}

	if (IsPress_ == true)
	{
		Time_ -= GameEngineTime::GetDeltaTime();
		if (Time_ <= 0)
		{
			GameManager::GetInst()->ChangeLevel("Stage1");
		}
	}
}
