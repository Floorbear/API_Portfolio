#include "Stage1.h"
#include "BackGround.h"
#include "GameEngine/GameEngineImageManager.h"
#include "GameEngineBase/GameEngineWindow.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Player.h"
#include "GameManager.h"
#include "HPBar.h"
#include "Scoreboard.h"
#include "RockManEnum.h"
#include "RockmanMonster.h"
#include "BunbyHeli.h"
#include "Blaster.h"
Stage1::Stage1()
{

}

Stage1::~Stage1()
{
}

void Stage1::InitColPosNScale()
{
	// Map index = 0
	{
		//���̵� �浹ü
		{
			GameEngineCollision* NewMoveUpCol = StartBackground_->CreateCollision("MoveUP", { 50,10 }, { 3939,0 });
			AllBackground_[0]->AllMoveUPCol_.push_back(NewMoveUpCol);
		}
		//�������� , ���� �浹ü
		{
			GameEngineCollision* NewObstacleCol = StartBackground_->CreateCollision("ObstacleCol", { 150,10 }, { 2753 ,950 });
		}

	}

	// Map index = 1
	{
		//�� �̵� �浹ü
		{
			GameEngineCollision* NewMoveDownCol = StartBackground_->CreateCollision("MoveDOWN", { 50,10 }, { 3939,-30 });
			AllBackground_[1]->AllMoveDownCol_.push_back(NewMoveDownCol);

			NewMoveDownCol = StartBackground_->CreateCollision("MoveDOWN", { 135,10 }, { 3735,-30 });
			AllBackground_[1]->AllMoveDownCol_.push_back(NewMoveDownCol);

			GameEngineCollision* NewMoveUpCol = StartBackground_->CreateCollision("MoveUP", { 50,10 }, { 3939,-1035 });
			AllBackground_[1]->AllMoveUPCol_.push_back(NewMoveUpCol);

		}
	}

	// Map Index = 2
	{
		//�� �̵� �浹ü
		{
			GameEngineCollision* NewMoveDownCol = StartBackground_->CreateCollision("MoveDOWN", { 50,10 }, { 3939,-1065 });
			AllBackground_[2]->AllMoveDownCol_.push_back(NewMoveDownCol);

			NewMoveDownCol = StartBackground_->CreateCollision("MoveDOWN", { 200,10 }, { 3485,-1065 });
			AllBackground_[2]->AllMoveDownCol_.push_back(NewMoveDownCol);

			NewMoveDownCol = StartBackground_->CreateCollision("MoveDOWN", { 100,10 }, { 3100,-1065 });
			AllBackground_[2]->AllMoveDownCol_.push_back(NewMoveDownCol);



		}
	}

}

void Stage1::InitBackground()
{
	//��׶��� �ε�

	// Map Index = 0
	{
		BackGround* NewBackground = CreateActor<BackGround>(static_cast<int>(GameLayer::Background), "Stage1_0");
		NewBackground->SetIndex(0);
		StartBackground_ = NewBackground;
		NewBackground->SetSpawnPoint({ 508,589.43 }); //üũ����Ʈ
		AllBackground_.push_back(NewBackground);
	}
	// Map index = 1
	{
		BackGround* NewBackground = CreateActor<BackGround>(static_cast<int>(GameLayer::Background), "Stage1_1");
		NewBackground->SetIndex(1);
		NewBackground->SetPosition({ 3072,-1024 });
		AllBackground_.push_back(NewBackground);
	}

	//Map Index = 2
	{
		BackGround* NewBackground = CreateActor<BackGround>(static_cast<int>(GameLayer::Background), "Stage1_2");
		NewBackground->SetIndex(2);
		NewBackground->SetPosition({ 3072,-2048 });
		AllBackground_.push_back(NewBackground);
	}
}

