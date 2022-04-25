#include "RockmanMonster.h"
#include <GameEngine/GameEngineRenderer.h>
#include "RockmanUtility.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameManager.h"
#include "Player.h"

RockmanMonster::RockmanMonster()
	:MonsterRenderer_(nullptr),
	CurState_(MonsterState::Chase),
	Player_(nullptr),
	CurHoriDir_(float4::ZERO),
	WantHoriDir_(float4::ZERO),
	Speed_(100.0f),
	AttackStartRange_(200.0f),
	AttCoolTime_(0.8f),
	CurAttTime_(0.0f)
{
	StateStr_[static_cast<int>(MonsterState::Chase)] = "Chase";
	StateStr_[static_cast<int>(MonsterState::Attack)] = "Attack";
}

RockmanMonster::~RockmanMonster()
{
}

void RockmanMonster::Start()
{
	//디버그용 테스트 포지션
	SetPosition({ 3300,100 });

	MonsterRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Monster), RenderPivot::CENTER);
	MonsterRenderer_->SetTransColor(TransColor);
	MonsterRenderer_->CreateAnimation("BunbyHeli_Left.bmp", "BunbyHeli_Left", 0, 1, 0.05f);
	MonsterRenderer_->CreateAnimation("BunbyHeli_Right.bmp", "BunbyHeli_Right", 0, 1, 0.05f);

	MonsterRenderer_->ChangeAnimation("BunbyHeli_Left");

	Player_ = GameManager::GetInst()->GetPlayer();
}

void RockmanMonster::Update()
{
	UpdateState();

}

void RockmanMonster::Render()
{
	if (GameManager::GetInst()->GetIsDebugMode() == true)
	{
		RockmanUtility::DebugText(StateStr_[static_cast<int>(CurState_)], GetCameraEffectPosition() + float4(0, 50));
	}

}

void RockmanMonster::ChangeState(MonsterState _State)
{
	if (CurState_ == _State)
	{
		return;
	}

	switch (_State)
	{
	case MonsterState::Chase:
		ChaseStart();
		break;
	case MonsterState::Attack:
		AttackStart();
		break;
	default:
		break;
	}

	CurState_ = _State;
}

void RockmanMonster::UpdateState()
{
	switch (CurState_)
	{
	case MonsterState::Chase:
		ChaseUpdate();
		break;
	case MonsterState::Attack:
		AttackUpdate();
		break;
	default:
		break;
	}
}

void RockmanMonster::ChaseStart()
{
	SetPosition(float4(GetPosition().x, AttackStartPos_.y));
}

void RockmanMonster::ChaseUpdate()
{
	WantHoriDir_= float4(Player_->GetPosition().x-GetPosition().x, 0);
	WantHoriDir_.Normal2D();

	//방향 전환이 일어난다면 애니메이션을 바꿔라
	if (WantHoriDir_.CompareInt2D(CurHoriDir_) == false)
	{
		MonsterRenderer_->ChangeAnimation("BunbyHeli_" + RockmanUtility::DirToStr(WantHoriDir_));
		CurHoriDir_ = WantHoriDir_;
	}

	//사정거리 내에 도달하면 공격을 한다.
	float Distance = float4(Player_->GetPosition().x - GetPosition().x, 0).Len2D();
	if (Distance <= AttackStartRange_)
	{
		ChangeState(MonsterState::Attack);
		return;
	}
	SetMove(CurHoriDir_ * Speed_*GameEngineTime::GetDeltaTime());
}

void RockmanMonster::AttackStart()
{
	AttackPos_ = Player_->GetPosition();
	AttackStartPos_ = GetPosition();

	InitVerDir_ = float4(0, Player_->GetPosition().y - GetPosition().y);
	VerSpeed_ = InitVerDir_.Len2D() * 1.5f; // 초기 스피드

	InitVerDir_.Normal2D();

	CurVerDir_ = InitVerDir_;

}

void RockmanMonster::AttackUpdate()
{
	float Distance = float4(0, AttackPos_.y - GetPosition().y).Len2D();		//공격목표점과의 거리

	//포물선 꼭지점에 도달하면 Vertical 방향전환
	if (Distance < 20.0f)
	{
		CurVerDir_ = -CurVerDir_;
	}

	//Vertical 방향전환이 일어난 상태에서 처음 공격 시작한 지점의 y좌표까지 도달한다면
	if (InitVerDir_.CompareInt2D(CurVerDir_) == false)
	{
		float InitDistance = float4(0, AttackStartPos_.y - GetPosition().y).Len2D();
		if (InitDistance < 20.0f)
		{
			ChangeState(MonsterState::Chase);
			return;
		}
	}

	VerSpeed_ += 200.0f * GameEngineTime::GetDeltaTime();

	//가속도 적용해주기!!
	SetMove(float4(CurHoriDir_.x * Speed_*4.3f * GameEngineTime::GetDeltaTime(),CurVerDir_.y*VerSpeed_*GameEngineTime::GetDeltaTime()));
}
