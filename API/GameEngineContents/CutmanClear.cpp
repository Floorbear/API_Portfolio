#include "CutmanClear.h"
#include <GameEngine/GameEngineRenderer.h>
#include "RockManEnum.h"

CutmanClear::CutmanClear():
	BackgroundRenderer_(nullptr),
	CutmanLogoRenderer_(nullptr),
	ClearLogoRenderer_(nullptr)
{
}

CutmanClear::~CutmanClear()
{
}

void CutmanClear::Start()
{
	BackgroundRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Object), RenderPivot::LeftTop);
	CutmanLogoRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Object), RenderPivot::LeftTop,{500,400});
	CutmanLogoRenderer_->SetTransColor(RGB(128, 0, 128));
	ClearLogoRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Object), RenderPivot::LeftTop,{500,500});
	ClearLogoRenderer_->SetTransColor(RGB(128, 0, 128));

	BackgroundRenderer_->CreateFolderAnimation("SelectFolder", "Background", 1, 1, 0.13f, false);
	CutmanLogoRenderer_->CreateFolderAnimation("SelectFolder_Cutman", "Cutman", 0, 5, 0.2f, false);
	ClearLogoRenderer_->CreateFolderAnimation("SelectFolder_Logo", "Logo", 0, 4, 0.2f, false);

	BackgroundRenderer_->ChangeAnimation("Background");
	CutmanLogoRenderer_->ChangeAnimation("Cutman");
	ClearLogoRenderer_->ChangeAnimation("Logo");
	ClearLogoRenderer_->Off();
}

void CutmanClear::Update()
{
	if (CutmanLogoRenderer_->IsEndAnimation() == true)
	{
		ClearLogoRenderer_->On();
	}
}
