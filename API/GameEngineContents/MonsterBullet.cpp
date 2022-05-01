#include "MonsterBullet.h"
#include <GameEngine/GameEngineRenderer.h>
#include "RockmanUtility.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "Player.h"
#include "GameManager.h"

MonsterBullet::MonsterBullet()
	:HaveDir_(false),
	Speed_(800.0f),
	Dir_({ 0,0 }),
	DeathTime_(1.2f),
	Renderer_(nullptr),
	Dmg_(1)
{
}

MonsterBullet::~MonsterBullet()
{
}


void MonsterBullet::SetBullet(const float4& _Pos, const float4& _Dir,int _Dmg, MonsterBulletType _BulletType)
{
	Type_ = _BulletType;
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

void MonsterBullet::Start()
{
	SetScale({ 30,30 });
	CreateCollision("MonsterBullet", GetScale());
}

void MonsterBullet::Update()
{
	if (HaveDir_ == true)
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
}


