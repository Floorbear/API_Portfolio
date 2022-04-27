#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include "GameManager.h"
#include "BackGround.h"
#include "Bullet.h"
#include <GameEngine/GameEngine.h>
#include "RockmanUtility.h"
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineCollision.h>
#include "RockmanStage.h"
#include "RockmanMonster.h"



Player::Player()
{
	InitPlayerPara();
	PlayerStateStr_[static_cast<int>(PlayerState::Idle)] = "Idle";
	PlayerStateStr_[static_cast<int>(PlayerState::Move)] = "Move";
	PlayerStateStr_[static_cast<int>(PlayerState::Jump)] = "Jump";
	PlayerStateStr_[static_cast<int>(PlayerState::Climb)] = "Climb";
	PlayerStateStr_[static_cast<int>(PlayerState::Hit)] = "Hit";

}

void Player::InitPlayerPara()
{
	MaxHP_ = 28;
	CurHP_ = MaxHP_;
	CurSpeed_ = 0.0f;
	CurState_ = PlayerState::Idle;
	AccSpeed_ = 800.0f;
	MaxSpeed_ = 350.0;

	Gravity_ = 500.0;
	AccGravity_ = 5000;
	MaxGravity_ = 800;
	JumpStrength_ = -600;

	CurHoriDir_ = float4::RIGHT;
	WantVerDir_ = float4::ZERO;

	CurHitTimer_ = 0;
	GetOutHitTimer_ = 0.45f;
	MaxHitTimer_ = 1.5f;
	HitAlpha_ = 40; //히트 시에 셋될 알파값
	CurBlinkTimer_ = 0;
	MaxBlinkTimer_ =0.12f;//이 시간이 지나면 알파값이 변화함
	IsHitAlphaOn_ = false;

	PlayerRenderer_ = nullptr;

	IsColHori = false;
	IsColUP = false;
	IsColDown = false;
	CurJumpTime_ = 0;
	MaxJumpTime_ = 0.25f;
	CanJump_ = true;
	IsAttacking = false;
	IsAttackEnd_ = false;
	AttackTickTime_ = 0.0f;
	MaxAttackTickTime_ = 0.45f;
	AttackCount_ = 0;
	MaxAttackCount_ = 3;
	PlayerCol_ = nullptr;
	CameraPosY_ = 0;
	CanActivate = true;

	PlayerRenderer_ = nullptr;
	HitEffect_Center_Renderer_ = nullptr;
	HitEffect_Top_Renderer_ = nullptr;
}

Player::~Player()
{
}

void Player::Start()
{

	//SetPosition(GameEngineWindow::GetScale().Half()+float4::UP*200+float4::RIGHT*-300);
	SetPosition({ 3500,700 });
	SetScale({ 100,100 });
	
	LoadAnimation();
	PlayerCol_ = CreateCollision("Player", { 60,80 });
	CameraDesY_ = CameraPosY_;
	StateChange(PlayerState::Idle);
}

