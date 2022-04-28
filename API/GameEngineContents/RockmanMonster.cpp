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
	InitMonster();
	StateStr_[static_cast<int>(MonsterState::Chase)] = "Chase";
	StateStr_[static_cast<int>(MonsterState::Attack)] = "Attack";
}

RockmanMonster::~RockmanMonster()
{
}

void RockmanMonster::Start()
{
	SetScale({ 70,80 });
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
			//카메라가 스폰포인트 위치 밖에 있으면, 몬스터의 위치를 SpawnPos로 옮긴다
			if ((GetLevel()->GetCameraPos().x - 30 < SpawnPos_.x && SpawnPos_.x < GetLevel()->GetCameraPos().x + 1060) &&
				(GetLevel()->GetCameraPos().y < SpawnPos_.y && SpawnPos_.y < GetLevel()->GetCameraPos().y + 960)) //카메라 안(살짝 카메라보다 큰 카메라)에 있어야 활동을 한다.
			{
				SetPosition(DeletePos_);
			}
			else //카메라 밖에 있을 때
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

void RockmanMonster::InitMonster()
{
	//스테이터스
	AttackDamage_ = 3;

	CurState_ = MonsterState::Chase;


	Default_Speed_ = 200.0f;
	Speed_ = Default_Speed_;
	AttackStartRange_=200.0f;

	Default_DeathTimer_ = 1.0f;
	DeathTimer_ = Default_DeathTimer_;
	MaxHP_ = 1;
	CurHP_ = MaxHP_;

		
}

void RockmanMonster::InitRenderer()
{
	//렌더러 애니메이션 셋팅
	MonsterRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Monster), RenderPivot::CENTER);
	MonsterRenderer_->SetTransColor(TransColor);
	MonsterRenderer_->CreateAnimation("BunbyHeli_Left.bmp", "BunbyHeli_Left", 0, 1, 0.05f);
	MonsterRenderer_->CreateAnimation("BunbyHeli_Right.bmp", "BunbyHeli_Right", 0, 1, 0.05f);

	//사망 애니메이션
	MonsterRenderer_->CreateAnimation("Explosion.bmp", "Explosion", 0, 4, 0.05f, false);

	MonsterRenderer_->ChangeAnimation("BunbyHeli_Left");
}

void RockmanMonster::ChangeIdleAni()
{
	CurHoriDir_ = float4(Player_->GetPosition().x - GetPosition().x, 0);
	CurHoriDir_.Normal2D();
	MonsterRenderer_->ChangeAnimation("BunbyHeli_" + RockmanUtility::DirToStr(CurHoriDir_));
}

void RockmanMonster::SetMonster()
{


	//콜리전 생성
	MonsterContactCol_ = CreateCollision("MonsterCol", GetScale());

}

void RockmanMonster::ChangeState(MonsterState _State)
{
	if (CurState_ == _State)
	{
		return;
	}

	switch (_State)
	{
	case MonsterState::Chase:
		ChaseStart();
		break;
	case MonsterState::Attack:
		AttackStart();
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
	case MonsterState::Chase:
		ChaseUpdate();
		break;
	case MonsterState::Attack:
		AttackUpdate();
		break;
	default:
		break;
	}
}

void RockmanMonster::ChaseStart()
{
	SetPosition(float4(GetPosition().x, AttackStartPos_.y));
	Speed_ = Default_Speed_;
	CurHoriDir_ = float4(Player_->GetPosition().x - GetPosition().x, 0);
	CurHoriDir_.Normal2D();
	MonsterRenderer_->ChangeAnimation("BunbyHeli_" + RockmanUtility::DirToStr(CurHoriDir_));

}

