#include "BackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::Start()
{
	SetPosition({ 0,0 });
	SetScale(GameEngineWindow::GetScale());
}
