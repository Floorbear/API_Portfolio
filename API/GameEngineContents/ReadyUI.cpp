#include "ReadyUI.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "GameManager.h"

ReadyUI::ReadyUI()
	:ReadyRenderer_(nullptr),
	ReadyEndTimer_(2.0f)
{
}

ReadyUI::~ReadyUI()
{
}

void ReadyUI::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half()-float4(0,150));
	ReadyRenderer_ = CreateRenderer(static_cast<int>(GameLayer::UI));
	ReadyRenderer_->SetImage("Ready.bmp");
	ReadyRenderer_->CameraEffectOff();
	ReadyRenderer_->SetTransColor(TransColor);

}

void ReadyUI::Update()
{
	ReadyEndTimer_ -= GameEngineTime::GetDeltaTime();
	if (ReadyEndTimer_ <= 0)
	{
		GameManager::GetInst()->IsGameStart = true;
		Death();
	}
}
