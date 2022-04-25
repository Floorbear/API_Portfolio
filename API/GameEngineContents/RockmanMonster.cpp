#include "RockmanMonster.h"
#include <GameEngine/GameEngineRenderer.h>
#include "RockmanUtility.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameManager.h"

RockmanMonster::RockmanMonster()
	:MonsterRenderer_(nullptr),
	CurState_(MonsterState::Chase),
	Player_(nullptr)
{
}

RockmanMonster::~RockmanMonster()
{
}

void RockmanMonster::Start()
{
	//디버그용 테스트 포지션
	SetPosition({ 3300,700 });

	MonsterRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Monster), RenderPivot::CENTER);
	MonsterRenderer_->SetTransColor(TransColor);
	MonsterRenderer_->CreateAnimation("BunbyHeli_Left.bmp", "BunbyHeli_Left", 0, 1, 0.05f);
	MonsterRenderer_->CreateAnimation("BunbyHeli_Right.bmp", "BunbyHeli_Right", 0, 1, 0.05f);

	MonsterRenderer_->ChangeAnimation("BunbyHeli_Left");

	
}

void RockmanMonster::Update()
{
	UpdateState();
}

void RockmanMonster::Render()
{
}

void RockmanMonster::ChangeState(MonsterState _State)
{
	if (CurState_ == _State)
	{
		return;
	}

	switch (CurState_)
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
}

void RockmanMonster::ChaseUpdate()
{
}

void RockmanMonster::AttackStart()
{
}

void RockmanMonster::AttackUpdate()
{
}
