#include "BackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::SetBackGroundImage(GameEngineImage* _Map , GameEngineImage* _ColMap)
{
	BackGroundImage_ = _Map;
	BackGroundColImage_ = _ColMap;

	if (BackGroundImage_ == nullptr || BackGroundColImage_ == nullptr)
	{
		MsgBoxAssert("BackGround SetImage에 매게변수가 nullptr입니다!");
		return;
	}

}

void BackGround::Start()
{
	SetPosition({ 0,0 });
	SetScale(GameEngineWindow::GetScale());
}


bool BackGround::IsBlocked(const float4& _Pos , unsigned long _RGB)
{
	return _RGB == BackGroundColImage_->GetImagePixel(_Pos);
}
