#include "SelectLogo.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineContents/RockManEnum.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "GameManager.h"

SelectLogo::SelectLogo()
	: Boss_Name_Renderer_(nullptr),
	Clear_Points_Renderer_(nullptr),
	Number_Renderer_(nullptr),
	IsOn_1_(false),
	IsOn_2_(false),
	WaitTime_(1.5f)
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
	//�̰� ���߿� �����ؾ���
	Boss_Name_Renderer_->CreateFolderAnimation("SelectFolder_Cutman", "SelectAni_CutmanLogo", 0, 5,0.13f,false);
	Boss_Name_Renderer_->ChangeAnimation("SelectAni_CutmanLogo");
}

void SelectLogo::Update()
{
	if (Boss_Name_Renderer_->IsEndAnimation() == true && IsOn_1_ == false)
	{
		//SelectFolder_Logo
		Clear_Points_Renderer_ = CreateRenderer(static_cast<int>(GameLayer::Object), RenderPivot::LeftTop, { 0,40 });
		Clear_Points_Renderer_->SetTransColor(RGB(128, 0, 128));
		Clear_Points_Renderer_->CreateFolderAnimation("SelectFolder_Logo", "SelectAni_ClearPointLogo", 0, 10, 0.13f, false);
		Clear_Points_Renderer_->ChangeAnimation("SelectAni_ClearPointLogo");
		IsOn_1_ = true;
	}
	
	//Ŭ��������Ʈ�� ���� ��µǰ� ���� ���� Ŭ���� ���� ���� ���
	if (IsOn_1_ == true)
	{
		if (Clear_Points_Renderer_->IsEndAnimation() == true && IsOn_2_ == false)
		{
			Clear_Points_Renderer_ = CreateRenderer(static_cast<int>(GameLayer::Object), RenderPivot::LeftTop, { 0,120 });
			Clear_Points_Renderer_->SetTransColor(RGB(128, 0, 128));
			Clear_Points_Renderer_->CreateFolderAnimation("SelectFolder_Logo", "SelectAni_Number", 11, 21, 0.02f, false);
			Clear_Points_Renderer_->ChangeAnimation("SelectAni_Number");
			IsOn_2_ = true;		
		}
	}

	//Ŭ���� ����Ʈ ����, Ŭ���� ���� ���ڰ� ���� ��µǸ� 1�ʵ� ���� ��ŸƮ
	if (IsOn_2_ == true)
	{
		WaitTime_ -= GameEngineTime::GetDeltaTime();
		if (WaitTime_ <= 0)
		{
			GameManager::GetInst()->ChangeLevel("Stage1");
		}
	}
	
}

