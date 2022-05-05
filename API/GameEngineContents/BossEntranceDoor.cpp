#include "BossEntranceDoor.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "Player.h"
#include "GameManager.h"
#include "BackGround.h"

BossEntranceDoor::BossEntranceDoor()
	:
	DoorRenderer_(nullptr),
	DoorCol_(nullptr),
	IsSet_(false)
{
}

BossEntranceDoor::~BossEntranceDoor()
{
}

void BossEntranceDoor::SetDoor(bool _IsBossDoor)
{
	IsSet_ = true;
	if (_IsBossDoor == false)
	{
		SetScale({ 128, 256 });
		DoorCol_ = CreateCollision("DoorCol", GetScale(), GetScale().Half());
		DoorRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Object), RenderPivot::LeftTop);
		DoorRenderer_->CreateAnimation("BossEntranceDoor.bmp", "DoorOpen", 0, 4, 0.2f, false);
		DoorRenderer_->SetTransColor(TransColor);
		DoorRenderer_->ChangeAnimation("DoorOpen");
		DoorRenderer_->PauseOn();
	}
	else
	{
		SetScale({ 64, 256 });
		DoorCol_ = CreateCollision("DoorCol", GetScale(), GetScale().Half());
		DoorRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Object), RenderPivot::LeftTop);
		DoorRenderer_->CreateAnimation("BossDoor.bmp", "DoorOpen", 0, 4, 0.2f, false);
		DoorRenderer_->SetTransColor(TransColor);
		DoorRenderer_->ChangeAnimation("DoorOpen");
		DoorRenderer_->PauseOn();
	}
}

void BossEntranceDoor::Start()
{
}

void BossEntranceDoor::Update()
{
	if (IsSet_ == false)
	{
		return;
	}

	if (DoorRenderer_->IsEndAnimation() == true)
	{
		Player* CurPlayer_ = GameManager::GetInst()->GetPlayer();
		BackGround* OldBackground = GameManager::GetInst()->GetCurrentBackGround();
		GameManager::GetInst()->SetCurrentBackGround(OldBackground->GetUPBackground());
		CurPlayer_->GetPlayerRenderer()->PauseOff();
		CurPlayer_->GoToRight(1024);
		Death();
	}
	DoorColCheck();
}

void BossEntranceDoor::DoorColCheck()
{
	Player* CurPlayer_ = nullptr;
	std::vector<GameEngineCollision*> PlayerColList_;
	if (DoorCol_->CollisionResult("Player", PlayerColList_, CollisionType::Rect, CollisionType::Rect) == true)
	{
		for (GameEngineCollision* PlayerCol : PlayerColList_)
		{
			CurPlayer_ = dynamic_cast<Player*>(PlayerCol->GetActor());
		}
		CurPlayer_->SwitchCanActivate();
		CurPlayer_->GetPlayerRenderer()->PauseOn();
		DoorCol_->Off();
		DoorRenderer_->PauseOff();
	}
}
