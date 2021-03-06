#include "Cutman.h"
#include <GameEngine/GameEngineRenderer.h>
#include "RockManEnum.h"
#include "RockmanUtility.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "Player.h"
#include "BackGround.h"
#include "GameManager.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "MonsterBullet.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineSound.h>
#include "Bullet.h"
#include "BossHPBar.h"
#include "BossDieEffect.h"
#include "RockmanItem.h"
#include "RockmanStage.h"
Cutman::Cutman():
	HitEffect_Center_Renderer_(nullptr),
	HitEffect_Top_Renderer_(nullptr)
{
}

Cutman::~Cutman()
{
}

void Cutman::Update()
{
	RockmanMonster::Update();
	CutmanBulletCheck();
	if (CurHitTime_ > 0)
	{
		CurHitTime_ += GameEngineTime::GetDeltaTime();
		CurBlinkTime_ += GameEngineTime::GetDeltaTime();

		if (CurBlinkTime_ >= 0.12f) //무적상태일때 깜빡거린ㅁ
		{
			if (IsHitAlphaOn_ == false)
			{
				IsHitAlphaOn_ = true;
				MonsterRenderer_->SetAlpha(40);
				HitEffect_Center_Renderer_->SetAlpha(40);
			}
			else
			{
				IsHitAlphaOn_ = false;
				MonsterRenderer_->SetAlpha(255);
				HitEffect_Center_Renderer_->SetAlpha(200);
			}
		}

		if (CurHitTime_ > 1.5f) //1.2초뒤 무적이 풀린다
		{
			IsHitAlphaOn_ = false;
			CurBlinkTime_ = 0;
			CurHitTime_ = 0;
			MonsterRenderer_->SetAlpha(255);
		}
	}

	//최초의 연출 파트
	if (IsFirst_ == true)
	{
		CurHPFloat_ += 18*GameEngineTime::GetDeltaTime();
		CurHP_ = static_cast<int>(CurHPFloat_);
		if (CurHP_ >= MaxHP_)
		{
			IsFirst_ = false;
			GameManager::GetInst()->GetPlayer()->OnCanActivate();
			ChangeState(MonsterState::Move);
		}
	}

	//죽을때 화면 멈추는 연출
	if (IsWillDead_ == true)
	{
		RockmanStage* CurrentStage = dynamic_cast<RockmanStage*>(GetLevel());
		CurrentStage->Bgm_.Stop();
		DeathTimer_ -= GameEngineTime::GetDeltaTime();
		CanActivate = false;
		MonsterRenderer_->PauseOn();
		Player_->OffCanActivate();
		if (DeathTimer_ <= 0)
		{
			Player_->OnCanActivate();
			Die();

		}
	}

	//x왼쪽으로 안빠져나가게
	BackGround* CurBackground = GameManager::GetInst()->GetCurrentBackGround();
	if (GetPosition().x < CurBackground->GetPosition().x + 50)
	{
		SetPosition({ CurBackground->GetPosition().x + 50,GetPosition().y });
	}
}

void Cutman::InitMonster()
{
	IsBossType_ = true;
	SetScale({ 60,80 });
	//스테이터스
	AttackDamage_ = 3;//Default 3

	DropScore_ = 500;

	CurState_ = MonsterState::Idle;

	Default_Speed_ = 250.0f;
	Speed_ = Default_Speed_;
	AttackStartRange_ = 200.0f;

	Default_DeathTimer_ = 1.5f;
	DeathTimer_ = Default_DeathTimer_;
	MaxHP_ = 28;
	CurHP_ = 0;
	CurHPFloat_ = 0;

	//공격관련
	IsAttacking_ = false;
	HaveWeaponStr_[0] = "HaveWeapon";
	HaveWeaponStr_[1] = "Attacking";

	//시간관련
	CurIdleTime_ = 0;
	MaxIdleTime_ = 1.0f;
	AttackStartWaitTime_ = 0;
	AttackJudgmentTime_ = 0;
	JumpAttackJudgmentTime_ = 0;
	CurHitTime_ = 0;
	CurBlinkTime_ = 0;
	IsHitAlphaOn_ = false;
	AttackStartCoolTime_ = 0;

	//중력관련
	Gravity_ = 0;

	IsFirst_ = true;
	IsWillDead_ = false;

}