void RockmanMonster::ChaseUpdate()
{
	WantHoriDir_= float4(Player_->GetPosition().x-GetPosition().x, 0);
	WantHoriDir_.Normal2D();

	//방향 전환이 일어난다면 애니메이션을 바꿔라
	if (WantHoriDir_.CompareInt2D(CurHoriDir_) == false)
	{
		if (WantHoriDir_.CompareInt2D(float4::ZERO) == false) //플레이어가 죽고 위치에 고정될때
		{
			MonsterRenderer_->ChangeAnimation("BunbyHeli_" + RockmanUtility::DirToStr(WantHoriDir_));
			CurHoriDir_ = WantHoriDir_;
		}
	}

	//사정거리 내에 도달하면 공격을 한다.
	float Distance = float4(Player_->GetPosition().x - GetPosition().x, 0).Len2D();
	if (Distance <= AttackStartRange_)
	{
		//Y축 거리차가 너무나면 공격을 중지한다.
		float DistanceY = float4(0, Player_->GetPosition().y - GetPosition().y).Len2D();
		if (DistanceY < 1200)
		{
			ChangeState(MonsterState::Attack);
			return;
		}
	}
	SetMove(CurHoriDir_ * Speed_*GameEngineTime::GetDeltaTime());
}

void RockmanMonster::AttackStart()
{
	AttackPos_ = Player_->GetPosition();
	AttackStartPos_ = GetPosition();

	InitVerDir_ = float4(0, Player_->GetPosition().y - GetPosition().y);
	VerSpeed_ = InitVerDir_.Len2D() * 1.5f; // 초기 스피드

	InitVerDir_.Normal2D();

	CurVerDir_ = InitVerDir_;

}

void RockmanMonster::AttackUpdate()
{

	if (InitVerDir_.CompareInt2D(CurVerDir_) == true) 
	{
		if (CurVerDir_.CompareInt2D(float4::UP) == true) //위로볼록 상태인 경우
		{
			if (GetPosition().y <= AttackPos_.y)
			{
				CurVerDir_ = -CurVerDir_;
			}
		}
		else if (CurVerDir_.CompareInt2D(float4::DOWN) == true) //아래로볼록 상태인 경우
		{
			if (GetPosition().y >= AttackPos_.y+20.0f)
			{
				CurVerDir_ = -CurVerDir_;
			}
		}
	}

	//Vertical 방향전환이 일어난 상태에서 처음 공격 시작한 지점의 y좌표까지 도달한다면
	if (InitVerDir_.CompareInt2D(CurVerDir_) == false)
	{
		if (CurVerDir_.CompareInt2D(float4::UP) == true) //아래로볼록 상태인 경우
		{
			if (GetPosition().y <= AttackStartPos_.y)
			{
				ChangeState(MonsterState::Chase);
				return;
			}
		}
		else if (CurVerDir_.CompareInt2D(float4::DOWN) == true) //위로볼록 상태인 경우
		{
			if (GetPosition().y >= AttackStartPos_.y)
			{
				CurVerDir_ = -CurVerDir_;
				ChangeState(MonsterState::Chase);
				return;
			}
		}
	}

	VerSpeed_ += VerSpeed_* GameEngineTime::GetDeltaTime();
	Speed_ += 1300.0f * GameEngineTime::GetDeltaTime();

	SetMove(float4(CurHoriDir_.x * Speed_ * GameEngineTime::GetDeltaTime(),CurVerDir_.y*VerSpeed_*1.1f*GameEngineTime::GetDeltaTime()));
}

void RockmanMonster::HitByBulletCheck()
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

void RockmanMonster::Hit(BulletType _BulletType)
{
	switch (_BulletType)
	{
	case BulletType::Normal:
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
	MonsterRenderer_->ChangeAnimation("Explosion");
	GameEngineSound::SoundPlayOneShot("EnemyDeath.mp3");
	DropItem();
	MonsterContactCol_->Off();
	ChangeState(MonsterState::Chase);
	Speed_ = Default_Speed_;
}

void RockmanMonster::DropItem()
{
	GameEngineRandom NewRandom;
	int RandomValue = NewRandom.RandomInt(0, 100);
	if (RandomValue > 50)
	{
		RockmanItem* NewItem = GetLevel()->CreateActor<RockmanItem>(static_cast<int>(GameLayer::Object), "Item");
		NewItem->SetPosition(GetPosition());
	}

}
