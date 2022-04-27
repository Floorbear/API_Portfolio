#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include "GameManager.h"
#include "BackGround.h"
#include "RockmanUtility.h"
#include "Bullet.h"
#include <GameEngineBase/GameEngineSound.h>

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
	case PlayerState::Jump:
		JumpUpdate();
		break;
	case PlayerState::Climb:
		ClimbUpdate();
		break;
	case PlayerState::Hit:
		HitUpdate();
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
	case PlayerState::Jump:
		JumpStart();
		break;
	case PlayerState::Climb:
		ClimbStart();
		break;
	case PlayerState::Hit:
		HitStart();
		break;
	default:
		break;
	}
	CurState_ = _State;
}

void Player::IdleStart()
{
	PlayerRenderer_->SetPivot({ 0,50 });
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
			Gravity_ = 0;
			StateChange(PlayerState::Jump);
			return;
		}
	}
	//��ٸ� Ÿ�� Ű�� ������ ���
	if (IsMoveVerKeyPress() == true)
	{
		if (CheckPixelCol(WantVerDir_, LadderColor, true) == true)
		{
			//�Ʒ��� ��ٸ��� �̵��� ��� ��ġ�� ��¦ �Ʒ��� �������ش�
			if (WantVerDir_.CompareInt2D(float4::DOWN) == true)
			{
				SetMove({ 0,50 });
			}
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
	PlayerRenderer_->SetPivot({ 0,50 });
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
			if (WantVerDir_.CompareInt2D(float4::DOWN) == true)
			{
				SetMove({ 0,50 });
			}
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
			Gravity_ = 0;
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
	IsColDown = false;
	PlayerRenderer_->SetPivot({ 0,50 });
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
		Attack(CurHoriDir_,{55,-20});
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
				IsColDown = true;
				//���� ����
				GameEngineSound::SoundPlayOneShot("Landing.mp3");
		}
		else
		{
			IsColDown = false;
		}
		
	}
	else //�ݴ�� ( == �߷��� 0 �����̸�) ���� ����
	{
		Move(float4::UP, -Gravity_);
		if (CheckPixelCol(float4::UP) == true) //�Ӹ��� �浹ü�� ���� ����
		{
			IsColUP = true;
			Gravity_ = 0;
			CanJump_ = false;
		}
		else
		{
			IsColUP = false;
		}
	}



	//���� ��Ҿ� 
	if (IsColDown == true)
	{
		Gravity_ = 0;
		CanJump_ = true; //������ �ٽ� �� �� �ִ�
		CurJumpTime_ = 0.0f;
		IsColUP = false;
		StateChange(PlayerState::Idle);
		return;
		
	}

}

void Player::ClimbStart()
{
	PlayerRenderer_->SetPivot({ 0,50 });
	ResetAttackPara();
	MoveToLadderPos();
	PlayerRenderer_->ChangeAnimation("RockMan_Climb");
	PlayerRenderer_->PauseOn();
}



void Player::ClimbUpdate()
{
	if (IsMoveVerKeyPress() == true && IsAttacking == false) // W or S�� �����ٸ�
	{
		PlayerRenderer_->PauseOff();
		Move(WantVerDir_, 170.0f);//Climb Speed
		if (CheckPixelCol(float4::DOWN, LadderColor, true) == false
		|| (WantVerDir_.CompareInt2D(float4::UP) &&(CheckPixelCol(float4::ZERO, LadderColor, true) == false))) //���ʻ�ٸ��� ������ ���� Base ���� : �� �� �Ʒ� ��ٸ� �ȼ��� ������ Climb����
		{
			if (CheckPixelCol(float4::UP, LadderColor, true) == false) //���ʿ��� ��ٸ��� �ٿ����� ��ٸ� �ȼ� üũ�� �߽ɿ��� ��. �̷��� ���ϸ� ��ٸ� �ִϸ��̼��� ������ ��ĥ �� �ǰ� �������
			{
				SetMove(float4::UP * 46);
				StateChange(PlayerState::Idle);
				return;
			}		
		}
		if (WantVerDir_.CompareInt2D(float4::DOWN) && (CheckPixelCol(float4::ZERO, LadderColor) == false) || CheckPixelCol(float4::DOWN, WallColor, true) == true)
		{
			StateChange(PlayerState::Idle);
			return;
		}
	}
	else //���� Ű�� ������ �ʾҴٸ� �ִϸ��̼� ����
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

	if (IsMoveHoriKeyPress() == true) //���� Ű�� ������ ��� CurHoriDir_ ����
	{
		CurHoriDir_ = WantHoriDir_;
	}

	if (GameEngineInput::GetInst()->IsDown("Attack") == true) //����Ű�� ������ ���
	{
		PlayerRenderer_->ChangeAnimation("RockMan_ClimbAttack_" + RockmanUtility::DirToStr(CurHoriDir_));
		//������ ��ġ �ڿ������� Ʋ��
		if (CurHoriDir_.CompareInt2D(float4::RIGHT) == true)
		{
			PlayerRenderer_->SetPivot({ 17,50 });
		}
		else if (CurHoriDir_.CompareInt2D(float4::LEFT) == true)
		{
			PlayerRenderer_->SetPivot({ -17,50 });
		}
		Attack(CurHoriDir_, { 55,-20 });
	}
	if (IsAttackEnd_ == true) //����Ű�� ������ ���� �ð��� ���� ��
	{
		PlayerRenderer_->ChangeAnimation("RockMan_Climb");
		PlayerRenderer_->SetPivot({ 0,50 }); //Ʋ���� ������ �ǹ� �ٽ� ����ġ��
		IsAttackEnd_ = false;
	}
}

