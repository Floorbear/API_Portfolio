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
	//스테이터스
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
	//렌더러 애니메이션 셋팅
	MonsterRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Monster), RenderPivot::CENTER);
	MonsterRenderer_->SetTransColor(TransColor);
	MonsterRenderer_->CreateAnimation("BunbyHeli_Left.bmp", "BunbyHeli_Left", 0, 1, 0.05f);
	MonsterRenderer_->CreateAnimation("BunbyHeli_Right.bmp", "BunbyHeli_Right", 0, 1, 0.05f);

	//사망 애니메이션
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
	//콜리전 생성
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

	//방향 전환이 일어난다면 애니메이션을 바꿔라
	if (WantHoriDir_.CompareInt2D(CurHoriDir_) == false)
	{
		if (WantHoriDir_.CompareInt2D(float4::ZERO) == false) //플레이어가 죽고 위치에 고정될때
		{
			MonsterRenderer_->ChangeAnimation("BunbyHeli_" + RockmanUtility::DirToStr(WantHoriDir_));
			CurHoriDir_ = WantHoriDir_;
		}
	}

	//사정거리 내에 도달하면 공격을 한다.
	float Distance = float4(Player_->GetPosition().x - GetPosition().x, 0).Len2D();
	if (Distance <= AttackStartRange_)
	{
		//Y축 거리차가 너무나면 공격을 중지한다.
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
	VerSpeed_ = InitVerDir_.Len2D() * 1.5f; // 초기 스피드

	InitVerDir_.Normal2D();

	CurVerDir_ = InitVerDir_;
}

void BunbyHeli::AttackUpdate()
{
	if (InitVerDir_.CompareInt2D(CurVerDir_) == true)
	{
		if (CurVerDir_.CompareInt2D(float4::UP) == true) //위로볼록 상태인 경우
		{
			if (GetPosition().y <= AttackPos_.y)
			{
				CurVerDir_ = -CurVerDir_;
			}
		}
		else if (CurVerDir_.CompareInt2D(float4::DOWN) == true) //아래로볼록 상태인 경우
		{
			if (GetPosition().y >= AttackPos_.y + 20.0f)
			{
				CurVerDir_ = -CurVerDir_;
			}
		}
	}

	//Vertical 방향전환이 일어난 상태에서 처음 공격 시작한 지점의 y좌표까지 도달한다면
	if (InitVerDir_.CompareInt2D(CurVerDir_) == false)
	{
		if (CurVerDir_.CompareInt2D(float4::UP) == true) //아래로볼록 상태인 경우
		{
			if (GetPosition().y <= AttackStartPos_.y)
			{
				ChangeState(MonsterState::Idle);
				return;
			}
		}
		else if (CurVerDir_.CompareInt2D(float4::DOWN) == true) //위로볼록 상태인 경우
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
