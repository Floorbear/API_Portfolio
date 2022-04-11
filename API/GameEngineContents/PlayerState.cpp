#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include "GameManager.h"
#include "BackGround.h"

void Player::IdleStart()
{
	PlayerRenderer_->ChangeAnimation(std::string("RockMan_Idle_" + PlayerDirStr_[static_cast<int>(CurDir_)]));
}

void Player::MoveStart()
{
	PlayerRenderer_->ChangeAnimation(std::string("RockMan_Move_" + PlayerDirStr_[static_cast<int>(CurDir_)]));
}

void Player::IdleUpdate()
{
	if (IsMoveKeyPress() == true)
	{
		StateChange(PlayerState::Move);
	}

	MoveDir_ = float4::ZERO;
}

void Player::MoveUpdate()
{
	if (IsMoveKeyPress() == false)
	{
		StateChange(PlayerState::Idle);
	}


	PlayerDir PlayerDir_ = PlayerDir::Right;

	if (GameEngineInput::GetInst()->IsPress("MoveRight") == true)
	{
		MoveDir_ += float4::RIGHT*AccSpeed_;
		PlayerDir_ = PlayerDir::Right;
	}
	else if (GameEngineInput::GetInst()->IsPress("MoveLeft") == true)
	{
		MoveDir_ += float4::LEFT*AccSpeed_;
		PlayerDir_ = PlayerDir::Left;
	}

	//������ȯ�� �Ͼ�� Idle��
	if (PlayerDir_ != CurDir_)
	{
		StateChange(PlayerState::Idle);
		CurDir_ = PlayerDir_;
	}

	//�ȼ�üũ
	float4 CheckHoriPos = GetPosition()  /*MoveDir_*/ ;

	//�߷�
	float Gravity = 30;

	//�̵�
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);




	//ī�޶� üũ
	float4 CameraPos = { GetPosition().x - GameEngineWindow::GetScale().Half().x,0 };
	float BackGroundScale_X = GameManager::GetInst()->GetCurrentBackGround()->GetScale().x;

	if (CameraPos.x <= 0)
	{
		CameraPos.x = 0;
	}
	if (CameraPos.x > BackGroundScale_X - GameEngineWindow::GetScale().x)
	{
		CameraPos.x = BackGroundScale_X - GameEngineWindow::GetScale().x;
	}

	GetLevel()->SetCameraPos(CameraPos);
}
