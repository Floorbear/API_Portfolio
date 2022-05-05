#include "RockmanMonster.h"
#include <GameEngine/GameEngineRenderer.h>
#include "RockmanUtility.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameManager.h"
#include "Player.h"
#include "BackGround.h"
#include <GameEngine/GameEngineCollision.h>
#include "Bullet.h"
#include <GameEngineBase/GameEngineSound.h>
#include "RockmanItem.h"
#include <GameEngineBase/GameEngineRandom.h>

RockmanMonster::RockmanMonster()
	:DeletePos_(float4(-1000,-1000)),
	MonsterRenderer_(nullptr),
	MonsterContactCol_(nullptr),
	Player_ (nullptr),
	CurHoriDir_(float4::ZERO),
	WantHoriDir_(float4::ZERO),
	CanActivate(true),
	SpawnPos_({ -1000, -1000 }),
	Index_(0)
{
	StateStr_[static_cast<int>(MonsterState::Idle)] = "Idle";
	StateStr_[static_cast<int>(MonsterState::Attack)] = "Attack";
}

RockmanMonster::~RockmanMonster()
{
}

void RockmanMonster::Start()
{
	InitMonster(); //몬스터의 기본적인 스테이터스가 초기화된다.
	InitRenderer();
	SetMonster();
}

void RockmanMonster::Update()
{
	if (CanActivate == true)
	{
		if ((GetLevel()->GetCameraPos().x - 30 < GetPosition().x && GetPosition().x < GetLevel()->GetCameraPos().x + 1060) &&
			(GetLevel()->GetCameraPos().y < GetPosition().y && GetPosition().y < GetLevel()->GetCameraPos().y + 960)) //카메라 안(살짝 카메라보다 큰 카메라)에 있어야 활동을 한다.
		{
			//플레이어 참조
			Player_ = GameManager::GetInst()->GetPlayer();
			if (Player_ != nullptr)
			{
				//맵의 변경을 계속 감시해서 맵변경이 일어나면 몬스터의 활동을 중지시킨다.
				size_t Background_Index = GameManager::GetInst()->GetCurrentBackGround()->GetIndex();
				if (Index_ == Background_Index && Player_->GetCanActivate() == true )
				{
					if (Player_->GetCurPlayerState() != PlayerState::Die) //플레이어가 Die상태일경우 잠시 몬스터가 멈춘다.
					{
						UpdateState();
						HitByBulletCheck();
					}
				}
			}
		}
		else //몬스터가 카메라 밖에 활동을 중지시킨다 (== 몬스터의 Pos를 -1000,-1000으로 옮긴다). , 몬스터의 위치를 SpawnPos로 옴긴다.
		{	
			Speed_ = Default_Speed_;
			ChangeState(MonsterState::Idle);
			//카메라가 스폰포인트 위치 밖에 있으면, 몬스터의 위치를 SpawnPos로 옮긴다
			if ((GetLevel()->GetCameraPos().x - 30 < SpawnPos_.x && SpawnPos_.x < GetLevel()->GetCameraPos().x + 1060) &&
				(GetLevel()->GetCameraPos().y < SpawnPos_.y && SpawnPos_.y < GetLevel()->GetCameraPos().y + 960)) //카메라 안(살짝 카메라보다 큰 카메라)에 있어야 활동을 한다.
			{
				SetPosition(DeletePos_);
			}
			else //스폰포인트가 카메라 밖에 있을 때
			{
				//스폰포스가 먼저 셋팅됬는데, 이시간뒤에 DeletePos로 가는 거야
				SetPosition(SpawnPos_);
			}
		}
	}
	

	//몬스터가 죽었을경우 일정시간 이후 몬스터를 DeletePos_로 옮긴다.
	if (CanActivate == false && DeathTimer_ >= 0)
	{
		DeathTimer_ -= GameEngineTime::GetDeltaTime();
		if (DeathTimer_ <= 0)
		{
			SetPosition(DeletePos_);
			ChangeIdleAni();
			MonsterContactCol_->On();
			CanActivate = true;
			CurHP_ = MaxHP_;
			DeathTimer_ = Default_DeathTimer_;
			ChangeState(MonsterState::Idle);
		}
	}
	
}

void RockmanMonster::Render()
{
	if (GameManager::GetInst()->GetIsDebugMode() == true)
	{
		RockmanUtility::DebugText(StateStr_[static_cast<int>(CurState_)], GetCameraEffectPosition() + float4(0, 50));
	}

}


void RockmanMonster::ChangeState(MonsterState _State)
{
	if (CurState_ == _State)
	{
		return;
	}

	switch (_State)
	{
	case MonsterState::Idle:
		IdleStart();
		break;
	case MonsterState::Attack:
		AttackStart();
		break;
	case MonsterState::Jump:
		JumpStart();
		break;
	case MonsterState::Move:
		MoveStart();
		break;
	default:
		break;
	}

	CurState_ = _State;
}

void RockmanMonster::UpdateState()
{
	switch (CurState_)
	{
	case MonsterState::Idle:
		IdleUpdate();
		break;
	case MonsterState::Attack:
		AttackUpdate();
		break;
	case MonsterState::Jump:
		JumpUpdate();
		break;
	case MonsterState::Move:
		MoveUpdate();
		break;
	default:
		break;
	}
}

void RockmanMonster::HitByBulletCheck()
{
	if (MonsterContactCol_ != nullptr) //충돌체가 없는 몬스터가 있을 수 있다(ex 스포너)
	{
		std::vector<GameEngineCollision*> BulletColList;
		if (MonsterContactCol_->CollisionResult("Bullet", BulletColList, CollisionType::Rect, CollisionType::Rect) == true)
		{
			BulletType Type = BulletType::Normal;
			//히트된 총알을 제거한다.
			for (GameEngineCollision* Col : BulletColList)
			{
				Bullet* HitBullet = dynamic_cast<Bullet*>(Col->GetActor());
				Type = HitBullet->GetBulletType();
				HitBullet->Death();
			}
			Hit(Type);
		}
	}
}

void RockmanMonster::Hit(BulletType _BulletType)
{
	switch (_BulletType)
	{
	case BulletType::Normal:
		GameEngineSound::SoundPlayOneShot("EnemyDeath.mp3");
		--CurHP_;
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

void RockmanMonster::Die()
{
	CanActivate = false;
	MonsterRenderer_->PauseOff();
	MonsterRenderer_->ChangeAnimation("Die");
	DropItem();
	GameManager::GetInst()->AddScore(DropScore_);
	MonsterContactCol_->Off();
	Speed_ = Default_Speed_;
}

void RockmanMonster::DropItem()
{
	GameEngineRandom NewRandom;
	int RandomValue = NewRandom.RandomInt(0, 100);
	if (RandomValue > 50)
	{
		RockmanItem* NewItem = GetLevel()->CreateActor<RockmanItem>(static_cast<int>(GameLayer::Object), "Item");
		NewItem->SetItem(GetPosition());
	}

	
}
