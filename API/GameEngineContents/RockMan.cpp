#include "RockMan.h"
#include "TitleLevel.h"
#include "Stage1.h"
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
	//해상도 셋팅
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({100,100}, {1024,896});


	//맵 디렉토리 로드
	GameEngineDirectory MapDir;
	MapDir.MoveParent("API");
	MapDir.Move("Resources");
	MapDir.Move("Map");

	std::vector<GameEngineFile> AllImageList = MapDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageList[i].GetFullPath());
	}


	CreateLevel<TitleLevel>("Title");
	CreateLevel<Stage1>("Stage1");
	ChangeLevel("Stage1");
}

void RockMan::GameLoop()
{
}

void RockMan::GameEnd()
{
}


