#include "RockMan.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>

RockMan::RockMan()
{
}

RockMan::~RockMan()
{
}

void RockMan::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({100,100}, {800,600});

	//현재 디렉토리
	GameEngineDirectory ResourcesDir;
	ResourcesDir.MoveParent("API");
	ResourcesDir.Move("Resources");
	ResourcesDir.Move("Image");

	std::vector<GameEngineFile> AllImageList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageList[i].GetFullPath());
	}


	CreateLevel<TitleLevel>("Title");
	ChangeLevel("Title");
}

void RockMan::GameLoop()
{
}

void RockMan::GameEnd()
{
}


