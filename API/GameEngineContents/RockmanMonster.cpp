#include "RockmanMonster.h"
#include <GameEngine/GameEngineRenderer.h>
#include "RockmanUtility.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameManager.h"
#include "Player.h"
#include "BackGround.h"
#include <GameEngine/GameEngineCollision.h>
#include "Bullet.h"

RockmanMonster::RockmanMonster()
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
	//����׿� �׽�Ʈ ������
	SetPosition({ 3300,100 });
	SetScale({ 70,80 });
	InitRenderer();
	SetMonster();
}

void RockmanMonster::Update()
{
	//�÷��̾� ����
	Player_ = GameManager::GetInst()->GetPlayer();
	if (Player_ != nullptr)
	{
		//���� ������ ��� �����ؼ� �Ͼ�� ���͸� ���δ�
		size_t Background_Index = GameManager::GetInst()->GetCurrentBackGround()->GetIndex();
		if (Index_ == Background_Index && IsDead == false)
		{
			if (Player_->GetCurPlayerState() != PlayerState::Die) //�÷��̾ Die�����ϰ�� ��� ���Ͱ� �����.
			{
				UpdateState();
				HitByBulletCheck();
			}
		}
		else
		{
			DeathTimer_ -= GameEngineTime::GetDeltaTime();
		}
		
	}
	
	if (DeathTimer_ <= 0)
	{
		Death();
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
	AttackDamage_ = 3;
	MonsterRenderer_ = nullptr;
	MonsterContactCol_ = nullptr;
	CurState_ = MonsterState::Chase;
	Player_ = nullptr;
	CurHoriDir_=float4::ZERO;
	WantHoriDir_=float4::ZERO;
	Speed_=100.0f;
	Default_Speed_ = 100.0f;
	AttackStartRange_=230.0f;
	DeathTimer_ = 1.0f;
	MaxHP_ = 2;
	IsDead = false;
		
}

void RockmanMonster::InitRenderer()
{
	//������ �ִϸ��̼� ����
	MonsterRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Monster), RenderPivot::CENTER);
	MonsterRenderer_->SetTransColor(TransColor);
	MonsterRenderer_->CreateAnimation("BunbyHeli_Left.bmp", "BunbyHeli_Left", 0, 1, 0.05f);
	MonsterRenderer_->CreateAnimation("BunbyHeli_Right.bmp", "BunbyHeli_Right", 0, 1, 0.05f);

	//��� �ִϸ��̼�
	MonsterRenderer_->CreateAnimation("Explosion.bmp", "Explosion", 0, 4, 0.05f, false);

	MonsterRenderer_->ChangeAnimation("BunbyHeli_Left");
}

void RockmanMonster::SetMonster()
{
	//�Ķ���� ����
	CurHP_ = MaxHP_;

	//�ݸ��� ����
	MonsterContactCol_ = CreateCollision("MonsterCol", GetScale());


	//������ �� ��׶����� �ε����� �ڱ� �ε�����
	Index_ = GameManager::GetInst()->GetCurrentBackGround()->GetIndex();
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
}

void RockmanMonster::ChaseUpdate()
{
	WantHoriDir_= float4(Player_->GetPosition().x-GetPosition().x, 0);
	WantHoriDir_.Normal2D();

	//���� ��ȯ�� �Ͼ�ٸ� �ִϸ��̼��� �ٲ��
	if (WantHoriDir_.CompareInt2D(CurHoriDir_) == false)
	{
		if (WantHoriDir_.CompareInt2D(float4::ZERO) == false) //�÷��̾ �װ� ��ġ�� �����ɶ�
		{
			MonsterRenderer_->ChangeAnimation("BunbyHeli_" + RockmanUtility::DirToStr(WantHoriDir_));
			CurHoriDir_ = WantHoriDir_;
		}
	}

	//�����Ÿ� ���� �����ϸ� ������ �Ѵ�.
	float Distance = float4(Player_->GetPosition().x - GetPosition().x, 0).Len2D();
	if (Distance <= AttackStartRange_)
	{
		//Y�� �Ÿ����� �ʹ����� ������ �����Ѵ�.
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
	VerSpeed_ = InitVerDir_.Len2D() * 1.5f; // �ʱ� ���ǵ�

	InitVerDir_.Normal2D();

	CurVerDir_ = InitVerDir_;

}

void RockmanMonster::AttackUpdate()
{

	if (InitVerDir_.CompareInt2D(CurVerDir_) == true) 
	{
		if (CurVerDir_.CompareInt2D(float4::UP) == true) //���κ��� ������ ���
		{
			if (GetPosition().y <= AttackPos_.y)
			{
				CurVerDir_ = -CurVerDir_;
			}
		}
		else if (CurVerDir_.CompareInt2D(float4::DOWN) == true) //�Ʒ��κ��� ������ ���
		{
			if (GetPosition().y >= AttackPos_.y+20.0f)
			{
				CurVerDir_ = -CurVerDir_;
			}
		}
	}

	//Vertical ������ȯ�� �Ͼ ���¿��� ó�� ���� ������ ������ y��ǥ���� �����Ѵٸ�
	if (InitVerDir_.CompareInt2D(CurVerDir_) == false)
	{
		if (CurVerDir_.CompareInt2D(float4::UP) == true) //�Ʒ��κ��� ������ ���
		{
			if (GetPosition().y <= AttackStartPos_.y)
			{
				ChangeState(MonsterState::Chase);
				return;
			}
		}
		else if (CurVerDir_.CompareInt2D(float4::DOWN) == true) //���κ��� ������ ���
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

	//ü���� 0���� �۴ٸ� 
	if (CurHP_ <= 0 && IsDead == false)
	{
		Die();
	}
}

void RockmanMonster::Die()
{
	IsDead = true;
	MonsterRenderer_->ChangeAnimation("Explosion");
	MonsterContactCol_->Off();
}
