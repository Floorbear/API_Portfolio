#include "HPBar.h"
#include <GameEngine/GameEngineRenderer.h>
#include "RockManEnum.h"

HPBar::HPBar()
	:HPBar_(nullptr)
{
}

HPBar::~HPBar()
{
}

void HPBar::Start()
{
	SetPosition({ 80,80 });
	HPBar_ = CreateRenderer(static_cast<int>(GameLayer::UI), RenderPivot::LeftTop);
	HPBar_->SetImage("HPBar.bmp");
	HPBar_->CameraEffectOff();
}

void HPBar::Update()
{
}

void HPBar::Render()
{
}
