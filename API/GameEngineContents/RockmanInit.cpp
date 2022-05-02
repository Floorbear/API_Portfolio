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
#include <GameEngineBase/GameEngineSound.h>

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

	//���� ���� �ε�
	{
		GameEngineDirectory SoundDir;
		SoundDir.MoveParent("API");
		SoundDir.Move("Resources");
		SoundDir.Move("Sounds");
		
		std::vector<GameEngineFile> AllSoundList = SoundDir.GetAllFile("mp3");

		for (size_t i = 0; i < AllSoundList.size(); i++)
		{
			GameEngineSound::LoadRes(AllSoundList[i].GetFullPath());
		}
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

		PlayerImage = GameEngineImageManager::GetInst()->Find("RockMan_Climb.bmp");
		PlayerImage->Cut({ 256,256 });

		PlayerImage = GameEngineImageManager::GetInst()->Find("RockMan_ClimbAttack.bmp");
		PlayerImage->Cut({ 256,256 });

		PlayerImage = GameEngineImageManager::GetInst()->Find("RockMan_Hit_Left.bmp");
		PlayerImage->Cut({ 256,256 });

		PlayerImage = GameEngineImageManager::GetInst()->Find("RockMan_Hit_Right.bmp");
		PlayerImage->Cut({ 256,256 });

		PlayerImage = GameEngineImageManager::GetInst()->Find("RockMan_Die.bmp");
		PlayerImage->Cut({ 256,256 });

		PlayerImage = GameEngineImageManager::GetInst()->Find("RockMan_Spawn.bmp");
		PlayerImage->Cut({ 256,256 });


	}

	//��Ÿ ������Ʈ �ʱ�ȭ
	{
		GameEngineImage* ObjectImage;
		ObjectImage = GameEngineImageManager::GetInst()->Find("Bullet.bmp");
		ObjectImage->Cut({ 256,256 });

		ObjectImage = GameEngineImageManager::GetInst()->Find("EnemyBullet.bmp");
		ObjectImage->Cut({ 32,32 });

		ObjectImage = GameEngineImageManager::GetInst()->Find("Explosion.bmp");
		ObjectImage->Cut({ 256,256 });

		ObjectImage = GameEngineImageManager::GetInst()->Find("HitEffect_Center.bmp");
		ObjectImage->Cut({ 256,256 });

		ObjectImage = GameEngineImageManager::GetInst()->Find("HitEffect_Top.bmp");
		ObjectImage->Cut({ 256,256 });

		ObjectImage = GameEngineImageManager::GetInst()->Find("BonusBall.bmp");
		ObjectImage->Cut({ 32,32 });

		ObjectImage = GameEngineImageManager::GetInst()->Find("RecoveryItem.bmp");
		ObjectImage->Cut({ 64,64 });
	}

	//UI��Ʈ�� �ʱ�ȭ
	{
		GameEngineImage* UIImage;
		UIImage = GameEngineImageManager::GetInst()->Find("Title.bmp");
		UIImage->Cut({ 1024,960 });

		UIImage = GameEngineImageManager::GetInst()->Find("PerHP.bmp");
		UIImage->Cut({ 32,32 });

		UIImage = GameEngineImageManager::GetInst()->Find("Numbers.bmp");
		UIImage->Cut({ 32,32 });
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

		//BunbyHeli
		{
			GameEngineImage* BunbyHeli;
			BunbyHeli = GameEngineImageManager::GetInst()->Find("BunbyHeli_Left.bmp");
			BunbyHeli->Cut({ 256,256 });

			BunbyHeli = GameEngineImageManager::GetInst()->Find("BunbyHeli_Right.bmp");
			BunbyHeli->Cut({ 256,256 });
		}

		//Blaster
		{
			GameEngineImage* Blaster;
			Blaster = GameEngineImageManager::GetInst()->Find("Blaster_Close_Left.bmp");
			Blaster->Cut({ 256,256 });
			Blaster = GameEngineImageManager::GetInst()->Find("Blaster_Close_Right.bmp");
			Blaster->Cut({ 256,256 });
			Blaster = GameEngineImageManager::GetInst()->Find("Blaster_Open_Left.bmp");
			Blaster->Cut({ 256,256 });
			Blaster = GameEngineImageManager::GetInst()->Find("Blaster_Open_Right.bmp");
			Blaster->Cut({ 256,256 });
		}

		//SuperCutter
		{
			GameEngineImage* SuperCutter;
			SuperCutter = GameEngineImageManager::GetInst()->Find("SuperCutter_Left.bmp");
			SuperCutter->Cut({ 256,256 });

			SuperCutter = GameEngineImageManager::GetInst()->Find("SuperCutter_Right.bmp");
			SuperCutter->Cut({ 256,256 });
		}

		//Flea
		{
			GameEngineImage* Flea;
			Flea = GameEngineImageManager::GetInst()->Find("Flea.bmp");
			Flea->Cut({ 256,256 });
		}
	}
}

void RockMan::InitKey()
{
	//Ű�ʱ�ȭ
	{
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');
		GameEngineInput::GetInst()->CreateKey("Jump", 'K');
		GameEngineInput::GetInst()->CreateKey("Attack", 'J');
		GameEngineInput::GetInst()->CreateKey("DebugMOde", 'O');
		GameEngineInput::GetInst()->CreateKey("TeleportKey", 'T');
	}

}
