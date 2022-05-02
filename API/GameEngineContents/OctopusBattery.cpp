#include "OctopusBattery.h"
#include "RockManEnum.h"
#include "RockmanUtility.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineDebug.h>
#include "BackGround.h"
#include "GameManager.h"

OctopusBattery::OctopusBattery()
{
}

OctopusBattery::~OctopusBattery()
{
}

void OctopusBattery::InitMonster()
{
	SetScale({ 60,60 });
	//�������ͽ�
	AttackDamage_ = 5;

	DropScore_ = 300;

	CurState_ = MonsterState::Idle;

	Default_Speed_ = 400.0f;
	Speed_ = Default_Speed_;
	AttackStartRange_ = 200.0f;

	CurIdleTime_ = 0;
	MaxIdleTime_ = 1.3f;//Idle���°� ���ӵǴ� �ð�

	MoveDir_ = float4::ZERO;

	IsVerType_ = false;
	IsHoriType_ = false;

	Default_DeathTimer_ = 1.0f;
	DeathTimer_ = Default_DeathTimer_;
	MaxHP_ = 5;
	CurHP_ = MaxHP_;

}

void OctopusBattery::InitRenderer()
{
	//������ �ִϸ��̼� ����
	MonsterRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Monster), RenderPivot::CENTER);
	MonsterRenderer_->SetTransColor(TransColor);
	MonsterRenderer_->CreateAnimation("OctopusBattery.bmp", "OctopusBattery_Idle", 0, 0, 0.1f,false);
	MonsterRenderer_->CreateAnimation("OctopusBattery.bmp", "OctopusBattery_Attack", 1, 2, 0.1f,false);

	//��� �ִϸ��̼�
	MonsterRenderer_->CreateAnimation("Explosion.bmp", "Die", 0, 4, 0.05f, false);

	MonsterRenderer_->ChangeAnimation("OctopusBattery_Idle");
}

void OctopusBattery::ChangeIdleAni()
{
	MonsterRenderer_->ChangeAnimation("OctopusBattery_Idle");
}

void OctopusBattery::SetMonster()
{
	MonsterContactCol_ = CreateCollision("MonsterCol", GetScale());
}

void OctopusBattery::IdleStart()
{
	CurIdleTime_ = 0;
	MonsterRenderer_->ChangeAnimation("OctopusBattery_Idle");
}

void OctopusBattery::IdleUpdate()
{
	CurIdleTime_ += GameEngineTime::GetDeltaTime();
	if (CurIdleTime_ >= MaxIdleTime_)
	{
		ChangeState(MonsterState::Attack);
		return;
	}

}

void OctopusBattery::AttackStart()
{
	MonsterRenderer_->ChangeAnimation("OctopusBattery_Attack");
	BackGround* CurrentBackground = GameManager::GetInst()->GetCurrentBackGround();
	if (IsVerType_ == true)
	{
		float4 CheckVerPos = GetPosition() + float4(0, GetScale().Half().y);
		//�Ʒ����� ���������� �������� �̵�
		if (CurrentBackground->IsBlocked(float4(CheckVerPos)) == true)
		{
			MoveDir_ = float4::UP;
		}
		else
		{
			MoveDir_ = float4::DOWN;
		}
	}
	else if (IsHoriType_ == true)
	{
		float4 CheckSidePos = GetPosition() + float4(GetScale().Half().x, 0);
		if (CurrentBackground->IsBlocked(float4(CheckSidePos)) == true)//�������� ���������� �������� �̵�
		{
			MoveDir_ = float4::LEFT;
		}
		else
		{
			MoveDir_ = float4::RIGHT;
		}
	}
}

void OctopusBattery::AttackUpdate()
{
	BackGround* CurrentBackground = GameManager::GetInst()->GetCurrentBackGround();

	float4 CheckPos = GetPosition() + MoveDir_ * 28;
	if (CurrentBackground->IsBlocked(float4(CheckPos)) == true)
	{
		ChangeState(MonsterState::Idle);
		return;
	}
	else
	{
		SetMove(MoveDir_ * Speed_ * GameEngineTime::GetDeltaTime());
	}

}
