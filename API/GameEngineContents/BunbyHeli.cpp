#include "BunbyHeli.h"

BunbyHeli::BunbyHeli()
{
}

BunbyHeli::~BunbyHeli()
{
}

void BunbyHeli::Start()
{
}

void BunbyHeli::Update()
{
	UpdateState();
}

void BunbyHeli::Render()
{
}

void BunbyHeli::ChangeState(MonsterState _State)
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
}

void BunbyHeli::UpdateState()
{
	switch (CurState_)
	{
	case MonsterState::Chase:
		break;
	case MonsterState::Attack:
		break;
	default:
		break;
	}
}
