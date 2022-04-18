#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include "GameManager.h"
#include "BackGround.h"
#include "RockmanUtility.h"
#include "Bullet.h"

void Player::IdleStart()
{
	//공격관련 초기화
	IsAttacking = false;
	AttackTickTime_ = 0.0f;
	IsAttackEnd_ = false;
	AttackCount_ = 0;
	PlayerRenderer_->ChangeAnimation(std::string("RockMan_Idle_" + RockmanUtility::DirToStr(CurDir_)));
}

void Player::MoveStart()
{
	//공격관련 초기화
	IsAttacking = false;
	AttackTickTime_ = 0.0f;
	IsAttackEnd_ = false;
	AttackCount_ = 0;

	PlayerRenderer_->ChangeAnimation("RockMan_Move_"+RockmanUtility::DirToStr(CurDir_));
}

void Player::IdleUpdate()
{
	//가만이 있다가 뚝 떨어진 경우
	if (CheckPixelCol(float4::DOWN) == false)
	{
		Gravity_ = MaxGravity_;
		CanJump_ = false;
		StateChange(PlayerState::Jump);
	}
	if (IsMoveKeyPress() == true)
	{
		CurDir_ = WantDir_;
		StateChange(PlayerState::Move);
	}

	if (GameEngineInput::GetInst()->IsDown("Attack") == true)
	{
		PlayerRenderer_->ChangeAnimation("RockMan_IdleAttack_" + RockmanUtility::DirToStr(CurDir_));
		Attack(CurDir_);
	}
	if (IsAttackEnd_ == true)
	{
		PlayerRenderer_->ChangeAnimation(std::string("RockMan_Idle_" + RockmanUtility::DirToStr(CurDir_)));
		IsAttackEnd_ = false;
	}
	
	if (GameEngineInput::GetInst()->IsDown("Jump") == true)
	{
		Gravity_ = JumpStrength_;
		StateChange(PlayerState::Jump);
		return;
	}
	
	if (CurSpeed_ <= 10.0f)
	{
		Move(CurDir_, 0);
	}
	else
	{
		CurSpeed_ += -CurSpeed_ * GameEngineTime::GetDeltaTime() * 30;
		Move(CurDir_, CurSpeed_);
	}
}

void Player::MoveUpdate()
{
	
	if (IsMoveKeyPress() == false)
	{
		StateChange(PlayerState::Idle);
	}


	if (GameEngineInput::GetInst()->IsDown("Jump") == true) //점프키를 눌렀을 경우
	{
		Gravity_ = JumpStrength_;
		StateChange(PlayerState::Jump);
		return;
	}
	if (CheckPixelCol(float4::DOWN) == false) //가다가 뚝 떨어진 경우
	{
		CanJump_ = false;
		Gravity_ = MaxGravity_;
		StateChange(PlayerState::Jump);
		return;
	}
	if (GameEngineInput::GetInst()->IsDown("Attack") == true) //공격키를 눌렀을 경우
	{
		if (IsAttacking == false)
		{
			PlayerRenderer_->ChangeAnimation("RockMan_MoveAttack_" + RockmanUtility::DirToStr(CurDir_));
		}
		Attack(CurDir_);
	}
	if (IsAttackEnd_ == true) //공격키를 누르고 일정 시간이 지난 후
	{
		PlayerRenderer_->ChangeAnimation("RockMan_Move_" + RockmanUtility::DirToStr(CurDir_));
		IsAttackEnd_ = false;
	}

	
	if (WantDir_.CompareInt2D(CurDir_) == false) //방향전환이 일어나면 Idle로 변경
	{
		CurSpeed_ = 0;
		StateChange(PlayerState::Idle);
		return;
	}


	CurDir_ = WantDir_;

	CurSpeed_ += GameEngineTime::GetDeltaTime() * AccSpeed_;

	//최대 속도 조절
	if (CurSpeed_ >= MaxSpeed_)
	{
		CurSpeed_ = MaxSpeed_;
	}


	Move(CurDir_, CurSpeed_);
}

void Player::JumpStart()
{
	//공격관련 초기화
	IsAttacking = false;
	AttackTickTime_ = 0.0f;
	IsAttackEnd_ = false;
	AttackCount_ = 0;

	PlayerRenderer_->ChangeAnimation("RockMan_Jump_"+ RockmanUtility::DirToStr(CurDir_));
}

void Player::JumpUpdate()
{
	
	//점프 키를 누른만큼 더 점프 거리가 늘어남
	if (GameEngineInput::GetInst()->IsPress("Jump") == true &&
		CanJump_ == true && CurJumpTime_ <= MaxJumpTime_ &&
		CheckPixelCol(float4::UP) == false)
	{
		CurJumpTime_ += GameEngineTime::GetDeltaTime();
		Gravity_ = JumpStrength_;
	}
	else if(GameEngineInput::GetInst()->IsFree("Jump") == true)
	{
		CanJump_ = false;
	}
	//중력가속도
	Gravity_ += AccGravity_ * GameEngineTime::GetDeltaTime();
	if (Gravity_ >= MaxGravity_)
	{
		Gravity_ = MaxGravity_;
	}

	

	//점프 중 이동
	if (IsMoveKeyPress() == true)
	{
		//이동 중 방향이 바뀌면 애니메이션이 바뀐다
		if (CurDir_.CompareInt2D(WantDir_) == false)
		{
			CurSpeed_ = 0;
			PlayerRenderer_->ChangeAnimation("RockMan_Jump_" + RockmanUtility::DirToStr(WantDir_));
		}
		CurDir_ = WantDir_;
		CurSpeed_ += GameEngineTime::GetDeltaTime() * AccSpeed_;

		//최대 속도 조절
		if (CurSpeed_ >= MaxSpeed_)
		{
			CurSpeed_ = MaxSpeed_;
		}
		Move(CurDir_, CurSpeed_);
	}	


	Move(float4::DOWN, Gravity_);


	//땅이나 머리에 닿았어
	if (IsColVer == true)
	{
		Gravity_ = MaxGravity_;
		if (Gravity_ >= 0)
		{
			CanJump_ = true; //점프를 다시 할 수 있더
			CurJumpTime_ = 0.0f;
			StateChange(PlayerState::Idle);
			return;
		}
		
	}

}
