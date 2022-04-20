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
	ResetAttackPara();
	PlayerRenderer_->ChangeAnimation(std::string("RockMan_Idle_" + RockmanUtility::DirToStr(CurHoriDir_)));
	PlayerRenderer_->PauseOff();
}

void Player::IdleUpdate()
{
	//������ �ִٰ� �� ������ ���
	if (CheckPixelCol(float4::DOWN, WallColor) == false)
	{
		//��ٸ� �� ���κ��ΰ�� �������� ���
		if (CheckPixelCol(float4::DOWN, LadderColor) == true
			&& CheckPixelCol(float4::UP, LadderColor) == false)
		{

		}
		else
		{
			CanJump_ = false;
			Gravity_ = MaxGravity_;
			StateChange(PlayerState::Jump);
			return;
		}
	}
	//��ٸ� Ÿ�� Ű�� ������ ���
	if (IsMoveVerKeyPress() == true)
	{
		if (CheckPixelCol(WantVerDir_, LadderColor, true) == true)
		{
			StateChange(PlayerState::Climb);
			return;
		}
	}
	//�̵� �ϰ� ���� ���
	if (IsMoveHoriKeyPress() == true)
	{
		CurHoriDir_ = WantHoriDir_;
		StateChange(PlayerState::Move);
		return;
	}

	//����Ű�� ���� ���
	if (GameEngineInput::GetInst()->IsDown("Attack") == true)
	{
		PlayerRenderer_->ChangeAnimation("RockMan_IdleAttack_" + RockmanUtility::DirToStr(CurHoriDir_));
		Attack(CurHoriDir_);
	}
	if (IsAttackEnd_ == true)
	{
		PlayerRenderer_->ChangeAnimation(std::string("RockMan_Idle_" + RockmanUtility::DirToStr(CurHoriDir_)));
		IsAttackEnd_ = false;
	}

	//����Ű�� ���� ���
	if (GameEngineInput::GetInst()->IsDown("Jump") == true)
	{
		CurJumpTime_ = 0.0f;
		CanJump_ = true;
		Gravity_ = JumpStrength_;
		StateChange(PlayerState::Jump);
		return;
	}

	if (CurSpeed_ <= 10.0f)
	{
		CurSpeed_ = 0;
		Move(CurHoriDir_, 0);
	}
	else
	{
		CurSpeed_ += -CurSpeed_ * GameEngineTime::GetDeltaTime() * 30;
		Move(CurHoriDir_, CurSpeed_);
	}
}

void Player::MoveStart()
{
	ResetAttackPara();

	PlayerRenderer_->ChangeAnimation("RockMan_Move_"+RockmanUtility::DirToStr(CurHoriDir_));

	PlayerRenderer_->PauseOff();
}

void Player::MoveUpdate()
{
	
	if (IsMoveHoriKeyPress() == false)
	{
		StateChange(PlayerState::Idle);
		return;
	}

	//��ٸ� Ű�� ������ �ܿ�
	if (IsMoveVerKeyPress() == true)
	{
		if (CheckPixelCol(WantVerDir_, LadderColor, true) == true)
		{
			StateChange(PlayerState::Climb);
			return;
		}
	}

	if (GameEngineInput::GetInst()->IsDown("Jump") == true) //����Ű�� ������ ���
	{
		CanJump_ = true;
		CurJumpTime_ = 0.0f;
		Gravity_ = JumpStrength_;
		StateChange(PlayerState::Jump);
		return;
	}
	if (CheckPixelCol(float4::DOWN, WallColor) == false) //���ٰ� �� ������ ���
	{
		//��ٸ� �� ���κ��ΰ�� �������� ���
		if (CheckPixelCol(float4::DOWN, LadderColor) == true
			&& CheckPixelCol(float4::UP, LadderColor) == false)
		{

		}
		else
		{
			CanJump_ = false;
			Gravity_ = MaxGravity_;
			StateChange(PlayerState::Jump);
			return;
		}

	}
	if (GameEngineInput::GetInst()->IsDown("Attack") == true) //����Ű�� ������ ���
	{
		if (IsAttacking == false)
		{
			PlayerRenderer_->ChangeAnimation("RockMan_MoveAttack_" + RockmanUtility::DirToStr(CurHoriDir_));
		}
		Attack(CurHoriDir_);
	}
	if (IsAttackEnd_ == true) //����Ű�� ������ ���� �ð��� ���� ��
	{
		PlayerRenderer_->ChangeAnimation("RockMan_Move_" + RockmanUtility::DirToStr(CurHoriDir_));
		IsAttackEnd_ = false;
	}

	
	if (WantHoriDir_.CompareInt2D(CurHoriDir_) == false) //������ȯ�� �Ͼ�� Idle�� ����
	{
		CurSpeed_ = 0;
		StateChange(PlayerState::Idle);
		return;
	}


	CurHoriDir_ = WantHoriDir_;

	CurSpeed_ += GameEngineTime::GetDeltaTime() * AccSpeed_;

	//�ִ� �ӵ� ����
	if (CurSpeed_ >= MaxSpeed_)
	{
		CurSpeed_ = MaxSpeed_;
	}


	Move(CurHoriDir_, CurSpeed_);
}

