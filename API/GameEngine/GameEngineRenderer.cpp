#include "GameEngineRenderer.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineDebug.h>

GameEngineRenderer::GameEngineRenderer()
	: Image_(nullptr)
	, PivotType_(RenderPivot::CENTER)
	, ScaleMode_(RenderScaleMode::Image)
	, RenderImagePivot_({ 0,0 })
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}

void GameEngineRenderer::SetImage(const std::string& _Name)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find(_Name);
	if (FindImage == nullptr)
	{
		MsgBoxAssert("존재하지 않는 이미지를 랜더러에 세팅하려고 했습니다.");
	}

	Image_ = FindImage;
}

void GameEngineRenderer::SetImageScale()
{
	if (Image_ == nullptr)
	{
		MsgBoxAssert("존재하지 않는 이미지로 크기를 조절하려고 했습니다");
		return;
	}

	ScaleMode_ = RenderScaleMode::Image;
	RenderScale_ = Image_->GetScale();
	RenderImageScale_ = Image_->GetScale();
}
