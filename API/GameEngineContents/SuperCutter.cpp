#include "SuperCutter.h"
#include <GameEngine/GameEngineRenderer.h>
#include "RockmanUtility.h"
#include "RockManEnum.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "Player.h"
#include "GameManager.h"

SuperCutter::SuperCutter()
{
}

SuperCutter::~SuperCutter()
{
}

void SuperCutter::SetSuperCutter()
{
	Player_ = GameManager::GetInst()->GetPlayer();
	if (Player_ == nullptr)
	{
		MsgBoxAssert("Player_ �� nullptr�Դϴ�");
	}
	ChangeIdleAni();
	Gravity_ = -800;
	Speed_ = float4(Player_->GetPosition().x - this->GetPosition().x, 0).Len2D();
	IsSet_ = true;
}

void SuperCutter::InitMonster()
{
	SetScale({ 70,80 });
	//�������ͽ�
	AttackDamage_ = 4;//Default

	DropScore_ = 500;

	CurState_ = MonsterState::Idle;

	Default_Speed_ = 100;
	Speed_ = Default_Speed_;
	AttackStartRange_ = 200.0f;

	//���� ���� �Ķ����
	IsSet_ = false;

	//���ݰ��� �Ķ����
	Default_DeathTimer_ = 1.0f;
	DeathTimer_ = Default_DeathTimer_;
	MaxHP_ = 5;
	CurHP_ = MaxHP_;
}

void SuperCutter::InitRenderer()
{
	//������ �ִϸ��̼� ����
	MonsterRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Monster), RenderPivot::CENTER);
	MonsterRenderer_->SetTransColor(TransColor);
	MonsterRenderer_->CreateAnimation("SuperCutter_Left.bmp", "SuperCutter_Left", 0, 1, 0.12f, true);
	MonsterRenderer_->CreateAnimation("SuperCutter_Right.bmp", "SuperCutter_Right", 0, 1, 0.12f, true);

	//��� �ִϸ��̼�
	MonsterRenderer_->CreateAnimation("Explosion.bmp", "Die", 0, 4, 0.05f, false);


	//�ִϸ��̼� ����
	MonsterRenderer_->ChangeAnimation("SuperCutter_Right");
}

void SuperCutter::ChangeIdleAni()
{
	CurHoriDir_ = float4(Player_->GetPosition().x - this->GetPosition().x, 0);
	CurHoriDir_.Normal2D();
	MonsterRenderer_->SetPivot({ static_cast<float>(-CurHoriDir_.x * 40),0 });
	MonsterRenderer_->ChangeAnimation("SuperCutter_" + RockmanUtility::DirToStr(CurHoriDir_));

}

void SuperCutter::SetMonster()
{
	//�ݸ��� ����
	MonsterContactCol_ = CreateCollision("MonsterCol", GetScale());
}

void SuperCutter::IdleStart()
{
	ChangeIdleAni();
}

void SuperCutter::IdleUpdate()
{
	if (IsSet_ == true)
	{
		Gravity_ += 2500 * GameEngineTime::GetDeltaTime();
		Speed_ += Speed_*0.8f * GameEngineTime::GetDeltaTime();
		SetMove(CurHoriDir_ * Speed_ * GameEngineTime::GetDeltaTime());
		SetMove(float4::DOWN * Gravity_ * GameEngineTime::GetDeltaTime());
	}
}