void Player::JumpStart()
{
	ResetAttackPara();

	PlayerRenderer_->ChangeAnimation("RockMan_Jump_"+ RockmanUtility::DirToStr(CurHoriDir_));
	PlayerRenderer_->PauseOff();
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

	//������ ����
	if (GameEngineInput::GetInst()->IsDown("Attack") == true) //����Ű�� ������ ���
	{
		if (IsAttacking == false)
		{
			PlayerRenderer_->ChangeAnimation("RockMan_JumpAttack_" + RockmanUtility::DirToStr(CurHoriDir_));
		}
		Attack(CurHoriDir_);
	}
	if (IsAttackEnd_ == true) //����Ű�� ������ ���� �ð��� ���� ��
	{
		PlayerRenderer_->ChangeAnimation("RockMan_Jump_" + RockmanUtility::DirToStr(CurHoriDir_));
		IsAttackEnd_ = false;
	}
	
	//��ٸ� Ű�� ������ �ܿ�
	if (IsMoveVerKeyPress() == true)
	{
		if (CheckPixelCol(WantVerDir_, LadderColor, true) == true)
		{
			StateChange(PlayerState::Climb);
			return;
		}
	}

	//���� �� �̵�
	if (IsMoveHoriKeyPress() == true)
	{
		//�̵� �� ������ �ٲ�� �ִϸ��̼��� �ٲ��
		if (CurHoriDir_.CompareInt2D(WantHoriDir_) == false)
		{
			CurSpeed_ = 0;
			PlayerRenderer_->ChangeAnimation("RockMan_Jump_" + RockmanUtility::DirToStr(WantHoriDir_));
		}
		CurHoriDir_ = WantHoriDir_;
		CurSpeed_ += GameEngineTime::GetDeltaTime() * AccSpeed_;

		//�ִ� �ӵ� ����
		if (CurSpeed_ >= MaxSpeed_)
		{
			CurSpeed_ = MaxSpeed_;
		}
		Move(CurHoriDir_, CurSpeed_);
	}	

	if (Gravity_ >= 0) //�߷��� 0�̻��̸� ��������
	{
		Move(float4::DOWN, Gravity_);

		//���� ���� ����
		if (CheckPixelCol(float4::DOWN, WallColor) == true
		|| ((CheckPixelCol(float4::DOWN, LadderColor) == true)&& (CheckPixelCol(float4::ZERO, LadderColor) == false)) )
		{
			BackGround* CurBackGround = GameManager::GetInst()->GetCurrentBackGround();

				float4 NextPos = float4(0,  (GetScale().Half().y + 1));
				float4 CheckPos_Mid = GetPosition() + float4(0,  (GetScale().Half().y + 1));
				float Len = NextPos.Len2D();

				while (
					true == CurBackGround->IsBlocked(CheckPos_Mid,WallColor))				
				{
					NextPos.Normal2D();
					Len -= 1.0f;
					NextPos *= Len;
					CheckPos_Mid = GetPosition() += NextPos;

					//���ѷ��� Ż���� ���� ������ġ
					if (1.0f >= NextPos.Len2D())
					{
						break;
					}
				}
				float4 WantMovePos = NextPos - float4(0, GetScale().Half().y);
				SetMove(WantMovePos);
				IsColVer = true;
		}
		else
		{
			IsColVer = false;
		}
		
	}
	else //�ݴ�� ( == �߷��� 0 �����̸�)���� ����
	{
		Move(float4::UP, -Gravity_);
		if (CheckPixelCol(float4::UP) == true)
		{
			IsColVer = true;
		}
		else
		{
			IsColVer = false;
		}
	}



	//���̳� �Ӹ��� ��Ҿ�
	if (IsColVer == true)
	{
		Gravity_ = MaxGravity_;
		if (Gravity_ >= 0) //�� ���� �Ȱɸ� �����ؼ� �Ӹ��� �� �ھƵ� Idle���°� ��
		{
			CanJump_ = true; //������ �ٽ� �� �� �ִ�
			CurJumpTime_ = 0.0f;
			StateChange(PlayerState::Idle);
			return;
		}
		
	}

}