void Cutman::InitRenderer()
{
	//렌더러 애니메이션 셋팅
	MonsterRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Monster), RenderPivot::CENTER,float4(0,40));
	HitEffect_Center_Renderer_ = CreateRenderer(static_cast<int>(GameLayer::Monster), RenderPivot::CENTER);
	HitEffect_Top_Renderer_ = CreateRenderer(static_cast<int>(GameLayer::Monster), RenderPivot::CENTER, float4(0, -50));
	MonsterRenderer_->SetTransColor(TransColor);
	HitEffect_Center_Renderer_->SetTransColor(RGB(255, 255, 255));
	HitEffect_Top_Renderer_->SetTransColor(RGB(255, 255, 255));
	MonsterRenderer_->CreateAnimation("Cutman_Right.bmp", "Cutman_Idle_HaveWeaponRight", 0, 1, 0.1f);
	MonsterRenderer_->CreateAnimation("Cutman_Left.bmp", "Cutman_Idle_HaveWeaponLeft", 0, 1, 0.1f);
	MonsterRenderer_->CreateAnimation("Cutman_Right.bmp", "Cutman_Move_HaveWeaponRight", 2, 4, 0.1f);
	MonsterRenderer_->CreateAnimation("Cutman_Left.bmp", "Cutman_Move_HaveWeaponLeft", 2, 4, 0.1f);
	MonsterRenderer_->CreateAnimation("Cutman_Left.bmp", "Cutman_Jump_HaveWeaponLeft", 5, 5, 0.001f,false);
	MonsterRenderer_->CreateAnimation("Cutman_Right.bmp", "Cutman_Jump_HaveWeaponRight", 5, 5, 0.001f, false);

	MonsterRenderer_->CreateAnimation("Cutman_Right.bmp", "Cutman_Idle_AttackingRight", 8, 9, 0.1f);
	MonsterRenderer_->CreateAnimation("Cutman_Left.bmp", "Cutman_Idle_AttackingLeft", 8, 9, 0.1f);
	MonsterRenderer_->CreateAnimation("Cutman_Right.bmp", "Cutman_Move_AttackingRight", 10, 12, 0.1f);
	MonsterRenderer_->CreateAnimation("Cutman_Left.bmp", "Cutman_Move_AttackingLeft", 10, 12, 0.1f);
	MonsterRenderer_->CreateAnimation("Cutman_Left.bmp", "Cutman_Jump_AttackingLeft", 13, 13, 0.001f, false);
	MonsterRenderer_->CreateAnimation("Cutman_Right.bmp", "Cutman_Jump_AttackingRight", 13, 13, 0.001f, false);

	MonsterRenderer_->CreateAnimation("Cutman_Right.bmp", "Cutman_Attack_Right", 6, 7, 0.25f, false);
	MonsterRenderer_->CreateAnimation("Cutman_Left.bmp", "Cutman_Attack_Left", 6, 7, 0.25f, false);

	MonsterRenderer_->CreateAnimation("Cutman_Right.bmp", "Cutman_Hit_HaveWeaponRight", 3, 3, 0.25f, false);
	MonsterRenderer_->CreateAnimation("Cutman_Left.bmp", "Cutman_Hit_HaveWeaponLeft", 3, 3, 0.25f, false);
	MonsterRenderer_->CreateAnimation("Cutman_Right.bmp", "Cutman_Hit_AttackingRight",11, 11, 0.25f, false);
	MonsterRenderer_->CreateAnimation("Cutman_Left.bmp", "Cutman_Hit_AttackingLeft", 11, 11, 0.25f, false);

	HitEffect_Center_Renderer_->CreateAnimation("HitEffect_Center.bmp", "HitEffect_Center_On", 0, 0, 0.05f, true);
	HitEffect_Center_Renderer_->CreateAnimation("HitEffect_Center.bmp", "HitEffect_Center_Off", 1, 1, 0.05f, false);
	HitEffect_Top_Renderer_->CreateAnimation("HitEffect_Top.bmp", "HitEffect_Top_On", 0, 3, 0.07f, false);
	HitEffect_Top_Renderer_->CreateAnimation("HitEffect_Top.bmp", "HitEffect_Top_Off", 3, 3, 0.07f, false);

	HitEffect_Center_Renderer_->ChangeAnimation("HitEffect_Center_Off");
	HitEffect_Top_Renderer_->ChangeAnimation("HitEffect_Top_Off");

	HitEffect_Center_Renderer_->SetAlpha(140);
	//사망 애니메이션
	MonsterRenderer_->CreateAnimation("Explosion.bmp", "Die", 0, 4, 0.05f, false);

	MonsterRenderer_->ChangeAnimation("Cutman_Idle_"+HaveWeaponStr_[static_cast<int>(IsAttacking_)]+"Left");
}

