#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include "GameManager.h"
#include "BackGround.h"

void Player::IdleStart()
{
	if (CurDir_.CompareInt2D(float4::RIGHT) == true)
	{
		PlayerRenderer_->ChangeAnimation("RockMan_Idle_Right");
	}
	else if (CurDir_.CompareInt2D(float4::LEFT) == true)
	{
		PlayerRenderer_->ChangeAnimation("RockMan_Idle_Left");
	}
}

void Player::MoveStart()
{
	if (CurDir_.CompareInt2D(float4::RIGHT) == true)
	{
		PlayerRenderer_->ChangeAnimation("RockMan_Move_Right");
	}
	else if (CurDir_.CompareInt2D(float4::LEFT) == true)
	{
		PlayerRenderer_->ChangeAnimation("RockMan_Move_Left");
	}
	
}

void Player::IdleUpdate()
{
	//�߷�üũ
	if (CheckPixelCol(float4::DOWN) == false)
	{
		Gravity_ = MaxGravity_;
		StateChange(PlayerState::Jump);
	}
	if (IsMoveKeyPress() == true)
	{
		CurDir_ = WantDir_;
		StateChange(PlayerState::Move);
	}

	if (GameEngineInput::GetInst()->IsDown("Jump") == true)
	{
		Gravity_ = Default_Gravity_;
		StateChange(PlayerState::Jump);
	}
	
	if (CurSpeed_ <= 10.0f)
	{
		Move(CurDir_, 0);
	}
	else
	{
		CurSpeed_ += -CurSpeed_ * GameEngineTime::GetDeltaTime() * 10;
		Move(CurDir_, CurSpeed_);
	}
}

void Player::MoveUpdate()
{
	
	if (IsMoveKeyPress() == false)
	{
		StateChange(PlayerState::Idle);
	}

	//����
	if (GameEngineInput::GetInst()->IsDown("Jump") == true)
	{
		Gravity_ = Default_Gravity_;
		StateChange(PlayerState::Jump);
		
	}
	if (CheckPixelCol(float4::DOWN) == false)
	{
		Gravity_ = MaxGravity_;
		StateChange(PlayerState::Jump);
	}

	//������ȯ�� �Ͼ�� Idle��
	if (WantDir_.CompareInt2D(CurDir_) == false)
	{
		CurSpeed_ = 0;
		StateChange(PlayerState::Idle);
	}


	CurDir_ = WantDir_;

	CurSpeed_ += GameEngineTime::GetDeltaTime() * AccSpeed_;

	//�ִ� �ӵ� ����
	if (CurSpeed_ >= MaxSpeed_)
	{
		CurSpeed_ = MaxSpeed_;
	}


	Move(CurDir_, CurSpeed_);
}

void Player::JumpStart()
{
	//�ִϸ��̼�
}

void Player::JumpUpdate()
{
	
	//�߷°��ӵ�
	Gravity_ += AccGravity_ * GameEngineTime::GetDeltaTime();
	if (Gravity_ >= MaxGravity_)
	{
		Gravity_ = MaxGravity_;
	}


	//���� �� �̵�
	if (IsMoveKeyPress() == true)
	{
		CurDir_ = WantDir_;
		CurSpeed_ += GameEngineTime::GetDeltaTime() * AccSpeed_;

		//�ִ� �ӵ� ����
		if (CurSpeed_ >= MaxSpeed_)
		{
			CurSpeed_ = MaxSpeed_;
		}
		Move(CurDir_, CurSpeed_);
	}	


	Move(float4::DOWN,Gravity_);


	if (CheckPixelCol(float4::DOWN) == true)
	{		
		Gravity_ = MaxGravity_;
		StateChange(PlayerState::Idle);
	}

}
