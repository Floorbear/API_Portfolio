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
	//�ػ� ����
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
		//�� ���丮 �ε�
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
		//������Ʈ ���丮 �ε�
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
		//UI ���丮 �ε�
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

	//Select Folder�̹��� �ε�
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

		//Cutman���� �����ֱ�
		SelectDir.MoveParent("Select");
		SelectDir.Move("Logo");
		GameEngineImageManager::GetInst()->FolderImageLoad(SelectDir.GetFullPath(), "SelectFolder_Logo");

	}
}

void RockMan::InitImage()
{
	//ĳ���� ��Ʈ�� �ʱ�ȭ
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


	//UI��Ʈ�� �ʱ�ȭ
	{
		GameEngineImage* UIImage;
		UIImage = GameEngineImageManager::GetInst()->Find("Title.bmp");
		UIImage->Cut({ 1024,960 });
	}

	//���� ��Ʈ�� �ʱ�ȭ
	{
		//��������1 ���� �Ƹ� 
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
	//Ű�ʱ�ȭ
	{
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("Jump", 'K');
		GameEngineInput::GetInst()->CreateKey("Attack", 'J');
	}

}
