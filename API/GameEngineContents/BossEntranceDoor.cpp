#include "BossEntranceDoor.h"
#include <GameEngineBase/GameEngineDebug.h>

BossEntranceDoor::BossEntranceDoor()
	:
	DoorRenderer_(nullptr),
	DoorCol_(nullptr)
{
}

BossEntranceDoor::~BossEntranceDoor()
{
}

void BossEntranceDoor::Start()
{
	SetScale({128, 256});

	DoorCol_ = CreateCollision("DoorCol", GetScale(), GetPosition() + GetScale().Half());
	DoorRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Object), RenderPivot::LeftTop);
	DoorRenderer_->CreateAnimation("BossEntranceDoor.bmp", "BossEntranceDoorOpen", 0, 4, 0.2f, false);
	DoorRenderer_->SetTransColor(TransColor);

	DoorRenderer_->ChangeAnimation("BossEntranceDoorOpen");
	DoorRenderer_->PauseOn();
}

void BossEntranceDoor::Update()
{
}

void BossEntranceDoor::DoorColCheck()
{

}
