#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include "GameManager.h"
#include "BackGround.h"


void Player::StateUpdate()
{
	switch (CurState_)
	{
	case PlayerState::Idle:
		IdleUpdate();
		break;
	case PlayerState::Move:
		MoveUpdate();
		break;
	default:
		break;
	}
}

void Player::StateChange(PlayerState _State)
{
	if (CurState_ == _State)
	{
		return;
	}

	switch (_State)
	{
	case PlayerState::Idle:
		IdleStart();
		break;
	case PlayerState::Move:
		MoveStart();
		break;
	default:
		break;
	}
	CurState_ = _State;
}


bool Player::IsMoveKeyPress()
{
	return GameEngineInput::GetInst()->IsPress("MoveRight") ||
		GameEngineInput::GetInst()->IsPress("MoveLeft");
}

Player::Player()
	:Speed_(10.0),
	AccSpeed_(0.5f),
	CurDir_(PlayerDir::Right),
	MoveDir_({0,0})
{
	PlayerDirStr_[static_cast<int>(PlayerDir::Left)] = "Left";
	PlayerDirStr_[static_cast<int>(PlayerDir::Right)] = "Right";
}

Player::~Player()
{
}

void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half()+float4::UP*200);
	SetScale({ 256,256 });
	
	LoadAnimation();


	//키초기화 << 이걸 여기서 해야하나?
	{
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
	}
	
	StateChange(PlayerState::Idle);
}

void Player::Update()
{
	StateUpdate();
	
}

void Player::Render()
{

}
