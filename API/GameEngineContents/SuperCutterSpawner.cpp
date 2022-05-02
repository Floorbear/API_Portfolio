#include "SuperCutterSpawner.h"
#include "Player.h"
#include "GameManager.h"
#include "SuperCutter.h"
#include "BackGround.h"

SuperCutterSpawner::SuperCutterSpawner()
{
}

SuperCutterSpawner::~SuperCutterSpawner()
{
}

void SuperCutterSpawner::InitMonster()
{
	SetScale({ 70,80 });
	//�������ͽ�
	AttackDamage_ = 4;//Default

	DropScore_ = 500;

	CurState_ = MonsterState::Idle;

	Default_Speed_ = 100;
	Speed_ = Default_Speed_;
	AttackStartRange_ = 320.0f;


	//���ݰ��� �Ķ����
	CurAttackTickTime_ = 0;
	MaxAttackTickTime_ = 0.5f;
	Default_DeathTimer_ = 1.0f;
	DeathTimer_ = Default_DeathTimer_;
	MaxHP_ = 5;
	CurHP_ = MaxHP_;
}

void SuperCutterSpawner::InitRenderer()
{

}

void SuperCutterSpawner::ChangeIdleAni()
{

}

void SuperCutterSpawner::SetMonster()
{
	//�ݸ��� ����
}

void SuperCutterSpawner::IdleStart()
{
}

void SuperCutterSpawner::IdleUpdate()
{
	Player_ = GameManager::GetInst()->GetPlayer();
	if (Player_ != nullptr)
	{
		float Distance = float4(Player_->GetPosition().x - GetPosition().x, 0).Len2D();
		if (Distance < AttackStartRange_)
		{
			if (CurAttackTickTime_ == 0)
			{
				SuperCutter* NewCutter = GetLevel()->CreateActor<SuperCutter>(static_cast<int>(GameLayer::Monster), "SuperCutter");
				NewCutter->SetPosition(GetPosition());
				NewCutter->SetIndex(GameManager::GetInst()->GetCurrentBackGround()->GetIndex());
				NewCutter->SetSuperCutter();
				NewCutter->Death(2.0f);
				CurAttackTickTime_ += GameEngineTime::GetDeltaTime();
			}
			else //���� ��Ÿ��
			{
				CurAttackTickTime_ += GameEngineTime::GetDeltaTime();
				if (CurAttackTickTime_ >= MaxAttackTickTime_)
				{
					CurAttackTickTime_ = 0;
				}
			}
			
		}
	}
}
