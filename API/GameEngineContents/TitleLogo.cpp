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
	//�ƹ� Ű�� �������� Ÿ��Ʋ �ִϸ��̼��� ����ǰ�, 3�� �� ����Ʈ ������ �����Ѵ�.
	if (IsPress_ == false)
	{
		//���� ������ Ű�߿� �ƹ�Ű�� ��������
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
