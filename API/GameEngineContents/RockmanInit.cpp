#include "RockMan.h"
#include "TitleLevel.h"
#include "SelectLevel.h"
#include "Stage1.h"
#include "GameManager.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineInput.h>

void RockMan::GameInit()
{
	//해상도 셋팅
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100,100 }, { 1024,960 });


	LoadResources();
	InitImage();
	InitKey();

	CreateLevel<TitleLevel>("Title");
	CreateLevel<SelectLevel>("Select");
	CreateLevel<Stage1>("Stage1");
	ChangeLevel("Stage1");
}

void RockMan::LoadResources()
{
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

	{
		//UI 디렉토리 로드
		GameEngineDirectory UIDir;
		UIDir.MoveParent("API");
		UIDir.Move("Resources");
		UIDir.Move("UI");

		std::vector<GameEngineFile> AllImageList = UIDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageList[i].GetFullPath());
		}
	}

	//Select Folder이미지 로드
	{
		GameEngineDirectory SelectDir;
		SelectDir.MoveParent("API");
		SelectDir.Move("Resources");
		SelectDir.Move("UI");
		SelectDir.Move("Select");
		GameEngineImageManager::GetInst()->FolderImageLoad(SelectDir.GetFullPath(), "SelectFolder");

		//CutMan
		SelectDir.Move("Cutman");
		GameEngineImageManager::GetInst()->FolderImageLoad(SelectDir.GetFullPath(), "SelectFolder_Cutman");

		//Cutman에서 나가주기
		SelectDir.MoveParent("Select");
		SelectDir.Move("Logo");
		GameEngineImageManager::GetInst()->FolderImageLoad(SelectDir.GetFullPath(), "SelectFolder_Logo");

	}
}

void RockMan::InitImage()
{
	//캐릭터 비트맵 초기화
	{
		GameEngineImage* PlayerImage;

		PlayerImage = GameEngineImageManager::GetInst()->Find("RockMan_Idle_Right.bmp");
		PlayerImage->Cut({ 256,256 });

		PlayerImage = GameEngineImageManager::GetInst()->Find("RockMan_Idle_left.bmp");
		PlayerImage->Cut({ 256,256 });

		PlayerImage = GameEngineImageManager::GetInst()->Find("RockMan_Move_left.bmp");
		PlayerImage->Cut({ 256,256 });

		PlayerImage = GameEngineImageManager::GetInst()->Find("RockMan_Move_Right.bmp");
		PlayerImage->Cut({ 256,256 });

		PlayerImage = GameEngineImageManager::GetInst()->Find("RockMan_Jump_Right.bmp");
		PlayerImage->Cut({ 256,256 });

		PlayerImage = GameEngineImageManager::GetInst()->Find("RockMan_Jump_Left.bmp");
		PlayerImage->Cut({ 256,256 });

		PlayerImage = GameEngineImageManager::GetInst()->Find("RockMan_Attack_Left.bmp");
		PlayerImage->Cut({ 256,256 });

		PlayerImage = GameEngineImageManager::GetInst()->Find("RockMan_Attack_Right.bmp");
		PlayerImage->Cut({ 256,256 });

		PlayerImage = GameEngineImageManager::GetInst()->Find("Bullet.bmp");
		PlayerImage->Cut({ 256,256 });
	}


	//UI비트맵 초기화
	{
		GameEngineImage* UIImage;
		UIImage = GameEngineImageManager::GetInst()->Find("Title.bmp");
		UIImage->Cut({ 1024,960 });
	}

	//몬스터 미트맵 초기화
	{
		//스테이지1 보스 컷맨 
		{
			GameEngineImage* CutmanImage;
			CutmanImage = GameEngineImageManager::GetInst()->Find("Cutman_Right.bmp");
			CutmanImage->Cut({ 256,256 });

			CutmanImage = GameEngineImageManager::GetInst()->Find("Cutman_Left.bmp");
			CutmanImage->Cut({ 256,256 });
		}
	}
}

void RockMan::InitKey()
{
	//키초기화
	{
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("Jump", 'K');
		GameEngineInput::GetInst()->CreateKey("Attack", 'J');
	}

}
