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
	InitMonster(); //������ �⺻���� �������ͽ��� �ʱ�ȭ�ȴ�.
	InitRenderer();
	SetMonster();
}

void RockmanMonster::Update()
{
	if (CanActivate == true)
	{
		if ((GetLevel()->GetCameraPos().x - 30 < GetPosition().x && GetPosition().x < GetLevel()->GetCameraPos().x + 1060) &&
			(GetLevel()->GetCameraPos().y < GetPosition().y && GetPosition().y < GetLevel()->GetCameraPos().y + 960)) //ī�޶� ��(��¦ ī�޶󺸴� ū ī�޶�)�� �־�� Ȱ���� �Ѵ�.
		{
			//�÷��̾� ����
			Player_ = GameManager::GetInst()->GetPlayer();
			if (Player_ != nullptr)
			{
				//���� ������ ��� �����ؼ� �ʺ����� �Ͼ�� ������ Ȱ���� ������Ų��.
				size_t Background_Index = GameManager::GetInst()->GetCurrentBackGround()->GetIndex();
				if (Index_ == Background_Index && Player_->GetCanActivate() == true )
				{
					if (Player_->GetCurPlayerState() != PlayerState::Die) //�÷��̾ Die�����ϰ�� ��� ���Ͱ� �����.
					{
						UpdateState();
						HitByBulletCheck();
					}
				}
			}
		}
		else //���Ͱ� ī�޶� �ۿ� Ȱ���� ������Ų�� (== ������ Pos�� -1000,-1000���� �ű��). , ������ ��ġ�� SpawnPos�� �ȱ��.
		{	
			Speed_ = Default_Speed_;
			ChangeState(MonsterState::Idle);
			//ī�޶� ��������Ʈ ��ġ �ۿ� ������, ������ ��ġ�� SpawnPos�� �ű��
			if ((GetLevel()->GetCameraPos().x - 30 < SpawnPos_.x && SpawnPos_.x < GetLevel()->GetCameraPos().x + 1060) &&
				(GetLevel()->GetCameraPos().y < SpawnPos_.y && SpawnPos_.y < GetLevel()->GetCameraPos().y + 960)) //ī�޶� ��(��¦ ī�޶󺸴� ū ī�޶�)�� �־�� Ȱ���� �Ѵ�.
			{
				SetPosition(DeletePos_);
			}
			else //��������Ʈ�� ī�޶� �ۿ� ���� ��
			{
				//���������� ���� ���É�µ�, �̽ð��ڿ� DeletePos�� ���� �ž�
				SetPosition(SpawnPos_);
			}
		}
	}
	

	//���Ͱ� �׾������ �����ð� ���� ���͸� DeletePos_�� �ű��.
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
	if (MonsterContactCol_ != nullptr) //�浹ü�� ���� ���Ͱ� ���� �� �ִ�(ex ������)
	{
		std::vector<GameEngineCollision*> BulletColList;
		if (MonsterContactCol_->CollisionResult("Bullet", BulletColList, CollisionType::Rect, CollisionType::Rect) == true)
		{
			BulletType Type = BulletType::Normal;
			//��Ʈ�� �Ѿ��� �����Ѵ�.
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

	//ü���� 0���� �۴ٸ� 
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
