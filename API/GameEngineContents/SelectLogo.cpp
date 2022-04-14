#include "SelectLogo.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineContents/RockManEnum.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "GameManager.h"

SelectLogo::SelectLogo()
	: Boss_Name_Renderer_(nullptr),
	Clear_Points_Renderer_(nullptr),
	Number_Renderer_(nullptr),
	IsOn_1_(false)
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
	if (Boss_Name_Renderer_->IsEndAnimation() == true && IsOn_1_ == false)
	{
		//SelectFolder_Logo
		Clear_Points_Renderer_ = CreateRenderer(static_cast<int>(GameLayer::Object), RenderPivot::LeftTop, { 0,40 });
		Clear_Points_Renderer_->SetTransColor(RGB(128, 0, 128));
		Clear_Points_Renderer_->CreateFolderAnimation("SelectFolder_Logo", "SelectAni_Logo", 0, 10, 0.2, false);
		Clear_Points_Renderer_->ChangeAnimation("SelectAni_Logo");
		IsOn_1_ = true;
	}
	
	if (IsOn_1_ == true)
	{
		if (Clear_Points_Renderer_->IsEndAnimation() == true)
		{
			GameManager::GetInst()->ChangeLevel("Stage1");
		}
	}
	
}

