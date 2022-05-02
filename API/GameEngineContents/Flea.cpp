#include "Flea.h"
#include "RockmanUtility.h"
#include "RockManEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineDebug.h>
#include "BackGround.h"
#include "GameManager.h"
#include "Player.h"

Flea::Flea()
{
}

Flea::~Flea()
{
}

void Flea::InitMonster()
{
	SetScale({ 60,78 });
	//스테이터스
	AttackDamage_ = 2;//

	DropScore_ = 300;

	CurState_ = MonsterState::Idle;
	CurIdleWaitTime_ = 0;
	MaxIdleWaitTime_ = 1.0f;

	Default_Speed_ = 200.0f;
	Speed_ = Default_Speed_;
	AttackStartRange_ = 200.0f;


	Default_DeathTimer_ = 1.0f;
	DeathTimer_ = Default_DeathTimer_;
	MaxHP_ = 1;
	CurHP_ = MaxHP_;

}

void Flea::InitRenderer()
{
	//렌더러 애니메이션 셋팅
	MonsterRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Monster), RenderPivot::CENTER,{0,30});
	MonsterRenderer_->SetTransColor(TransColor);
	MonsterRenderer_->CreateAnimation("Flea.bmp", "Flea_Idle", 0, 0, 0.1f,false);
	MonsterRenderer_->CreateAnimation("Flea.bmp", "Flea_Jump", 1, 1, 0.1f,false);

	//사망 애니메이션
	MonsterRenderer_->CreateAnimation("Explosion.bmp", "Die", 0, 4, 0.05f, false);

	MonsterRenderer_->ChangeAnimation("Flea_Idle");
}

void Flea::ChangeIdleAni()
{
	MonsterRenderer_->ChangeAnimation("Flea_Idle");
}

void Flea::SetMonster()
{
	MonsterContactCol_ = CreateCollision("MonsterCol", GetScale());
}

void Flea::IdleStart()
{
	Speed_ = Default_Speed_;
	MonsterRenderer_->ChangeAnimation("Flea_Idle");
	CurIdleWaitTime_ = 0;
}

void Flea::IdleUpdate()
{
	CurIdleWaitTime_ += GameEngineTime::GetDeltaTime();
	if (CurIdleWaitTime_ >= MaxIdleWaitTime_)
	{
		ChangeState(MonsterState::Attack);
		return;
	}
}

void Flea::AttackStart()
{
	Gravity_ = -900;
	MonsterRenderer_->ChangeAnimation("Flea_Jump");
	CurHoriDir_ = float4(Player_->GetPosition().x - GetPosition().x, 0);
	Speed_ = CurHoriDir_.Len2D();
	CurHoriDir_.Normal2D();
}

void Flea::AttackUpdate()
{
	Gravity_ += 1900 * GameEngineTime::GetDeltaTime();
	Speed_ += Speed_ *0.9f* GameEngineTime::GetDeltaTime();



	BackGround* CurrentBackground = GameManager::GetInst()->GetCurrentBackGround();
	float4 CheckUpPos = GetPosition() + float4(0, -GetScale().Half().y);
	float4 CheckDownPos = GetPosition() + float4(0, GetScale().Half().y-10);
	float4 CheckSidePos = GetPosition() + float4(CurHoriDir_.x*GetScale().Half().x, 0);
	//윗쪽 픽셀 충돌 검사
	if (CurrentBackground->IsBlocked(CheckUpPos) == true)
	{
		Gravity_ = 0;
		//1픽셀 아래로
		SetMove(float4::DOWN);
	}

	//사이드
	if (CurrentBackground->IsBlocked(CheckSidePos) == false)
	{
		SetMove(CurHoriDir_ * Speed_ * GameEngineTime::GetDeltaTime());
	}

	//아랫쪽
	if (Gravity_ > 0) //떨어지고 있는상태 == Gravity가 >0 상태에서만 발판체크를 한다!
	{
		if (CurrentBackground->IsBlocked(CheckDownPos) == true)
		{
			ChangeState(MonsterState::Idle);
			return;
			
		}
	}
	SetMove(float4::DOWN * Gravity_ * GameEngineTime::GetDeltaTime());

}
