#include "RockMan.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>

RockMan::RockMan()
{
}

RockMan::~RockMan()
{
}

void RockMan::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({100,100}, {800,600});
	CreateLevel<TitleLevel>("Title");
	ChangeLevel("Title");
}

void RockMan::GameLoop()
{
}

void RockMan::GameEnd()
{
}