void Player::Update()
{
	if (CanActivate == true)
	{
		StateUpdate();
		if (CurHitTimer_ == 0)
		{
			IsHitAlphaOn_ = false;
			CurBlinkTimer_ = 0;
			CheckMonsterCol();
		}
		else //히트 시 MaxHitTimer_시간동안 몬스터와의 충돌체크를 하지않는다. == 무적상태가 된다. & 무적상태일때 알파값 이펙트를 보여준다
		{
			CurBlinkTimer_ += GameEngineTime::GetDeltaTime();
			CurHitTimer_ += GameEngineTime::GetDeltaTime();

			if (CurBlinkTimer_ > MaxBlinkTimer_) //무적상태일때 깜박거림
			{
				if (IsHitAlphaOn_ == false)
				{
					IsHitAlphaOn_ = true;
					PlayerRenderer_->SetAlpha(HitAlpha_);
					HitEffect_Center_Renderer_->SetAlpha(HitAlpha_);
				}
				else
				{
					IsHitAlphaOn_ = false;
					PlayerRenderer_->SetAlpha(255);
					HitEffect_Center_Renderer_->SetAlpha(200);
				}
			}

			if (CurHitTimer_ >= MaxHitTimer_)
			{
				CurHitTimer_ = 0;
				PlayerRenderer_->SetAlpha(255);
			}
		}
		

		//공격 딜레이 체크
		if (IsAttacking == true)
		{
			AttackTickTime_ += GameEngineTime::GetDeltaTime();
			if (AttackTickTime_ >= MaxAttackTickTime_)
			{
				IsAttacking = false;
				AttackTickTime_ = 0.0f;
				AttackCount_ = 0;
				IsAttackEnd_ = true;
			}
		}
	}

	//맵 변경이 일어날때 카메라와 플레이어를 부드럽게 이동
	if (CameraDesY_ != CameraPosY_)
	{
		float VerDirY = CameraDesY_ - CameraPosY_;
		float4 VerDir = { 0,VerDirY };
		VerDir.Normal2D();
		CameraPosY_ += VerDir.y * 800 * GameEngineTime::GetDeltaTime();

		//플레이어의 y좌표를 조금씩 이동
		SetMove(VerDir * GameEngineTime::GetDeltaTime()*100.0f);

		//약간의 오차(카메라 무브시 델타타임으로 일어나는 오차값)가 일어나면 조절해준다.
		VerDir = { 0,CameraPosY_ - CameraDesY_ };
		if (VerDir.Len2D() < 0.5f)
		{
			CameraPosY_ = CameraDesY_;
		}


	}
	else //맵 변경이 종료되면
	{
		CanActivate = true;
		PlayerCol_->On();
	}


	//카메라 체크
	float4 CameraPos = { GetPosition().x - GameEngineWindow::GetScale().Half().x,CameraPosY_ };
	float BackGroundScale_X = GameManager::GetInst()->GetCurrentBackGround()->GetScale().x + GameManager::GetInst()->GetCurrentBackGround()->GetPosition().x;


	//카메라가 화면 밖으로 벗어나지 못하게 한다
	if (CameraPos.x <= GameManager::GetInst()->GetCurrentBackGround()->GetPosition().x)
	{
		CameraPos.x = GameManager::GetInst()->GetCurrentBackGround()->GetPosition().x;
	}
	if (CameraPos.x > BackGroundScale_X - GameEngineWindow::GetScale().x)
	{
		CameraPos.x = BackGroundScale_X - GameEngineWindow::GetScale().x;
	}

	GetLevel()->SetCameraPos(CameraPos);

}

void Player::Render()
{
	if (GameManager::GetInst()->GetIsDebugMode() == true)
	{
		RockmanUtility::DebugText(PlayerStateStr_[static_cast<int>(CurState_)] + "\n x :" +
			std::to_string(GetPosition().x) + "\n y :" + std::to_string(GetPosition().y), GetCameraEffectPosition() + float4(-90, 90));
	}

}

bool Player::CheckPixelCol(float4 _Dir, unsigned long _RGB, bool _CheckOnlyMid)
{ 
	//_Dir == left or right
	if (_Dir.CompareInt2D(float4::LEFT) == true || _Dir.CompareInt2D(float4::RIGHT) == true)
	{
		BackGround* CurBackGround = GameManager::GetInst()->GetCurrentBackGround();

		float4 CheckPos_Top = GetPosition() + float4((GetScale().Half().x-15) * _Dir.x, -GetScale().Half().y);
		float4 CheckPos_Mid = GetPosition() + float4((GetScale().Half().x-15) * _Dir.x, 0);
		float4 CheckPos_Bottom = GetPosition() + float4((GetScale().Half().x-15 )* _Dir.x, GetScale().Half().y-10);

		if (_CheckOnlyMid == true)
		{
			if (CurBackGround->IsBlocked(CheckPos_Mid, _RGB) == true)
			{
				return true;
			}
			return false;
		}

		if (CurBackGround->IsBlocked(CheckPos_Top,_RGB) ||
			CurBackGround->IsBlocked(CheckPos_Mid , _RGB) ||
			CurBackGround->IsBlocked(CheckPos_Bottom, _RGB)
			)
		{
			return true;
		}
	}

	//_Dir == Up or Down
	else if (_Dir.CompareInt2D(float4::DOWN) == true || _Dir.CompareInt2D(float4::UP) == true)
	{
		BackGround* CurBackGround = GameManager::GetInst()->GetCurrentBackGround();

		
		float4 CheckPos_Left = GetPosition() + float4(-GetScale().Half().x+20, _Dir.y*( GetScale().Half().y +1));//그래비티는 무조건 float4::down이 들어가니 (속력이 아닌 속도라서) Gravity로 부호를 체크해야한다
		float4 CheckPos_Mid = GetPosition() + float4(0, _Dir.y  *(GetScale().Half().y+1));
		float4 CheckPos_Right = GetPosition() + float4(GetScale().Half().x-20, _Dir.y *(GetScale().Half().y +1));


		if (_CheckOnlyMid == true)
		{
			if (CurBackGround->IsBlocked(CheckPos_Mid, _RGB) == true)
			{
				return true;
			}
			return false;
		}
		if (CurBackGround->IsBlocked(CheckPos_Left,_RGB) ||
			CurBackGround->IsBlocked(CheckPos_Mid,_RGB) ||
			CurBackGround->IsBlocked(CheckPos_Right,_RGB)
			)
		{
			return true;
		}
	}
	else if (_Dir.CompareInt2D(float4::ZERO) == true)
	{
		BackGround* CurBackGround = GameManager::GetInst()->GetCurrentBackGround();

		float4 CheckPos_Left = GetPosition() + float4(-GetScale().Half().x + 20,0);
		float4 CheckPos_Mid = GetPosition() + float4(0,0);
		float4 CheckPos_Right = GetPosition() + float4(GetScale().Half().x - 20,0);


		if (_CheckOnlyMid == true)
		{
			if (CurBackGround->IsBlocked(CheckPos_Mid, _RGB) == true)
			{
				return true;
			}
			return false;
		}
		if (CurBackGround->IsBlocked(CheckPos_Left, _RGB) ||
			CurBackGround->IsBlocked(CheckPos_Mid, _RGB) ||
			CurBackGround->IsBlocked(CheckPos_Right, _RGB)
			)
		{
			return true;
		}
	}
	return false;
}

