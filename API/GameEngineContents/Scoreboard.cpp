#include "Scoreboard.h"
#include "RockManEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>

Scoreboard::Scoreboard()
	:Scoreboard_(nullptr)
{
}

Scoreboard::~Scoreboard()
{
}

void Scoreboard::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half()-float4(0,420));
	Scoreboard_ = CreateRenderer(static_cast<int>(GameLayer::UI));
	Scoreboard_->SetImage("Scoreboard.bmp");
	Scoreboard_->CameraEffectOff();
	Scoreboard_->SetTransColor(RGB(128, 0, 128));

}

void Scoreboard::Update()
{
}

void Scoreboard::Render()
{
}
