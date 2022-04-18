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
	//���ݰ��� �ʱ�ȭ
	IsAttacking = false;
	AttackTickTime_ = 0.0f;
	IsAttackEnd_ = false;
	AttackCount_ = 0;
	PlayerRenderer_->ChangeAnimation(std::string("RockMan_Idle_" + RockmanUtility::DirToStr(CurDir_)));
}

void Player::MoveStart()
{
	//���ݰ��� �ʱ�ȭ
	IsAttacking = false;
	AttackTickTime_ = 0.0f;
	IsAttackEnd_ = false;
	AttackCount_ = 0;

	PlayerRenderer_->ChangeAnimation("RockMan_Move_"+RockmanUtility::DirToStr(CurDir_));
}

void Player::IdleUpdate()
{
	//������ �ִٰ� �� ������ ���
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


	if (GameEngineInput::GetInst()->IsDown("Jump") == true) //����Ű�� ������ ���
	{
		Gravity_ = JumpStrength_;
		StateChange(PlayerState::Jump);
		return;
	}
	if (CheckPixelCol(float4::DOWN) == false) //���ٰ� �� ������ ���
	{
		CanJump_ = false;
		Gravity_ = MaxGravity_;
		StateChange(PlayerState::Jump);
		return;
	}
	if (GameEngineInput::GetInst()->IsDown("Attack") == true) //����Ű�� ������ ���
	{
		if (IsAttacking == false)
		{
			PlayerRenderer_->ChangeAnimation("RockMan_MoveAttack_" + RockmanUtility::DirToStr(CurDir_));
		}
		Attack(CurDir_);
	}
	if (IsAttackEnd_ == true) //����Ű�� ������ ���� �ð��� ���� ��
	{
		PlayerRenderer_->ChangeAnimation("RockMan_Move_" + RockmanUtility::DirToStr(CurDir_));
		IsAttackEnd_ = false;
	}

	
	if (WantDir_.CompareInt2D(CurDir_) == false) //������ȯ�� �Ͼ�� Idle�� ����
	{
		CurSpeed_ = 0;
		StateChange(PlayerState::Idle);
		return;
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
	//���ݰ��� �ʱ�ȭ
	IsAttacking = false;
	AttackTickTime_ = 0.0f;
	IsAttackEnd_ = false;
	AttackCount_ = 0;

	PlayerRenderer_->ChangeAnimation("RockMan_Jump_"+ RockmanUtility::DirToStr(CurDir_));
}

void Player::JumpUpdate()
{
	
	//���� Ű�� ������ŭ �� ���� �Ÿ��� �þ
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
	//�߷°��ӵ�
	Gravity_ += AccGravity_ * GameEngineTime::GetDeltaTime();
	if (Gravity_ >= MaxGravity_)
	{
		Gravity_ = MaxGravity_;
	}

	

	//���� �� �̵�
	if (IsMoveKeyPress() == true)
	{
		//�̵� �� ������ �ٲ�� �ִϸ��̼��� �ٲ��
		if (CurDir_.CompareInt2D(WantDir_) == false)
		{
			CurSpeed_ = 0;
			PlayerRenderer_->ChangeAnimation("RockMan_Jump_" + RockmanUtility::DirToStr(WantDir_));
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


	Move(float4::DOWN, Gravity_);


	//���̳� �Ӹ��� ��Ҿ�
	if (IsColVer == true)
	{
		Gravity_ = MaxGravity_;
		if (Gravity_ >= 0)
		{
			CanJump_ = true; //������ �ٽ� �� �� �ִ�
			CurJumpTime_ = 0.0f;
			StateChange(PlayerState::Idle);
			return;
		}
		
	}

}
