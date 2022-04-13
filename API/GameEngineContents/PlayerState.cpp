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
	
	if (MoveDir_.Len2D() >= 0.03f)
	{
		MoveDir_ += -MoveDir_ * GameEngineTime::GetDeltaTime()*5;
		Move();
	}
	else
	{
		MoveDir_ = float4::ZERO;
	}

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
		//CheckPixelCol(PlayerDir::Right);
		MoveDir_ += float4::RIGHT*AccSpeed_ * GameEngineTime::GetDeltaTime();
		PlayerDir_ = PlayerDir::Right;
	}
	else if (GameEngineInput::GetInst()->IsPress("MoveLeft") == true)
	{
		MoveDir_ += float4::LEFT*AccSpeed_ * GameEngineTime::GetDeltaTime();
		PlayerDir_ = PlayerDir::Left;
	}

	//최대 속도 조절
	if (MoveDir_.Len2D() >= MaxSpeed_)
	{
		MoveDir_.Range2D(MaxSpeed_);
	}

	//방향전환이 일어나면 Idle로
	if (PlayerDir_ != CurDir_)
	{
		StateChange(PlayerState::Idle);
		CurDir_ = PlayerDir_;
	}

	
	Move();

}

//bool Player::CheckPixelCol(PlayerDir _Dir)
//{
//	//콜리전 체크
//	BackGround* CurBackGround = GameManager::GetInst()->GetCurrentBackGround();
//
//	float4 CheckPos_Top = GetPosition() + float4(50, -50) * DirValue_[static_cast<int>(CurDir_)];
//	float4 CheckPos_Mid = GetPosition() + float4(50, 0);
//	float4 CheckPos_Bottom = GetPosition() + float4(50, 50);
//
//	if (CurBackGround->IsBlocked(CheckPos_Top) ||
//		CurBackGround->IsBlocked(CheckPos_Mid) ||
//		CurBackGround->IsBlocked(CheckPos_Bottom)
//		)
//	{
//		return;
//	}
//}

void Player::Move()
{
	//이동
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);

	//카메라 체크
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