void Player::ClimbStart()
{
	ResetAttackPara();
	MoveToLadderPos();
	PlayerRenderer_->ChangeAnimation("RockMan_Climb");
	PlayerRenderer_->PauseOn();
}

void Player::ClimbUpdate()
{
	if (IsMoveVerKeyPress() == true)
	{
		PlayerRenderer_->PauseOff();
		Move(WantVerDir_, 170.0f);//Climb Speed
		if (CheckPixelCol(float4::DOWN, LadderColor, true) == false
		|| (WantVerDir_.CompareInt2D(float4::UP) &&(CheckPixelCol(float4::ZERO, LadderColor, true) == false))) //��ٸ��� ������ ����
		{
			if (CheckPixelCol(float4::UP, LadderColor, true) == false) //���ʿ��� ��ٸ��� �ٿ����� ClimbFinish �ִϸ��̼��� ���
			{
				SetMove(float4::UP * 46);
				StateChange(PlayerState::Idle);
			}
			else
			{
				StateChange(PlayerState::Idle);
			}		
		}
	}
	else
	{
		PlayerRenderer_->PauseOn();
	}
	if (GameEngineInput::GetInst()->IsDown("Jump") == true) //����Ű�� ������ ���
	{
		CanJump_ = false;
		Gravity_ = 0;
		StateChange(PlayerState::Jump);
		return;
	}
}

void Player::MoveToLadderPos()
{
	//�ϴ� �� �ڵ忡�� ������ "��ٸ� �ȼ�"�� �߰� �ߴٴ� ��
	BackGround* CurBackGround = GameManager::GetInst()->GetCurrentBackGround();

	float4 CheckLadderPos = GetPosition() + float4(0, WantVerDir_.y * (GetScale().Half().y + 1));
	float4 LadderHoriSize = { 30.0,0,0 };
	float MoveSize = 0.0f;

	while (CurBackGround->IsBlocked(CheckLadderPos - LadderHoriSize, LadderColor) == false
		|| CurBackGround->IsBlocked(CheckLadderPos, LadderColor) == false
		|| CurBackGround->IsBlocked(CheckLadderPos + LadderHoriSize, LadderColor) == false)
	{
		//�������� ��ٸ� �ȼ��� ���� �����ʿ��� ��ٸ� �ȼ��� �ִ� ����
		if (CurBackGround->IsBlocked(CheckLadderPos - LadderHoriSize, LadderColor) == false
			&& CurBackGround->IsBlocked(CheckLadderPos + LadderHoriSize, LadderColor) == true)
		{
			CheckLadderPos.x += 1.0f;
			MoveSize += 1.0f;
			continue;
		}
		//������ ���� ��ٸ� �ȼ��� ���� ���� ������ ��ٸ� �ȼ��� �ִ� ����
		//�������� ��ٸ� �ȼ��� ���� �����ʿ��� ��ٸ� �ȼ��� �ִ� ����
		if (CurBackGround->IsBlocked(CheckLadderPos - LadderHoriSize, LadderColor) == true
			&& CurBackGround->IsBlocked(CheckLadderPos + LadderHoriSize, LadderColor) == false)
		{
			CheckLadderPos.x -= 1.0f;
			MoveSize -= 1.0f;
			continue;
		}
		break;
	}
	SetMove(float4(MoveSize, 0));
}
void Player::ResetAttackPara()
{
	IsAttacking = false;
	AttackTickTime_ = 0.0f;
	IsAttackEnd_ = false;
	AttackCount_ = 0;
}
