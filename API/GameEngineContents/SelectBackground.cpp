#include "SelectBackground.h"
#include "GameEngineContents/RockManEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include "GameManager.h"

SelectBackground::SelectBackground()
	:BackgroundRenderer_(nullptr)
{
}

SelectBackground::~SelectBackground()
{
}

void SelectBackground::Start()
{
	BackgroundRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Background), RenderPivot::LeftTop);
	BackgroundRenderer_->CreateFolderAnimation("SelectFolder", "SelectAni", 0, 1, 0.3f);
	BackgroundRenderer_->ChangeAnimation("SelectAni");
}

void SelectBackground::Update()
{

	if (GameEngineInput::GetInst()->IsPress("Jump") ||
		GameEngineInput::GetInst()->IsPress("MoveLeft") ||
		GameEngineInput::GetInst()->IsPress("MoveRight")
		)
	{
		GameManager::GetInst()->ChangeLevel("Stage1");
	}
}