void Cutman::ChangeIdleAni()
{
	CurHoriDir_ = float4(Player_->GetPosition().x - GetPosition().x, 0);
	CurHoriDir_.Normal2D();
	MonsterRenderer_->ChangeAnimation("Cutman_Idle_" + HaveWeaponStr_[static_cast<int>(IsAttacking_)] + RockmanUtility::DirToStr(CurHoriDir_));
}

void Cutman::SetMonster()
{
	//콜리전 생성
	MonsterContactCol_ = CreateCollision("MonsterCol", GetScale());

	//HP바 생성
	CurHPBar_ = GetLevel()->CreateActor<BossHPBar>(static_cast<int>(GameLayer::UI), "BossHPbar");
	CurHPBar_->SetCutman(this);

}

void Cutman::IdleStart()
{

	ChangeIdleAni();
	CurIdleTime_ = 0;
}

void Cutman::IdleUpdate()
{
	CurIdleTime_ += GameEngineTime::GetDeltaTime();
	if (CurIdleTime_ >= MaxIdleTime_)
	{
		ChangeState(MonsterState::Move);
		return;
	}
}

void Cutman::MoveStart()
{
	CurHoriDir_ = float4(Player_->GetPosition().x - GetPosition().x, 0);
	CurHoriDir_.Normal2D();
	Speed_ = Default_Speed_;
	MonsterRenderer_->ChangeAnimation("Cutman_Move_" + HaveWeaponStr_[static_cast<int>(IsAttacking_)] + RockmanUtility::DirToStr(CurHoriDir_));
}

void Cutman::MoveUpdate()
{
	//컷맨은 플레이어가 있는 방향으로 업데이트하고, 애니메이션을 최신화 합니다
	float4 WantPos = float4(Player_->GetPosition().x - GetPosition().x, 0);
	float4 WantDir = WantPos;
	WantDir.Normal2D();
	if (CurHoriDir_.CompareInt2D(WantDir) == false)
	{
		CurHoriDir_ = WantDir;
		MonsterRenderer_->ChangeAnimation("Cutman_Move_" + HaveWeaponStr_[static_cast<int>(IsAttacking_)] + RockmanUtility::DirToStr(CurHoriDir_));
	}

	//이동상태가 1초이상(누적) 지속됐으면, 70%확률로 공격을 한다
	AttackJudgmentTime_ += GameEngineTime::GetDeltaTime();
	if (AttackJudgmentTime_ >= 1.0f)
	{
		AttackJudgmentTime_ = 0;
		if (IsAttacking_ == false)
		{
			GameEngineRandom NewRandom;
			int RandomValue = NewRandom.RandomInt(0, 100);
			if (RandomValue > 30)
			{
				ChangeState(MonsterState::Attack);
				return;
			}
		}
	}

	if (WantPos.Len2D() < AttackStartRange_)
	{
		GameEngineRandom NewRandom;	
		Gravity_ = NewRandom.RandomFloat(-2100, -1500);;
		ChangeState(MonsterState::Jump);
		return;
	}

	//아래 바닥이 없는경우 점프 상태로
	if (CheckPixelCol(float4::DOWN, WallColor, false) == false)
	{
		Gravity_ = 0;
		ChangeState(MonsterState::Jump);
		return;
	}

	//앞에 벽이 있으면  점프상태로
	if (CheckPixelCol(CurHoriDir_, WallColor, false) == true)
	{
		GameEngineRandom NewRandom;
		Gravity_ = NewRandom.RandomFloat(-2100, -1500);;
		ChangeState(MonsterState::Jump);
		return;
	}

	Move(CurHoriDir_, Speed_,WallColor,false);
}

void Cutman::JumpStart()
{
	MonsterRenderer_->ChangeAnimation("Cutman_Jump_" + HaveWeaponStr_[static_cast<int>(IsAttacking_)] + RockmanUtility::DirToStr(CurHoriDir_));
	AttackStartCoolTime_ = 0;
}