void Stage1::ConnectBackground()
{
	//Map Index = 0
	{
		AllBackground_[0]->UpBackground_ = AllBackground_[1];
	}

	//Map Index = 1
	{
		AllBackground_[1]->DownBackground_ = AllBackground_[0];
		AllBackground_[1]->UpBackground_ = AllBackground_[2];
	}

	//Map Index = 2
	{
		AllBackground_[2]->DownBackground_ = AllBackground_[1];
	}


}

void Stage1::InitMonster()
{
	//Map Index : 0
	{
		BunbyHeli* NewMonster = CreateActor<BunbyHeli>(static_cast<int>(GameLayer::Monster), "BunbyHeli");
		NewMonster->SetIndex(0); //���Ͱ� �����ϴ� ��׶��� �ε���
		NewMonster->SetSpawnPos({ 1100, 270 });

		NewMonster = CreateActor<BunbyHeli>(static_cast<int>(GameLayer::Monster), "BunbyHeli");
		NewMonster->SetIndex(0);
		NewMonster->SetSpawnPos({ 1259, 574 });

		NewMonster = CreateActor<BunbyHeli>(static_cast<int>(GameLayer::Monster), "BunbyHeli");
		NewMonster->SetIndex(0);
		NewMonster->SetSpawnPos({ 1320 , 415 });

		NewMonster = CreateActor<BunbyHeli>(static_cast<int>(GameLayer::Monster), "BunbyHeli");
		NewMonster->SetIndex(0);
		NewMonster->SetSpawnPos({2259, 314 });

		NewMonster = CreateActor<BunbyHeli>(static_cast<int>(GameLayer::Monster), "BunbyHeli");
		NewMonster->SetIndex(0);
		NewMonster->SetSpawnPos({ 2525 , 589 });

		Blaster* NewBlaster = CreateActor<Blaster>(static_cast<int>(GameLayer::Monster), "Blaster");
		NewBlaster->SetIndex(0);
		NewBlaster->SetDir(float4::LEFT);
		NewBlaster->SetSpawnPos({ 3815, 490 });

		NewBlaster = CreateActor<Blaster>(static_cast<int>(GameLayer::Monster), "Blaster");
		NewBlaster->SetIndex(0);
		NewBlaster->SetDir(float4::LEFT);
		NewBlaster->SetSpawnPos({ 3302 , 285 });
	}

	//Map Index : 1
	{
		Blaster* NewBlaster = CreateActor<Blaster>(static_cast<int>(GameLayer::Monster), "Blaster");
		NewBlaster->SetIndex(1);
		NewBlaster->SetDir(float4::LEFT);
		NewBlaster->SetSpawnPos({ 3946, -419 });

		NewBlaster = CreateActor<Blaster>(static_cast<int>(GameLayer::Monster), "Blaster");
		NewBlaster->SetIndex(1);
		NewBlaster->SetDir(float4::LEFT);
		NewBlaster->SetSpawnPos({ 3560, -669 });

		NewBlaster = CreateActor<Blaster>(static_cast<int>(GameLayer::Monster), "Blaster");
		NewBlaster->SetIndex(1);
		NewBlaster->SetDir(float4::LEFT);
		NewBlaster->SetSpawnPos({ 3689, -800 });
	}

	//Map Index : 2
	{
		Blaster* NewBlaster = CreateActor<Blaster>(static_cast<int>(GameLayer::Monster), "Blaster");
		NewBlaster->SetIndex(2);
		NewBlaster->SetDir(float4::RIGHT);
		NewBlaster->SetSpawnPos({ 3352 ,-1310 });

		NewBlaster = CreateActor<Blaster>(static_cast<int>(GameLayer::Monster), "Blaster");
		NewBlaster->SetIndex(2);
		NewBlaster->SetDir(float4::LEFT);
		NewBlaster->SetSpawnPos({ 3560, -1570 });

		NewBlaster = CreateActor<Blaster>(static_cast<int>(GameLayer::Monster), "Blaster");
		NewBlaster->SetIndex(2);
		NewBlaster->SetDir(float4::LEFT);
		NewBlaster->SetSpawnPos({ 3815,  -1820 });
	}
}


