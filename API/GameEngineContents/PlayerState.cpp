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
			Gravity_ = 0;
			StateChange(PlayerState::Jump);
			return;
		}
	}
	//사다리 타기 키를 눌렀을 경우
	if (IsMoveVerKeyPress() == true)
	{
		if (CheckPixelCol(WantVerDir_, LadderColor, true) == true)
		{
			//아래쪽 사다리로 이동할 경우 위치를 살짝 아래로 조정해준다
			if (WantVerDir_.CompareInt2D(float4::DOWN) == true)
			{
				SetMove({ 0,50 });
			}
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

	//사다리 키를 눌렀을 겨우
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
			Gravity_ = 0;
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
	IsColDown = false;
	PlayerRenderer_->SetPivot({ 0,50 });
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
		Attack(CurHoriDir_,{55,-20});
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
				IsColDown = true;
				//착지 사운드
				GameEngineSound::SoundPlayOneShot("Landing.mp3");
		}
		else
		{
			IsColDown = false;
		}
		
	}
	else //반대면 ( == 중력이 0 이하이면) 점프 상태
	{
		Move(float4::UP, -Gravity_);
		if (CheckPixelCol(float4::UP) == true) //머리에 충돌체를 박은 상태
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



	//땅에 닿았어 
	if (IsColDown == true)
	{
		Gravity_ = 0;
		CanJump_ = true; //점프를 다시 할 수 있더
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
	if (IsMoveVerKeyPress() == true && IsAttacking == false) // W or S를 눌렀다면
	{
		PlayerRenderer_->PauseOff();
		Move(WantVerDir_, 170.0f);//Climb Speed
		if (CheckPixelCol(float4::DOWN, LadderColor, true) == false
		|| (WantVerDir_.CompareInt2D(float4::UP) &&(CheckPixelCol(float4::ZERO, LadderColor, true) == false))) //윗쪽사다리가 끝나는 조건 Base 개념 : 내 발 아래 사다리 픽셀이 없으면 Climb종료
		{
			if (CheckPixelCol(float4::UP, LadderColor, true) == false) //윗쪽에서 사다리를 다오르면 사다리 픽셀 체크를 중심에서 함. 이렇게 안하면 사다리 애니메이션이 위에서 마칠 때 되게 어색해짐
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
	else //수직 키를 누르지 않았다면 애니메이션 정지
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

	if (IsMoveHoriKeyPress() == true) //수평 키를 눌렀을 경우 CurHoriDir_ 변경
	{
		CurHoriDir_ = WantHoriDir_;
	}

	if (GameEngineInput::GetInst()->IsDown("Attack") == true) //공격키를 눌렀을 경우
	{
		PlayerRenderer_->ChangeAnimation("RockMan_ClimbAttack_" + RockmanUtility::DirToStr(CurHoriDir_));
		//렌더러 위치 자연스럽게 틀기
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
	if (IsAttackEnd_ == true) //공격키를 누르고 일정 시간이 지난 후
	{
		PlayerRenderer_->ChangeAnimation("RockMan_Climb");
		PlayerRenderer_->SetPivot({ 0,50 }); //틀어진 랜더러 피벗 다시 원위치로
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
	CurHitTimer_ = 0.01; //CurHitTimer의 값을 살짝 건드려서 Update에서 타이머가 작동하게 한다.
}

void Player::HitUpdate()
{
	if (CurHitTimer_ < GetOutHitTimer_)
	{
		CurSpeed_ -= CurSpeed_ * GameEngineTime::GetDeltaTime();
		//중력가속도
		Gravity_ += AccGravity_ * GameEngineTime::GetDeltaTime();

		if (Gravity_ >= MaxGravity_)
		{
			Gravity_ = MaxGravity_;
		}
		if (CurSpeed_ < 0.5f)
		{
			CurSpeed_ = 0;
		}
		if (Gravity_ >= 0) //중력이 0이상이면 떨어진다wd
		{

			if (((CheckPixelCol(float4::DOWN, LadderColor) == true) && (CheckPixelCol(float4::UP, LadderColor) == false)))//사다리 픽셀 추가 검사
			{

			}
			else
			{
				Move(float4::DOWN, Gravity_);
			}

			//땅에 닿은 상태
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

					//무한루프 탈출을 위한 안전장치
					if (1.0f >= NextPos.Len2D())
					{
						break;
					}
				}
				float4 WantMovePos = NextPos - float4(0, GetScale().Half().y);
				SetMove(WantMovePos);
				IsColDown = true;
				//착지 사운드
				GameEngineSound::SoundPlayOneShot("Landing.mp3");
			}

		}

		Move(-CurHoriDir_, CurSpeed_); //히트 시 뒤로 밀려나는 이동량
	}
	else //Hit상태에서 탈출하는 경우
	{
		//아래 발판이 없을 경우
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
