#include "BackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include "RockManEnum.h"

BackGround::BackGround()
{

}

BackGround::~BackGround()
{
}



void BackGround::Start()
{
	BackGroundImage_ = GameEngineImageManager::GetInst()->Find(GetNameConstRef() + ".bmp");

	BackGroundColImage_ = GameEngineImageManager::GetInst()->Find(GetNameConstRef() + "_Col.bmp");

	if (BackGroundImage_ == nullptr || BackGroundColImage_ == nullptr)
	{
		MsgBoxAssertString("BackGroundImage_ 혹은 BackGroundColImage를 찾을 수 없습니다." + GetNameConstRef() + ".bmp");
	}

	Renderer_ = CreateRenderer(GetNameConstRef() + ".bmp", static_cast<int>(GameLayer::Background), RenderPivot::LeftTop);
	SetScale(GameEngineWindow::GetScale());
}


bool BackGround::IsBlocked(const float4& _Pos , unsigned long _RGB)
{
	return _RGB == BackGroundColImage_->GetImagePixel(_Pos-GetPosition());
}