void Player::HitStart()
{
	ResetAttackPara();
	PlayerRenderer_->SetPivot({ 0,50 });
	PlayerRenderer_->ChangeAnimation("RockMan_Hit_" + RockmanUtility::DirToStr(CurHoriDir_));
	HitEffect_Center_Renderer_->ChangeAnimation("HitEffect_Center_On");
	HitEffect_Top_Renderer_->ChangeAnimation("HitEffect_Top_On");
	PlayerRenderer_->PauseOff();
	CurSpeed_ = MaxSpeed_*0.7f;
	CurHitTimer_ = 0.01; //CurHitTimer�� ���� ��¦ �ǵ���� Update���� Ÿ�̸Ӱ� �۵��ϰ� �Ѵ�.
}

void Player::HitUpdate()
{
	if (CurHitTimer_ < GetOutHitTimer_)
	{
		CurSpeed_ -= CurSpeed_ * GameEngineTime::GetDeltaTime();
		//�߷°��ӵ�
		Gravity_ += AccGravity_ * GameEngineTime::GetDeltaTime();

		if (Gravity_ >= MaxGravity_)
		{
			Gravity_ = MaxGravity_;
		}
		if (CurSpeed_ < 0.5f)
		{
			CurSpeed_ = 0;
		}
		if (Gravity_ >= 0) //�߷��� 0�̻��̸� ��������wd
		{

			if (((CheckPixelCol(float4::DOWN, LadderColor) == true) && (CheckPixelCol(float4::UP, LadderColor) == false)))//��ٸ� �ȼ� �߰� �˻�
			{

			}
			else
			{
				Move(float4::DOWN, Gravity_);
			}

			//���� ���� ����
			if (CheckPixelCol(float4::DOWN, WallColor) == true
				|| ((CheckPixelCol(float4::DOWN, LadderColor) == true) && (CheckPixelCol(float4::UP, LadderColor) == false)))
			{
				BackGround* CurBackGround = GameManager::GetInst()->GetCurrentBackGround();

				float4 NextPos = float4(0, (GetScale().Half().y + 1));
				float4 CheckPos_Mid = GetPosition() + float4(0, (GetScale().Half().y + 1));
				float Len = NextPos.Len2D();

				while (
					true == CurBackGround->IsBlocked(CheckPos_Mid, WallColor) || true == CurBackGround->IsBlocked(CheckPos_Mid, LadderColor))
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
				IsColDown = true;
				//���� ����
				GameEngineSound::SoundPlayOneShot("Landing.mp3");
			}

		}

		Move(-CurHoriDir_, CurSpeed_); //��Ʈ �� �ڷ� �з����� �̵���
	}
	else //Hit���¿��� Ż���ϴ� ���
	{
		//�Ʒ� ������ ���� ���
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
				HitEffect_Center_Renderer_->ChangeAnimation("HitEffect_Center_Off");
				HitEffect_Top_Renderer_->ChangeAnimation("HitEffect_Top_Off");
				StateChange(PlayerState::Jump);
				return;
			}
		}
		HitEffect_Center_Renderer_->ChangeAnimation("HitEffect_Center_Off");
		HitEffect_Top_Renderer_->ChangeAnimation("HitEffect_Top_Off");
		StateChange(PlayerState::Idle);
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
