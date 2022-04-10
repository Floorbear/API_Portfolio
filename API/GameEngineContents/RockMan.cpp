#include "RockMan.h"
#include "TitleLevel.h"
#include "Stage1.h"
#include "GameManager.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineImage.h>

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

	{
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
	}
	
	{
		//오브젝트 디렉토리 로드
		GameEngineDirectory ObjDir;
		ObjDir.MoveParent("API");
		ObjDir.Move("Resources");
		ObjDir.Move("Object");

		std::vector<GameEngineFile> AllImageList = ObjDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageList[i].GetFullPath());
		}
	}
	
	//캐릭터 비트맵 초기화
	{
		{
			GameEngineImage* PlayerImage = GameEngineImageManager::GetInst()->Find("RockMan_Idle_Right.bmp");
			PlayerImage->Cut({ 256,256 });
		}
		{
			GameEngineImage* PlayerImage = GameEngineImageManager::GetInst()->Find("RockMan_Idle_left.bmp");
			PlayerImage->Cut({ 256,256 });
		}
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
	GameManager::GetInst()->Destroy();
}


