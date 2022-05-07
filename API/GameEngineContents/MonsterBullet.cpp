#include "MonsterBullet.h"
#include <GameEngine/GameEngineRenderer.h>
#include "RockmanUtility.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "Player.h"
#include "GameManager.h"
#include "Cutman.h"

MonsterBullet::MonsterBullet()
	:HaveDir_(false),
	Speed_(800.0f),
	Dir_({ 0,0 }),
	DeathTime_(1.2f),
	Renderer_(nullptr),
	Dmg_(1),
	Cutman_(nullptr),
	IsReturn_(false)
{
}

MonsterBullet::~MonsterBullet()
{
}


void MonsterBullet::SetBullet(const float4& _Pos, const float4& _Dir,int _Dmg, MonsterBulletType _BulletType)
{
	Type_ = _BulletType;

	if (_BulletType != MonsterBulletType::CutmanBullet)
	{
		SetScale({ 30,30 });
		CreateCollision("MonsterBullet", GetScale());
		Renderer_ = CreateRenderer(static_cast<int>(GameLayer::Bullet), RenderPivot::CENTER);
		Renderer_->SetImage("EnemyBullet.bmp");
		Renderer_->SetTransColor(TransColor);
		HaveDir_ = true;
		Dir_ = _Dir;
		Dmg_ = _Dmg;
		SetPosition(_Pos);
		Death(DeathTime_);
		Renderer_->SetIndex(static_cast<int>(_BulletType));
		return;
	}
	else //컷맨 불릿이면
	{
		SetScale({ 50,50 });
		SetPosition(_Pos+float4(0,-80));
		StartPos_ = _Pos;
		Speed_ = 700.0f;
		HaveDir_ = true;
		Dir_ = _Dir;
		DeathTime_ = 0.2f;

		Renderer_ = CreateRenderer(static_cast<int>(GameLayer::Bullet), RenderPivot::CENTER, { 0,30 });
		Renderer_->SetTransColor(TransColor);
		Renderer_->CreateAnimation("Cutman_Right.bmp", "CutmanBullet", 17, 20, 0.12, true);
		CreateCollision("MonsterBullet", GetScale());

		Renderer_->ChangeAnimation("CutmanBullet");
	}

}

void MonsterBullet::Start()
{

}

void MonsterBullet::Update()
{
	//일반 불릿용
	if (HaveDir_ == true && Type_ != MonsterBulletType::CutmanBullet)
	{
		Player* CurPlayer = GameManager::GetInst()->GetPlayer();
		if (CurPlayer != nullptr)
		{
			if (CurPlayer->GetCanActivate() == true)
			{
				SetMove(Dir_ * Speed_ * GameEngineTime::GetDeltaTime());
			}
		}
	}

	//컷맨 불릿용
	if (Type_ == MonsterBulletType::CutmanBullet)
	{
		/*DeathTime_ -= GameEngineTime::GetDeltaTime();
		if (DeathTime_ >= 0)
		{
			return;
		}*/


		//여기서 Cutman이 없으면 죽게 만들어
		if (Cutman_ == nullptr)
		{
			Death();
		}

		if (Cutman_->GetHP() == 0)
		{
			Death();
		}


		if (HaveDir_ == true) //셋된 상태에서만
		{
			if (IsReturn_ == false)
			{
				//이때 Dir_은 목표지점을 의미한다.
				float AttackRange = (Dir_ - StartPos_).Len2D();
				float CurAttackRange = (GetPosition() - StartPos_).Len2D();
				if (CurAttackRange >= AttackRange)
				{
					IsReturn_ = true;
				}
				else
				{
					float4 AttackDir_ = Dir_ - StartPos_;
					AttackDir_.Normal2D();
					SetMove(AttackDir_ * Speed_ * GameEngineTime::GetDeltaTime());
				}
			}
			else //돌아가는 상태
			{
				float4 ReturnDir = Cutman_->GetPosition() - GetPosition();
				ReturnDir.Normal2D();
				SetMove(ReturnDir * Speed_ * GameEngineTime::GetDeltaTime());
			}

		}
	}
}


