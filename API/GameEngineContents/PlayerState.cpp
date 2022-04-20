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
	//가만이 있다가 뚝 떨어진 경우
	if (CheckPixelCol(float4::DOWN, WallColor) == false)
	{
		//사다리 윗 끝부분인경우 발판으로 고려
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
	//사다리 타기 키를 눌렀을 경우
	if (IsMoveVerKeyPress() == true)
	{
		if (CheckPixelCol(WantVerDir_, LadderColor, true) == true)
		{
			StateChange(PlayerState::Climb);
			return;
		}
	}
	//이동 하고 싶은 경우
	if (IsMoveHoriKeyPress() == true)
	{
		CurHoriDir_ = WantHoriDir_;
		StateChange(PlayerState::Move);
		return;
	}

	//공격키를 누를 경우
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

	//점프키를 누를 경우
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

	//사다리 키를 눌렀을 겨우
	if (IsMoveVerKeyPress() == true)
	{
		if (CheckPixelCol(WantVerDir_, LadderColor, true) == true)
		{
			StateChange(PlayerState::Climb);
			return;
		}
	}

	if (GameEngineInput::GetInst()->IsDown("Jump") == true) //점프키를 눌렀을 경우
	{
		CanJump_ = true;
		CurJumpTime_ = 0.0f;
		Gravity_ = JumpStrength_;
		StateChange(PlayerState::Jump);
		return;
	}
	if (CheckPixelCol(float4::DOWN, WallColor) == false) //가다가 뚝 떨어진 경우
	{
		//사다리 윗 끝부분인경우 발판으로 고려
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
	if (GameEngineInput::GetInst()->IsDown("Attack") == true) //공격키를 눌렀을 경우
	{
		if (IsAttacking == false)
		{
			PlayerRenderer_->ChangeAnimation("RockMan_MoveAttack_" + RockmanUtility::DirToStr(CurHoriDir_));
		}
		Attack(CurHoriDir_);
	}
	if (IsAttackEnd_ == true) //공격키를 누르고 일정 시간이 지난 후
	{
		PlayerRenderer_->ChangeAnimation("RockMan_Move_" + RockmanUtility::DirToStr(CurHoriDir_));
		IsAttackEnd_ = false;
	}

	
	if (WantHoriDir_.CompareInt2D(CurHoriDir_) == false) //방향전환이 일어나면 Idle로 변경
	{
		CurSpeed_ = 0;
		StateChange(PlayerState::Idle);
		return;
	}


	CurHoriDir_ = WantHoriDir_;

	CurSpeed_ += GameEngineTime::GetDeltaTime() * AccSpeed_;

	//최대 속도 조절
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

	//점프중 공격
	if (GameEngineInput::GetInst()->IsDown("Attack") == true) //공격키를 눌렀을 경우
	{
		if (IsAttacking == false)
		{
			PlayerRenderer_->ChangeAnimation("RockMan_JumpAttack_" + RockmanUtility::DirToStr(CurHoriDir_));
		}
		Attack(CurHoriDir_);
	}
	if (IsAttackEnd_ == true) //공격키를 누르고 일정 시간이 지난 후
	{
		PlayerRenderer_->ChangeAnimation("RockMan_Jump_" + RockmanUtility::DirToStr(CurHoriDir_));
		IsAttackEnd_ = false;
	}
	
	//사다리 키를 눌렀을 겨우
	if (IsMoveVerKeyPress() == true)
	{
		if (CheckPixelCol(WantVerDir_, LadderColor, true) == true)
		{
			StateChange(PlayerState::Climb);
			return;
		}
	}

	//점프 중 이동
	if (IsMoveHoriKeyPress() == true)
	{
		//이동 중 방향이 바뀌면 애니메이션이 바뀐다
		if (CurHoriDir_.CompareInt2D(WantHoriDir_) == false)
		{
			CurSpeed_ = 0;
			PlayerRenderer_->ChangeAnimation("RockMan_Jump_" + RockmanUtility::DirToStr(WantHoriDir_));
		}
		CurHoriDir_ = WantHoriDir_;
		CurSpeed_ += GameEngineTime::GetDeltaTime() * AccSpeed_;

		//최대 속도 조절
		if (CurSpeed_ >= MaxSpeed_)
		{
			CurSpeed_ = MaxSpeed_;
		}
		Move(CurHoriDir_, CurSpeed_);
	}	

	if (Gravity_ >= 0) //중력이 0이상이면 떨어진다
	{
		Move(float4::DOWN, Gravity_);

		//땅에 닿은 상태
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

					//무한루프 탈출을 위한 안전장치
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
	else //반대면 ( == 중력이 0 이하이면)점프 상태
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



	//땅이나 머리에 닿았어
	if (IsColVer == true)
	{
		Gravity_ = MaxGravity_;
		if (Gravity_ >= 0) //이 조건 안걸면 점프해서 머리에 벽 박아도 Idle상태가 되
		{
			CanJump_ = true; //점프를 다시 할 수 있더
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
		|| (WantVerDir_.CompareInt2D(float4::UP) &&(CheckPixelCol(float4::ZERO, LadderColor, true) == false))) //사다리가 끝나는 조건
		{
			if (CheckPixelCol(float4::UP, LadderColor, true) == false) //윗쪽에서 사다리를 다오르면 ClimbFinish 애니메이션을 출력
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
	if (GameEngineInput::GetInst()->IsDown("Jump") == true) //점프키를 눌렀을 경우
	{
		CanJump_ = false;
		Gravity_ = 0;
		StateChange(PlayerState::Jump);
		return;
	}
}

void Player::MoveToLadderPos()
{
	//일단 이 코드에서 전제는 "사다리 픽셀"을 발견 했다는 것
	BackGround* CurBackGround = GameManager::GetInst()->GetCurrentBackGround();

	float4 CheckLadderPos = GetPosition() + float4(0, WantVerDir_.y * (GetScale().Half().y + 1));
	float4 LadderHoriSize = { 30.0,0,0 };
	float MoveSize = 0.0f;

	while (CurBackGround->IsBlocked(CheckLadderPos - LadderHoriSize, LadderColor) == false
		|| CurBackGround->IsBlocked(CheckLadderPos, LadderColor) == false
		|| CurBackGround->IsBlocked(CheckLadderPos + LadderHoriSize, LadderColor) == false)
	{
		//왼쪽위는 사다리 픽셀이 없고 오른쪽에는 사다리 픽셀이 있는 상태
		if (CurBackGround->IsBlocked(CheckLadderPos - LadderHoriSize, LadderColor) == false
			&& CurBackGround->IsBlocked(CheckLadderPos + LadderHoriSize, LadderColor) == true)
		{
			CheckLadderPos.x += 1.0f;
			MoveSize += 1.0f;
			continue;
		}
		//오른쪽 위는 사다리 픽셀이 없고 왼쪽 위에는 사다리 픽셀이 있는 상태
		//왼쪽위는 사다리 픽셀이 없고 오른쪽에는 사다리 픽셀이 있는 상태
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