void Player::Move(float4 _Dir, float _Speed)
{
	if (CheckPixelCol(_Dir) == true)
	{
		return;
	}

	SetMove(_Dir * GameEngineTime::GetDeltaTime() * _Speed);
}

void Player::GoToVer(float4 _VerDir)
{
	if (_VerDir.CompareInt2D(float4::UP) == false && _VerDir.CompareInt2D(float4::DOWN) == false)
	{
		MsgBoxAssert("잘못된 _VerDir");
	}
	CanActivate = false;
	PlayerCol_->Off();
	CameraDesY_ = GameManager::GetInst()->GetCurrentBackGround()->GetPosition().y;
	MoveToLadderPos();

}

bool Player::IsMoveVerKeyPress()
{
	if (GameEngineInput::GetInst()->IsPress("MoveUp") == true)
	{
		WantVerDir_ = float4::UP;
		return true;
	}
	else if (GameEngineInput::GetInst()->IsPress("MoveDown") == true)
	{
		WantVerDir_ = float4::DOWN;
		return true;
	}
	return false;
}

bool Player::IsMoveHoriKeyPress()
{
	if (GameEngineInput::GetInst()->IsPress("MoveRight") == true)
	{
		WantHoriDir_ = float4::RIGHT;
		return true;
	}
	else if (GameEngineInput::GetInst()->IsPress("MoveLeft") == true)
	{
		WantHoriDir_ = float4::LEFT;
		return true;
	}
	return false;
}

void Player::Attack(const float4& _Dir, const float4& _AttackPos)
{
	if (AttackCount_ < MaxAttackCount_)
	{
		//사운드
		GameEngineSound::SoundPlayOneShot("Bullet.mp3");
		AttackTickTime_ = 0.0f;
		IsAttacking = true;
		Bullet* NewBullet = GetLevel()->CreateActor<Bullet>(static_cast<int>(GameLayer::Bullet), "Bullet");
		NewBullet->SetBullet(GetPosition() + float4(_Dir.x * _AttackPos.x, _AttackPos.y), _Dir);
		AttackCount_++;
	}
}
void Player::CheckMonsterCol()
{
	std::vector<GameEngineCollision*> MonsterColList;
	RockmanMonster* Monster = nullptr;
	if (PlayerCol_->CollisionResult("MonsterCol", MonsterColList, CollisionType::Rect, CollisionType::Rect) == true)
	{
		for (GameEngineCollision* MonsterCol : MonsterColList)
		{
			Monster = dynamic_cast<RockmanMonster*>(MonsterCol->GetActor());
			CurHP_ -= Monster->GetAttackDmg();
			CurHoriDir_ = float4(Monster->GetPosition().x - GetPosition().x, 0);
			CurHoriDir_.Normal2D();
			break;
		}

		StateChange(PlayerState::Hit);
		/*if (CurHP_ <= 0)
		{
			CurHP_ = 0;
		}
		else
		{
			StateChange(PlayerState::Hit);
		}*/
}
}

