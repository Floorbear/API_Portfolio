#include "BunbyHeli.h"
#include <GameEngine/GameEngineRenderer.h>
#include "RockmanUtility.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "Player.h"

BunbyHeli::BunbyHeli()
{
}

BunbyHeli::~BunbyHeli()
{
}

void BunbyHeli::InitMonster()
{
	SetScale({ 70,80 });
	//�������ͽ�
	AttackDamage_ = 3;//Default 3

	DropScore_ = 500;

	CurState_ = MonsterState::Idle;

	Default_Speed_ = 300.0f;
	Speed_ = Default_Speed_;
	AttackStartRange_ = 200.0f;

	Default_DeathTimer_ = 1.0f;
	DeathTimer_ = Default_DeathTimer_;
	MaxHP_ = 1;
	CurHP_ = MaxHP_;

}

void BunbyHeli::InitRenderer()
{
	//������ �ִϸ��̼� ����
	MonsterRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Monster), RenderPivot::CENTER);
	MonsterRenderer_->SetTransColor(TransColor);
	MonsterRenderer_->CreateAnimation("BunbyHeli_Left.bmp", "BunbyHeli_Left", 0, 1, 0.05f);
	MonsterRenderer_->CreateAnimation("BunbyHeli_Right.bmp", "BunbyHeli_Right", 0, 1, 0.05f);

	//��� �ִϸ��̼�
	MonsterRenderer_->CreateAnimation("Explosion.bmp", "Die", 0, 4, 0.05f, false);

	MonsterRenderer_->ChangeAnimation("BunbyHeli_Left");
}

void BunbyHeli::ChangeIdleAni()
{
	CurHoriDir_ = float4(Player_->GetPosition().x - GetPosition().x, 0);
	CurHoriDir_.Normal2D();
	MonsterRenderer_->ChangeAnimation("BunbyHeli_" + RockmanUtility::DirToStr(CurHoriDir_));
}

void BunbyHeli::SetMonster()
{
	//�ݸ��� ����
	MonsterContactCol_ = CreateCollision("MonsterCol", GetScale());
}

void BunbyHeli::IdleStart()
{
	SetPosition(float4(GetPosition().x, AttackStartPos_.y));
	Speed_ = Default_Speed_;
	CurHoriDir_ = float4(Player_->GetPosition().x - GetPosition().x, 0);
	CurHoriDir_.Normal2D();
	MonsterRenderer_->ChangeAnimation("BunbyHeli_" + RockmanUtility::DirToStr(CurHoriDir_));
}

void BunbyHeli::IdleUpdate()
{
	WantHoriDir_ = float4(Player_->GetPosition().x - GetPosition().x, 0);
	WantHoriDir_.Normal2D();

	//���� ��ȯ�� �Ͼ�ٸ� �ִϸ��̼��� �ٲ��
	if (WantHoriDir_.CompareInt2D(CurHoriDir_) == false)
	{
		if (WantHoriDir_.CompareInt2D(float4::ZERO) == false) //�÷��̾ �װ� ��ġ�� �����ɶ�
		{
			MonsterRenderer_->ChangeAnimation("BunbyHeli_" + RockmanUtility::DirToStr(WantHoriDir_));
			CurHoriDir_ = WantHoriDir_;
		}
	}

	//�����Ÿ� ���� �����ϸ� ������ �Ѵ�.
	float Distance = float4(Player_->GetPosition().x - GetPosition().x, 0).Len2D();
	if (Distance <= AttackStartRange_)
	{
		//Y�� �Ÿ����� �ʹ����� ������ �����Ѵ�.
		float DistanceY = float4(0, Player_->GetPosition().y - GetPosition().y).Len2D();
		if (DistanceY < 1200)
		{
			ChangeState(MonsterState::Attack);
			return;
		}
	}
	SetMove(CurHoriDir_ * Speed_ * GameEngineTime::GetDeltaTime());
}

void BunbyHeli::AttackStart()
{
	AttackPos_ = Player_->GetPosition();
	AttackStartPos_ = GetPosition();

	InitVerDir_ = float4(0, Player_->GetPosition().y - GetPosition().y);
	VerSpeed_ = InitVerDir_.Len2D() * 1.5f; // �ʱ� ���ǵ�

	InitVerDir_.Normal2D();

	CurVerDir_ = InitVerDir_;
}

void BunbyHeli::AttackUpdate()
{
	if (InitVerDir_.CompareInt2D(CurVerDir_) == true)
	{
		if (CurVerDir_.CompareInt2D(float4::UP) == true) //���κ��� ������ ���
		{
			if (GetPosition().y <= AttackPos_.y)
			{
				CurVerDir_ = -CurVerDir_;
			}
		}
		else if (CurVerDir_.CompareInt2D(float4::DOWN) == true) //�Ʒ��κ��� ������ ���
		{
			if (GetPosition().y >= AttackPos_.y + 20.0f)
			{
				CurVerDir_ = -CurVerDir_;
			}
		}
	}

	//Vertical ������ȯ�� �Ͼ ���¿��� ó�� ���� ������ ������ y��ǥ���� �����Ѵٸ�
	if (InitVerDir_.CompareInt2D(CurVerDir_) == false)
	{
		if (CurVerDir_.CompareInt2D(float4::UP) == true) //�Ʒ��κ��� ������ ���
		{
			if (GetPosition().y <= AttackStartPos_.y)
			{
				ChangeState(MonsterState::Idle);
				return;
			}
		}
		else if (CurVerDir_.CompareInt2D(float4::DOWN) == true) //���κ��� ������ ���
		{
			if (GetPosition().y >= AttackStartPos_.y)
			{
				CurVerDir_ = -CurVerDir_;
				ChangeState(MonsterState::Idle);
				return;
			}
		}
	}

	VerSpeed_ += VerSpeed_ * GameEngineTime::GetDeltaTime();
	Speed_ += 500.0f * GameEngineTime::GetDeltaTime();

	SetMove(float4(CurHoriDir_.x * Speed_ * GameEngineTime::GetDeltaTime(), CurVerDir_.y * VerSpeed_ * 1.1f * GameEngineTime::GetDeltaTime()));
}
