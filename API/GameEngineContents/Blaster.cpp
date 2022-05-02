#include "Blaster.h"
#include <GameEngine/GameEngineRenderer.h>
#include "RockmanUtility.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "Player.h"
#include "MonsterBullet.h"
#include <GameEngineBase/GameEngineSound.h>
Blaster::Blaster()
{
}

Blaster::~Blaster()
{
}

void Blaster::InitMonster()
{
	SetScale({ 50,60 });
	//스테이터스
	AttackDamage_ = 1;//Default

	DropScore_ = 200;

	CurState_ = MonsterState::Idle;

	Default_Speed_ = 0;
	Speed_ = Default_Speed_;
	AttackStartRange_ = 500.0f;

	DefaultIdleTime_ = 2.0f;
	CurIdleTime_ = DefaultIdleTime_;

	//공격관련 파라미터
	MaxAttackCount_ = 4;
	CurAttackCount_ = 0;
	CurAttackTickTime_ = 0;
	MaxAttackTickTime_ = 0.8f;

	Default_DeathTimer_ = 1.0f;
	DeathTimer_ = Default_DeathTimer_;
	MaxHP_ = 1;
	CurHP_ = MaxHP_;

	CurWaitTime_ = 0;
}

void Blaster::InitRenderer()
{
	//렌더러 애니메이션 셋팅
	MonsterRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Monster), RenderPivot::CENTER);
	MonsterRenderer_->SetTransColor(TransColor);
	MonsterRenderer_->CreateAnimation("Blaster_Close_Left.bmp", "Blaster_Close_Left", 0, 3, 0.15f,false);
	MonsterRenderer_->CreateAnimation("Blaster_Close_Right.bmp", "Blaster_Close_Right", 0, 3, 0.15f, false);
	MonsterRenderer_->CreateAnimation("Blaster_Open_Left.bmp", "Blaster_Open_Left", 0, 3, 0.15f, false);
	MonsterRenderer_->CreateAnimation("Blaster_Open_Right.bmp", "Blaster_Open_Right", 0, 3, 0.15f, false);
	MonsterRenderer_->CreateAnimation("Blaster_Open_Left.bmp", "Blaster_Idle_Left", 0, 0, 0.15f, false);
	MonsterRenderer_->CreateAnimation("Blaster_Open_Right.bmp", "Blaster_Idle_Right", 0, 0, 0.15f, false);

	//사망 애니메이션
	MonsterRenderer_->CreateAnimation("Explosion.bmp", "Die", 0, 4, 0.05f, false);

	MonsterRenderer_->ChangeAnimation("Blaster_Idle_Left");
}

void Blaster::ChangeIdleAni()
{
	MonsterRenderer_->ChangeAnimation("Blaster_Idle_" + RockmanUtility::DirToStr(CurHoriDir_));
	MonsterRenderer_->SetPivot({ static_cast<float>(-25 * CurHoriDir_.x),0 });
}

void Blaster::SetMonster()
{
	MonsterContactCol_ = CreateCollision("MonsterCol", GetScale());

}

void Blaster::IdleStart()
{
	ChangeIdleAni();
	CurAttackTickTime_ = 0;
	CurAttackCount_ = 0;
	CurIdleTime_ = DefaultIdleTime_;
}

void Blaster::IdleUpdate()
{
	CurIdleTime_ -= GameEngineTime::GetDeltaTime();

	if (CurIdleTime_ <= 0)
	{
		CurIdleTime_ = DefaultIdleTime_;
		ChangeState(MonsterState::Attack);
		return;
	}
}

void Blaster::AttackStart()
{
	MonsterRenderer_->ChangeAnimation("Blaster_Open_" + RockmanUtility::DirToStr(CurHoriDir_));
	CurWaitTime_ = 0;
}

void Blaster::AttackUpdate()
{
	CurWaitTime_ += GameEngineTime::GetDeltaTime();
	if (CurWaitTime_ > 0.3)
	{
		if (CurAttackCount_ < MaxAttackCount_)
		{
			CurAttackTickTime_ += GameEngineTime::GetDeltaTime();
			if (CurAttackTickTime_ >= MaxAttackTickTime_) //총알발사
			{
				//CurAttCount에 따라 총알을 발사하는 방향이 다름
				float4 BulletDir = float4(0, 0);
				switch (CurAttackCount_)
				{
				case 0:
					BulletDir = float4(1, -1);
					break;
				case 1:
					BulletDir = float4(5, -1);
					break;
				case 2:
					BulletDir = float4(5, 1);
					break;
				case 3:
					BulletDir = float4(1, 1);
					break;
				default:
					break;
				}
				BulletDir.Normal2D();
				CurAttackTickTime_ = 0;
				MonsterBullet* NewBullet = GetLevel()->CreateActor<MonsterBullet>(static_cast<int>(GameLayer::Bullet), "EnemyBullet");
				NewBullet->SetBullet(GetPosition() + float4(20 * CurHoriDir_.x, 0), float4(BulletDir.x * CurHoriDir_.x, BulletDir.y), 2);//2
				GameEngineSound::SoundPlayOneShot("MetShoot.mp3");
				CurAttackCount_++;
			}
		}
	}

	//공격을 다하면 뚜껑을 닫는다
	if (CurAttackCount_ >= MaxAttackCount_)
	{
		MonsterRenderer_->ChangeAnimation("Blaster_Close_" + RockmanUtility::DirToStr(CurHoriDir_));
		if (MonsterRenderer_->IsEndAnimation() == true)
		{
			CurIdleTime_ = DefaultIdleTime_;
			ChangeState(MonsterState::Idle);
			return;
		}
	}
}

void Blaster::Hit(BulletType _BulletType)
{
	switch (_BulletType)
	{
	case BulletType::Normal:
		if (CurState_ == MonsterState::Idle)
		{
			//팅하는 사운드
			GameEngineSound::SoundPlayOneShot("ShootRecoil.mp3");
		}
		else
		{
			GameEngineSound::SoundPlayOneShot("EnemyDeath.mp3");
			CurHP_--;
		}
		break;
	default:
		break;
	}

	//체력이 0보다 작다면 
	if (CurHP_ <= 0 && CanActivate == true)
	{
		Die();
	}
}

void Blaster::SetDir(const float4& _Dir)
{
	CurHoriDir_ = _Dir;
	ChangeIdleAni();
}