void Cutman::JumpUpdate()
{
	//점프공격
	//이동상태가 1.8초이상(누적) 지속됐으면, 70%확률로 공격을 한다
	JumpAttackJudgmentTime_ += GameEngineTime::GetDeltaTime();
	if (JumpAttackJudgmentTime_ >= 1.2f)
	{
		JumpAttackJudgmentTime_ = 0;
		if (IsAttacking_ == false)
		{
			GameEngineRandom NewRandom;
			int RandomValue = NewRandom.RandomInt(0, 100);
			if (RandomValue > 30)
			{
				if (IsAttacking_ == false) //공격 시간
				{
					CurHoriDir_ = float4(Player_->GetPosition().x - GetPosition().x, 0);
					CurHoriDir_.Normal2D();
					IsAttacking_ = true;
					MonsterRenderer_->ChangeAnimation("Cutman_Attack_" + RockmanUtility::DirToStr(CurHoriDir_));
				}
			}
		}
	}

	if (CurBullet_ == nullptr && AttackStartCoolTime_ >= 0.2f && IsAttacking_ == true)
	{
		float4 PlayerDir = float4(Player_->GetPosition().x - GetPosition().x, Player_->GetPosition().y - GetPosition().y);
		float Distance = PlayerDir.Len2D() * 1.6f; //플레이어가 있는 지점보다 살짝 더 뒤까지 발사시킨다
		PlayerDir.Normal2D();
		GameEngineSound::SoundPlayOneShot("MetShoot.mp3");
		CurBullet_ = GetLevel()->CreateActor<MonsterBullet>(static_cast<int>(GameLayer::Bullet), "CutmanBullet");
		CurBullet_->SetCutman(this);
		CurBullet_->SetBullet(GetPosition(), GetPosition() + PlayerDir * Distance, 3, MonsterBulletType::CutmanBullet);
	}

	//공격 On이면 선딜쿨타이머가 돈다
	if (IsAttacking_ == true)
	{
		AttackStartCoolTime_ += GameEngineTime::GetDeltaTime();
	}

	Gravity_ += 5000 * GameEngineTime::GetDeltaTime();
	Speed_ -= Speed_ * 0.5f * GameEngineTime::GetDeltaTime();

	///////////////////////////////////////////////////////////////////////////

	//수평 이동
	if (MonsterRenderer_->IsEndAnimation() == true)
	{
		Move(CurHoriDir_, Speed_, WallColor, false);
	}

	//수직이동
	if (Gravity_ >= 0) //떨어지고 있는 상태라면
	{
		if (CheckPixelCol(float4::DOWN, WallColor, false) == true)//떨어지는 상태에서만 발판체크
		{
			//땅에 닿은 상태
			if (CheckPixelCol(float4::DOWN, WallColor,false) == true)
			{
				BackGround* CurBackGround = GameManager::GetInst()->GetCurrentBackGround();

				float4 NextPos = float4(0, (GetScale().Half().y + 1));
				float4 CheckPos_Mid = GetPosition() + float4(0, (GetScale().Half().y + 1));
				float Len = NextPos.Len2D();

				while (
					true == CurBackGround->IsBlocked(CheckPos_Mid, WallColor))
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
			}
			if (MonsterRenderer_->IsEndAnimation() == true)
			{
				ChangeState(MonsterState::Move);
			}		
			return;
		}

		Move(float4::DOWN, Gravity_, WallColor, false);
	}
	else //상승하고 있는 상태면
	{
		Move(float4::UP, -Gravity_, WallColor, false);
	}
}

void Cutman::AttackStart()
{

	ChangeIdleAni();
	AttackStartWaitTime_ = 0;
	AttackStartCoolTime_ = 0;
}

void Cutman::AttackUpdate()
{
	AttackStartWaitTime_ += GameEngineTime::GetDeltaTime();
	if (AttackStartWaitTime_ >= 1.1f && IsAttacking_ == false) //공격 시간
	{
		CurHoriDir_ = float4(Player_->GetPosition().x - GetPosition().x, 0);
		CurHoriDir_.Normal2D();
		IsAttacking_ = true;
		MonsterRenderer_->ChangeAnimation("Cutman_Attack_" + RockmanUtility::DirToStr(CurHoriDir_));
	}

	if (CurBullet_ == nullptr && AttackStartCoolTime_ >= 0.2f && IsAttacking_ == true)
	{
		float4 PlayerDir = float4(Player_->GetPosition().x - GetPosition().x, Player_->GetPosition().y - GetPosition().y);
		float Distance = PlayerDir.Len2D() * 1.6f; //플레이어가 있는 지점보다 살짝 더 뒤까지 발사시킨다
		PlayerDir.Normal2D();
		GameEngineSound::SoundPlayOneShot("MetShoot.mp3");
		CurBullet_ = GetLevel()->CreateActor<MonsterBullet>(static_cast<int>(GameLayer::Bullet), "CutmanBullet");
		CurBullet_->SetCutman(this);
		CurBullet_->SetBullet(GetPosition(), GetPosition() + PlayerDir * Distance, 3, MonsterBulletType::CutmanBullet);
	}

	//공격 On이면 선딜쿨타이머가 돈다
	if (IsAttacking_ == true)
	{
		AttackStartCoolTime_ += GameEngineTime::GetDeltaTime();
	}

	if (IsAttacking_ == true)
	{

		if (AttackStartWaitTime_ >= 1.6f)
		{
			ChangeState(MonsterState::Move);
			return;
		}
	}
}

