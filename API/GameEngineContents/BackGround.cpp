#include "BackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::SetImage(GameEngineImage* _Map , GameEngineImage* _ColMap)
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

bool BackGround::IsBlocked(float4& _Pos1, float4& _Pos2)
{
	return RGB(0, 0, 0) == BackGroundColImage_->GetImagePixel(_Pos1) || 
		RGB(0, 0, 0) == BackGroundColImage_->GetImagePixel(_Pos2);
}

bool BackGround::IsBlocked(float4& _Pos)
{
	return RGB(0,0,0) == BackGroundColImage_->GetImagePixel(_Pos);
}
