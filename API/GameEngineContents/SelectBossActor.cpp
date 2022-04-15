#include "SelectBossActor.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "SelectLogo.h"

SelectBossActor::SelectBossActor()
	:Time_(1.5f),
	Gravity_(0),
	AccGravity_(0),
	Speed_(0),
	IsLand_(false),
	BossName_(BossName::Max),
	IdleTime_(2.0f),
	IsIdleEnd_(false),
	Renderer_(nullptr)
{
}

SelectBossActor::~SelectBossActor()
{
}

void SelectBossActor::InitSelectActor(BossName _BossName)
{
	switch (_BossName)
	{
	case BossName::Cutman:
		SetPosition({ 390,180 });
		Gravity_ = -480;
		AccGravity_ = 940;
		Speed_ = 0;
		IdleTime_ = 1.9f;
		BossName_ = BossName::Cutman;
		Renderer_->CreateAnimation("Cutman_right.bmp", "Cutman_Jump_Right", 5, 5, 1, false);
		Renderer_->CreateAnimation("Cutman_right.bmp", "Cutman_Idle_Right", 0, 1, 0.1, true);
		Renderer_->ChangeAnimation("Cutman_Jump_Right");
		break;
	default:
		break;
	}
}

void SelectBossActor::Start()
{
	SetScale({100, 100});
	//�Ƹ� ��ġ
	Renderer_ = CreateRenderer(static_cast<int>(GameLayer::Object), RenderPivot::CENTER);
	Renderer_->SetTransColor(RGB(255,255,255));
}

void SelectBossActor::Update()
{
	Time_ -= GameEngineTime::GetDeltaTime();
	//��ǥ���� �̵�
	if (Time_ >= 0 && IsLand_ == false)
	{
		Gravity_ += AccGravity_ * GameEngineTime::GetDeltaTime();
		SetMove(float4::RIGHT * Speed_ * GameEngineTime::GetDeltaTime());
		SetMove(float4::DOWN * Gravity_ * GameEngineTime::GetDeltaTime());
	}

	//�����ϰ� ���� �ϴ� �ִϸ��̼�
	if (Time_ <= 0 && IsLand_ == false)
	{
		switch (BossName_)
		{
		case BossName::Cutman:
			Renderer_->ChangeAnimation("Cutman_Idle_Right");
			break;
		default:
			break;
		}
		IsLand_ = true;
	}

	//�����ϰ� ���� �ϴ� �ִϸ��̼� ���ӽð�
	if (IdleTime_ >= 0 && IsLand_ == true)
	{
		IdleTime_ -= GameEngineTime::GetDeltaTime();
	}
	else if (IdleTime_ <= 0 && IsIdleEnd_ == false) //�ð��� �� �Ǹ� Idle�ִϸ��̼� ���� �� �ΰ� ����
	{
		Renderer_->PauseOn();
		GetLevel()->CreateActor<SelectLogo>(static_cast<int>(GameLayer::Object), "SelectLogo");
		IsIdleEnd_ = true;
	}
}

void SelectBossActor::Render()
{
}

