#include "SelectLogo.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineContents/RockManEnum.h>
#include <GameEngineBase/GameEngineWindow.h>

SelectLogo::SelectLogo()
	: Boss_Name_Renderer_(nullptr),
	Clear_Points_Renderer_(nullptr),
	Number_Renderer_(nullptr)
{
}

SelectLogo::~SelectLogo()
{
}

void SelectLogo::StartLogo()
{
	On();
}

void SelectLogo::Start()
{
	float4 Boss_Name_Pos = GameEngineWindow::GetScale().Half()+float4(0,-110);
	SetPosition(Boss_Name_Pos);
	Boss_Name_Renderer_ = CreateRenderer(static_cast<int>(GameLayer::Object), RenderPivot::LeftTop);
	Boss_Name_Renderer_->SetTransColor(RGB(128, 0, 128));
	Boss_Name_Renderer_->CreateFolderAnimation("SelectFolder_Cutman", "SelectAni_Cutman", 0, 5,0.2,false);
	Boss_Name_Renderer_->ChangeAnimation("SelectAni_Cutman");
}

void SelectLogo::Update()
{
}