void Cutman::HitStart()
{
	CurHitTime_ += GameEngineTime::GetDeltaTime();
	MonsterRenderer_->ChangeAnimation("Cutman_Hit_" + HaveWeaponStr_[static_cast<int>(IsAttacking_)] + RockmanUtility::DirToStr(CurHoriDir_));
	HitEffect_Center_Renderer_->ChangeAnimation("HitEffect_Center_On");
	HitEffect_Top_Renderer_->ChangeAnimation("HitEffect_Top_On");
	Speed_ = Default_Speed_;
	Gravity_ = 0;
}

void Cutman::HitUpdate()
{
	if (CurHitTime_ < 0.45f)
	{
		Speed_ -= Speed_ * GameEngineTime::GetDeltaTime();
		//중력가속도
		Gravity_ += 5000 * GameEngineTime::GetDeltaTime();


		if (Speed_ < 0.5f)
		{
			Speed_ = 0;
		}
		//수직이동
		if (Gravity_ >= 0) //떨어지고 있는 상태라면
		{
			Move(float4::DOWN, Gravity_, WallColor, false);

			if (CheckPixelCol(float4::DOWN, WallColor, false) == true)//떨어지는 상태에서만 발판체크
			{
				//땅에 닿은 상태
				if (CheckPixelCol(float4::DOWN, WallColor, false) == true)
				{
					BackGround* CurBackGround = GameManager::GetInst()->GetCurrentBackGround();

					float4 NextPos = float4(0, (GetScale().Half().y + 1));
					float4 CheckPos_Mid = GetPosition() + float4(0, (GetScale().Half().y + 1));
					float Len = NextPos.Len2D();

					while (
						true == CurBackGround->IsBlocked(CheckPos_Mid, WallColor))
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
				}
			}
		}

		Move(-CurHoriDir_, Speed_,WallColor,false); //히트 시 뒤로 밀려나는 이동량
	}
	else //Hit상태에서 탈출하는 경우
	{
		//아래 발판이 없을 경우
		if (CheckPixelCol(float4::DOWN, WallColor,false) == false)
		{
			HitEffect_Center_Renderer_->ChangeAnimation("HitEffect_Center_Off");
			HitEffect_Top_Renderer_->ChangeAnimation("HitEffect_Top_Off");
			ChangeState(MonsterState::Jump);
			return;
		}
		HitEffect_Center_Renderer_->ChangeAnimation("HitEffect_Center_Off");
		HitEffect_Top_Renderer_->ChangeAnimation("HitEffect_Top_Off");
		ChangeState(MonsterState::Move);
		return;
	}
}

void Cutman::HitByBulletCheck()
{
	if (CurHitTime_ != 0)
	{
		return;
	}
	RockmanMonster::HitByBulletCheck();
}

void Cutman::Hit(BulletType _BulletType, const float4& _BulletPos)
{

	switch (_BulletType)
	{
	case BulletType::Normal:
		GameEngineSound::SoundPlayOneShot("EnemyDeath.mp3");
		CurHP_ -= 3;
		if (CurHP_ <= 0)
		{
			CurHP_ = 0;
		}
		break;
	default:
		break;
	}

	CurHoriDir_ = float4(Player_->GetPosition().x - GetPosition().x, 0);
	CurHoriDir_.Normal2D();

	//체력이 0보다 작다면 
	if (CurHP_ <= 0 && CanActivate == true)
	{
		IsWillDead_ = true;
		return;
	}
	else if (CurHP_ > 0 && CanActivate == true)
	{
		ChangeState(MonsterState::Hit);
	}
}

