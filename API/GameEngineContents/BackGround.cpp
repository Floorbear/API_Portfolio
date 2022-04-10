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
		MsgBoxAssert("BackGround SetImage�� �ŰԺ����� nullptr�Դϴ�!");
		return;
	}

}

void BackGround::Start()
{
	SetPosition({ 0,0 });
	SetScale(GameEngineWindow::GetScale());
}