void Cutman::Die()
{
	CanActivate = false;
	MonsterRenderer_->PauseOn();
	BossDieEffect* DieEffect = GetLevel()->CreateActor<BossDieEffect>(static_cast<int>(GameLayer::Object), "DieEffect");
	DieEffect->SetPosition(GetPosition());
	RockmanItem* NewItem = GetLevel()->CreateActor<RockmanItem>(static_cast<int>(GameLayer::Object), "Item");
	NewItem->SetItem({ 12723, -4900 });
	CurHPBar_->Death();
	GameManager::GetInst()->AddScore(DropScore_);
	MonsterContactCol_->Off();
	Speed_ = Default_Speed_;


	Death();
}

bool Cutman::CheckPixelCol(float4 _Dir, unsigned long _RGB, bool _CheckOnlyMid)
{
	//_Dir == left or right
	if (_Dir.CompareInt2D(float4::LEFT) == true || _Dir.CompareInt2D(float4::RIGHT) == true)
	{
		BackGround* CurBackGround = GameManager::GetInst()->GetCurrentBackGround();

		float4 CheckPos_Top = GetPosition() + float4((GetScale().Half().x - 15) * _Dir.x, -GetScale().Half().y);
		float4 CheckPos_Mid = GetPosition() + float4((GetScale().Half().x - 15) * _Dir.x, 0);
		float4 CheckPos_Bottom = GetPosition() + float4((GetScale().Half().x - 15) * _Dir.x, GetScale().Half().y - 10);

		if (_CheckOnlyMid == true)
		{
			if (CurBackGround->IsBlocked(CheckPos_Mid, _RGB) == true)
			{
				return true;
			}
			return false;
		}

		if (CurBackGround->IsBlocked(CheckPos_Top, _RGB) ||
			CurBackGround->IsBlocked(CheckPos_Mid, _RGB) ||
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


		float4 CheckPos_Left = GetPosition() + float4(-GetScale().Half().x + 20, _Dir.y * (GetScale().Half().y + 1));//그래비티는 무조건 float4::down이 들어가니 (속력이 아닌 속도라서) Gravity로 부호를 체크해야한다
		float4 CheckPos_Mid = GetPosition() + float4(0, _Dir.y * (GetScale().Half().y + 1));
		float4 CheckPos_Right = GetPosition() + float4(GetScale().Half().x - 20, _Dir.y * (GetScale().Half().y + 1));


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
	else if (_Dir.CompareInt2D(float4::ZERO) == true)
	{
		BackGround* CurBackGround = GameManager::GetInst()->GetCurrentBackGround();

		float4 CheckPos_Left = GetPosition() + float4(-GetScale().Half().x + 20, 0);
		float4 CheckPos_Mid = GetPosition() + float4(0, 0);
		float4 CheckPos_Right = GetPosition() + float4(GetScale().Half().x - 20, 0);


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

void Cutman::Move(float4 _Dir, float _Speed, unsigned long _RGB, bool _CheckOnlyMid)
{
	if (CheckPixelCol(_Dir, _RGB, _CheckOnlyMid) == true)
	{
		return;
	}

	SetMove(_Dir * GameEngineTime::GetDeltaTime() * _Speed);
}

void Cutman::CutmanBulletCheck()
{
	if (MonsterContactCol_->CollisionCheck("MonsterBullet", CollisionType::Rect, CollisionType::Rect) == true)
	{
		if (CurBullet_ == nullptr)
		{
			return;
		}

		if (CurBullet_->GetIsReturn() == false) //돌아오는 상태가 아니면 종료
		{
			return;
		}

		CurBullet_->Death();
		CurBullet_ = nullptr;
		IsAttacking_ = false;

		//애니메이션 최신화
		switch (CurState_)
		{
		case MonsterState::Idle:
			ChangeIdleAni();
			break;
		case MonsterState::Attack:
			break;
		case MonsterState::Move:
			MonsterRenderer_->ChangeAnimation("Cutman_Move_" + HaveWeaponStr_[static_cast<int>(IsAttacking_)] + RockmanUtility::DirToStr(CurHoriDir_));
			break;
		case MonsterState::Jump:
			MonsterRenderer_->ChangeAnimation("Cutman_Jump_" + HaveWeaponStr_[static_cast<int>(IsAttacking_)] + RockmanUtility::DirToStr(CurHoriDir_));
			break;
		case MonsterState::Max:
			break;
		default:
			break;
		}

	}
}
