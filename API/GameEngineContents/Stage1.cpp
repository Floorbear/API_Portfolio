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
#include "SuperCutter.h"
#include "SuperCutterSpawner.h"
#include "Flea.h"
#include "OctopusBattery.h"
#include "BossEntranceDoor.h"
#include "Cutman.h"

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
		//맵이동 충돌체
		{
			GameEngineCollision* NewMoveNextCol = StartBackground_->CreateCollision("MoveNext", { 50,10 }, { 3939,0 });
			AllBackground_[0]->AllMoveNextCol_.push_back(NewMoveNextCol);
		}
		//낭떨어지 , 가시 충돌체
		{
			GameEngineCollision* NewObstacleCol = StartBackground_->CreateCollision("ObstacleCol", { 150,10 }, { 2753 ,950 });
		}

	}

	// Map index = 1
	{
		//맵 이동 충돌체
		{
			GameEngineCollision* NewMovePrevCol = StartBackground_->CreateCollision("MovePrev", { 50,10 }, { 3939,-30 });
			AllBackground_[1]->AllMovePrevCol_.push_back(NewMovePrevCol);

			NewMovePrevCol = StartBackground_->CreateCollision("MovePrev", { 135,10 }, { 3735,-30 });
			AllBackground_[1]->AllMovePrevCol_.push_back(NewMovePrevCol);

			GameEngineCollision* NewMoveNextCol = StartBackground_->CreateCollision("MoveNext", { 50,10 }, { 3939,-1035 });
			AllBackground_[1]->AllMoveNextCol_.push_back(NewMoveNextCol);

		}
	}

	// Map Index = 2
	{
		//맵 이동 충돌체
		{
			//Down
			GameEngineCollision* NewMovePrevCol = StartBackground_->CreateCollision("MovePrev", { 50,10 }, { 3939,-1065 });
			AllBackground_[2]->AllMovePrevCol_.push_back(NewMovePrevCol);

			NewMovePrevCol = StartBackground_->CreateCollision("MovePrev", { 200,10 }, { 3485,-1065 });
			AllBackground_[2]->AllMovePrevCol_.push_back(NewMovePrevCol);

			NewMovePrevCol = StartBackground_->CreateCollision("MovePrev", { 100,10 }, { 3100,-1065 });
			AllBackground_[2]->AllMovePrevCol_.push_back(NewMovePrevCol);


			//Up

			GameEngineCollision* NewMoveNextCol = StartBackground_->CreateCollision("MoveNext", { 50,10 }, { 3939,-2050 });
			AllBackground_[2]->AllMoveNextCol_.push_back(NewMoveNextCol);
		}
	}

	// Map Index = 3
	{
		//맵 이동 충돌체
		{
			//Down
			GameEngineCollision* NewMovePrevCol = StartBackground_->CreateCollision("MovePrev", { 50,10 }, { 3939,-2080});
			AllBackground_[3]->AllMovePrevCol_.push_back(NewMovePrevCol);

			NewMovePrevCol = StartBackground_->CreateCollision("MovePrev", { 120,10 }, { 3570,-2080 });
			AllBackground_[3]->AllMovePrevCol_.push_back(NewMovePrevCol);

			NewMovePrevCol = StartBackground_->CreateCollision("MovePrev", { 140,10 }, { 3150,-2080 });
			AllBackground_[3]->AllMovePrevCol_.push_back(NewMovePrevCol);

			//UP
			GameEngineCollision* NewMoveNextCol = StartBackground_->CreateCollision("MoveNext", { 50,10 }, { 3297,-3080 });
			AllBackground_[3]->AllMoveNextCol_.push_back(NewMoveNextCol);

		}
	}

	//Map Index = 4
	{
		//맵 이동 충돌체
		{
			//Down
			GameEngineCollision* NewMovePrevCol = StartBackground_->CreateCollision("MovePrev", { 200,10 }, { 3197,-3110 });
			AllBackground_[4]->AllMovePrevCol_.push_back(NewMovePrevCol);

			//UP
			GameEngineCollision* NewMoveNextCol = StartBackground_->CreateCollision("MoveNext", { 50,10 }, { 5982,-4094 });
			AllBackground_[4]->AllMoveNextCol_.push_back(NewMoveNextCol);
		}
		//낭떨어지 , 가시 충돌체
		{
			GameEngineCollision* NewObstacleCol = StartBackground_->CreateCollision("ObstacleCol", { 150,10 }, { 4743, -3100});
		}
	}
	
	//Map Index = 5
	{
		//맵 이동 충돌체
		{
			//Down
			GameEngineCollision* NewMovePrevCol = StartBackground_->CreateCollision("MovePrev", { 50,10 }, { 5982,-4124 });
			AllBackground_[5]->AllMovePrevCol_.push_back(NewMovePrevCol);

			//UP
			GameEngineCollision* NewMoveNextCol = StartBackground_->CreateCollision("MoveNext", { 50,10 }, { 5985,-5119 });
			AllBackground_[5]->AllMoveNextCol_.push_back(NewMoveNextCol);
		}
	}

	//Map Index = 6
	{
		//맵 이동 충돌체
		{
			//Down
			GameEngineCollision* NewMovePrevCol = StartBackground_->CreateCollision("MovePrev", { 50,10 }, { 5985,-5149 });
			AllBackground_[6]->AllMovePrevCol_.push_back(NewMovePrevCol);

			//UP
			GameEngineCollision* NewMoveNextCol = StartBackground_->CreateCollision("MoveNext", { 50,10 }, { 5281,-6136 });
			AllBackground_[6]->AllMoveNextCol_.push_back(NewMoveNextCol);
		}
	}

	//Map Index = 7
	{
		//맵 이동 충돌체
		{
			//Down
			GameEngineCollision* NewMovePrevCol = StartBackground_->CreateCollision("MovePrev", { 50,10 }, { 5281,-6166 });
			AllBackground_[7]->AllMovePrevCol_.push_back(NewMovePrevCol);
			//UP
			GameEngineCollision* NewMoveNextCol = StartBackground_->CreateCollision("MoveNext", { 50,10 }, { 7969,-6250 });
			AllBackground_[7]->AllMoveNextCol_.push_back(NewMoveNextCol);
		}
	}

	//Map Index = 8
	{
		//맵 이동 충돌체
		{
			//Down
			GameEngineCollision* NewMovePrevCol = StartBackground_->CreateCollision("MovePrev", { 50,10 }, { 7969,-6220 });
			AllBackground_[8]->AllMovePrevCol_.push_back(NewMovePrevCol);

			//Up
			GameEngineCollision* NewMoveNextCol = StartBackground_->CreateCollision("MoveNext", { 50,10 }, { 7329,-5170 });
			AllBackground_[8]->AllMoveNextCol_.push_back(NewMoveNextCol);

			NewMoveNextCol = StartBackground_->CreateCollision("MoveNext", { 600,10 }, { 7900,-5170 });
			AllBackground_[8]->AllMoveNextCol_.push_back(NewMoveNextCol);
		}
	}

	//Map Index = 9
	{
		//맵 이동 충돌체
		{
			//Down
			GameEngineCollision* NewMovePrevCol = StartBackground_->CreateCollision("MovePrev", { 50,10 }, { 7329,-5140 });
			AllBackground_[9]->AllMovePrevCol_.push_back(NewMovePrevCol);
		}
	}

}

void Stage1::InitBackground()
{
	//백그라운드 로드

	// Map Index = 0
	{
		BackGround* NewBackground = CreateActor<BackGround>(static_cast<int>(GameLayer::Background), "Stage1_0");
		NewBackground->SetIndex(0);
		StartBackground_ = NewBackground;
		NewBackground->SetSpawnPoint({ 508,589.43 }); //체크포인트
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

	//Map Index = 3
	{
		BackGround* NewBackground = CreateActor<BackGround>(static_cast<int>(GameLayer::Background), "Stage1_3");
		NewBackground->SetIndex(3);
		NewBackground->SetPosition({ 3072,-3072 });
		AllBackground_.push_back(NewBackground);
	}

	//Map Index = 4
	{
		BackGround* NewBackground = CreateActor<BackGround>(static_cast<int>(GameLayer::Background), "Stage1_4");
		NewBackground->SetIndex(4);
		NewBackground->SetPosition({ 3072,-4096 });
		AllBackground_.push_back(NewBackground);
	}

	//Map Index = 5
	{
		BackGround* NewBackground = CreateActor<BackGround>(static_cast<int>(GameLayer::Background), "Stage1_5");
		NewBackground->SetIndex(5);
		NewBackground->SetPosition({ 5120,-5120 });
		AllBackground_.push_back(NewBackground);
	}

	//Map Index = 6
	{
		BackGround* NewBackground = CreateActor<BackGround>(static_cast<int>(GameLayer::Background), "Stage1_6");
		NewBackground->SetIndex(6);
		NewBackground->SetPosition({ 5120,-6144 });
		AllBackground_.push_back(NewBackground);
	}

	//Map Index = 7
	{
		BackGround* NewBackground = CreateActor<BackGround>(static_cast<int>(GameLayer::Background), "Stage1_7");
		NewBackground->SetIndex(7);
		NewBackground->SetPosition({ 5120,-7168 });
		AllBackground_.push_back(NewBackground);
	}

	//Map Index = 8
	{
		BackGround* NewBackground = CreateActor<BackGround>(static_cast<int>(GameLayer::Background), "Stage1_8");
		NewBackground->SetIndex(8);
		NewBackground->SetPosition({ 7168,-6144 });
		AllBackground_.push_back(NewBackground);
	}

	//Map Index = 9
	{
		BackGround* NewBackground = CreateActor<BackGround>(static_cast<int>(GameLayer::Background), "Stage1_9");
		NewBackground->SetIndex(9);
		NewBackground->SetPosition({ 7168,-5120 });
		AllBackground_.push_back(NewBackground);
	}

	//Map Index = 10
	{
		BackGround* NewBackground = CreateActor<BackGround>(static_cast<int>(GameLayer::Background), "Stage1_10");
		NewBackground->SetIndex(10);
		NewBackground->SetPosition({ 9216,-5120 });
		AllBackground_.push_back(NewBackground);
	}

	//Map Index = 11
	{
		BackGround* NewBackground = CreateActor<BackGround>(static_cast<int>(GameLayer::Background), "Stage1_11");
		NewBackground->SetIndex(11);
		NewBackground->SetPosition({ 12288,-5120 });
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
		AllBackground_[2]->UpBackground_ = AllBackground_[3];
	}

	//Map Index = 3
	{
		AllBackground_[3]->DownBackground_ = AllBackground_[2];
		AllBackground_[3]->UpBackground_ = AllBackground_[4];
	}

	//Map Index = 4
	{
		AllBackground_[4]->DownBackground_ = AllBackground_[3];
		AllBackground_[4]->UpBackground_ = AllBackground_[5];
	}

	//Map Index = 5
	{
		AllBackground_[5]->DownBackground_ = AllBackground_[4];
		AllBackground_[5]->UpBackground_ = AllBackground_[6];

	}

	//Map Index = 6
	{
		AllBackground_[6]->DownBackground_ = AllBackground_[5];
		AllBackground_[6]->UpBackground_ = AllBackground_[7];
	}

	//Map Index = 7
	{
		AllBackground_[7]->DownBackground_ = AllBackground_[6];
		AllBackground_[7]->UpBackground_ = AllBackground_[8];
	}

	//Map Index = 8
	{
		AllBackground_[8]->DownBackground_ = AllBackground_[7];
		AllBackground_[8]->UpBackground_ = AllBackground_[9];
	}

	//Map Index = 9
	{
		AllBackground_[9]->DownBackground_ = AllBackground_[8];
		AllBackground_[9]->UpBackground_ = AllBackground_[10];
	}

	//Map Index = 10
	{
		AllBackground_[10]->UpBackground_ = AllBackground_[11];
	}


}

void Stage1::InitMonster()
{
	//Map Index : 0
	{

		BunbyHeli* NewMonster = CreateActor<BunbyHeli>(static_cast<int>(GameLayer::Monster), "BunbyHeli");
		NewMonster->SetIndex(0); //몬스터가 존재하는 백그라운드 인덱스
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

	//Map Index : 3
	{
		Blaster* NewBlaster = CreateActor<Blaster>(static_cast<int>(GameLayer::Monster), "Blaster");
		NewBlaster->SetIndex(3);
		NewBlaster->SetDir(float4::RIGHT);
		NewBlaster->SetSpawnPos({ 3544,-2200 });

		NewBlaster = CreateActor<Blaster>(static_cast<int>(GameLayer::Monster), "Blaster");
		NewBlaster->SetIndex(3);
		NewBlaster->SetDir(float4::LEFT);
		NewBlaster->SetSpawnPos({ 3815,-2725 });

		NewBlaster = CreateActor<Blaster>(static_cast<int>(GameLayer::Monster), "Blaster");
		NewBlaster->SetIndex(3);
		NewBlaster->SetDir(float4::LEFT);
		NewBlaster->SetSpawnPos({ 3688,-2909 });
	}

	//Map Index : 4
	{
		//SuperCutterSpawner
		SuperCutterSpawner* NewSuperCutterSpawner = CreateActor<SuperCutterSpawner>(static_cast<int>(GameLayer::Monster), "SuperCutterSpawner");
		NewSuperCutterSpawner->SetIndex(4);
		NewSuperCutterSpawner->SetSpawnPos({ 3640, -3450 });

		Flea* NewFlea = CreateActor<Flea>(static_cast<int>(GameLayer::Monster), "Flea");
		NewFlea->SetIndex(4); 
		NewFlea->SetSpawnPos({ 4317,-3358 });

		NewFlea = CreateActor<Flea>(static_cast<int>(GameLayer::Monster), "Flea");
		NewFlea->SetIndex(4);
		NewFlea->SetSpawnPos({ 4445,-3486 });

		NewFlea = CreateActor<Flea>(static_cast<int>(GameLayer::Monster), "Flea");
		NewFlea->SetIndex(4);
		NewFlea->SetSpawnPos({ 4576,-3613 });

		OctopusBattery* NewOctopusBattery = CreateActor<OctopusBattery>(static_cast<int>(GameLayer::Monster), "OctopusBattery");
		NewOctopusBattery->SetIndex(4);
		NewOctopusBattery->SetDir(true);
		NewOctopusBattery->SetSpawnPos({ 5406,-3435 });

		NewOctopusBattery = CreateActor<OctopusBattery>(static_cast<int>(GameLayer::Monster), "OctopusBattery");
		NewOctopusBattery->SetIndex(4);
		NewOctopusBattery->SetDir(true);
		NewOctopusBattery->SetSpawnPos({ 5533,-3682 });

		NewOctopusBattery = CreateActor<OctopusBattery>(static_cast<int>(GameLayer::Monster), "OctopusBattery");
		NewOctopusBattery->SetIndex(4);
		NewOctopusBattery->SetDir(false);
		NewOctopusBattery->SetSpawnPos({ 5860,-3559 });
	}

	//Map Index : 5
	{
		OctopusBattery* NewOctopusBattery = CreateActor<OctopusBattery>(static_cast<int>(GameLayer::Monster), "OctopusBattery");
		NewOctopusBattery->SetIndex(5);
		NewOctopusBattery->SetDir(true);
		NewOctopusBattery->SetSpawnPos({ 5469,-4591 });

		NewOctopusBattery = CreateActor<OctopusBattery>(static_cast<int>(GameLayer::Monster), "OctopusBattery");
		NewOctopusBattery->SetIndex(5);
		NewOctopusBattery->SetDir(false);
		NewOctopusBattery->SetSpawnPos({ 5981,-4573 });

		NewOctopusBattery = CreateActor<OctopusBattery>(static_cast<int>(GameLayer::Monster), "OctopusBattery");
		NewOctopusBattery->SetIndex(5);
		NewOctopusBattery->SetDir(false);
		NewOctopusBattery->SetSpawnPos({ 5606,-4708 });

		NewOctopusBattery = CreateActor<OctopusBattery>(static_cast<int>(GameLayer::Monster), "OctopusBattery");
		NewOctopusBattery->SetIndex(5);
		NewOctopusBattery->SetDir(false);
		NewOctopusBattery->SetSpawnPos({ 5401,-4840 });
	}

	//Map Index : 6
	{
		OctopusBattery* NewOctopusBattery = CreateActor<OctopusBattery>(static_cast<int>(GameLayer::Monster), "OctopusBattery");
		NewOctopusBattery->SetIndex(6);
		NewOctopusBattery->SetDir(true);
		NewOctopusBattery->SetSpawnPos({ 5658,-5420 });

		NewOctopusBattery = CreateActor<OctopusBattery>(static_cast<int>(GameLayer::Monster), "OctopusBattery");
		NewOctopusBattery->SetIndex(6);
		NewOctopusBattery->SetDir(false);
		NewOctopusBattery->SetSpawnPos({ 5538,-5470 });

		NewOctopusBattery = CreateActor<OctopusBattery>(static_cast<int>(GameLayer::Monster), "OctopusBattery");
		NewOctopusBattery->SetIndex(6);
		NewOctopusBattery->SetDir(false);
		NewOctopusBattery->SetSpawnPos({ 5858,-5730 });

		NewOctopusBattery = CreateActor<OctopusBattery>(static_cast<int>(GameLayer::Monster), "OctopusBattery");
		NewOctopusBattery->SetIndex(6);
		NewOctopusBattery->SetDir(false);
		NewOctopusBattery->SetSpawnPos({ 5985,-5840});
	}

	//Map Index : 7
	{
		SuperCutterSpawner* NewSuperCutterSpawner = CreateActor<SuperCutterSpawner>(static_cast<int>(GameLayer::Monster), "SuperCutterSpawner");
		NewSuperCutterSpawner->SetIndex(7);
		NewSuperCutterSpawner->SetSpawnPos({ 5692,-6500 });

		Flea* NewFlea = CreateActor<Flea>(static_cast<int>(GameLayer::Monster), "Flea");
		NewFlea->SetIndex(7);
		NewFlea->SetSpawnPos({ 6237,-6558 });

		NewFlea = CreateActor<Flea>(static_cast<int>(GameLayer::Monster), "Flea");
		NewFlea->SetIndex(7);
		NewFlea->SetSpawnPos({ 6493,-6686 });

		NewFlea = CreateActor<Flea>(static_cast<int>(GameLayer::Monster), "Flea");
		NewFlea->SetIndex(7);
		NewFlea->SetSpawnPos({ 6683,-6813 });

		BunbyHeli* NewMonster = CreateActor<BunbyHeli>(static_cast<int>(GameLayer::Monster), "BunbyHeli");
		NewMonster->SetIndex(7); 
		NewMonster->SetSpawnPos({ 7549, -6906 });

		NewMonster = CreateActor<BunbyHeli>(static_cast<int>(GameLayer::Monster), "BunbyHeli");
		NewMonster->SetIndex(7);
		NewMonster->SetSpawnPos({ 7989,-6450 });
	}
	
	//Map Index : 8
	{
		Blaster* NewBlaster = CreateActor<Blaster>(static_cast<int>(GameLayer::Monster), "Blaster");
		NewBlaster->SetIndex(8);
		NewBlaster->SetDir(float4::RIGHT);
		NewBlaster->SetSpawnPos({ 7510,-6002 });

		NewBlaster = CreateActor<Blaster>(static_cast<int>(GameLayer::Monster), "Blaster");
		NewBlaster->SetIndex(8);
		NewBlaster->SetDir(float4::RIGHT);
		NewBlaster->SetSpawnPos({ 7320,-5362 });

		OctopusBattery* NewOctopusBattery = CreateActor<OctopusBattery>(static_cast<int>(GameLayer::Monster), "OctopusBattery");
		NewOctopusBattery->SetIndex(8);
		NewOctopusBattery->SetDir(true);
		NewOctopusBattery->SetSpawnPos({ 7395,-5342 });
	}

	//Map Index : 9
	{
		BossEntranceDoor* NewDoor = CreateActor<BossEntranceDoor>(static_cast<int>(GameLayer::Object), "BossEntranceDoor");
		NewDoor->SetPosition({ 9090,-4736});
		NewDoor->SetDoor(false);
	}

	//Map Index : 10
	{
		BossEntranceDoor* NewDoor = CreateActor<BossEntranceDoor>(static_cast<int>(GameLayer::Object), "BossDoor");
		NewDoor->SetPosition({ 12230,-4736 });
		NewDoor->SetDoor(true);
	}

	//Map Index : 11
	{
		Cutman* NewCutman = CreateActor<Cutman>(static_cast<int>(GameLayer::Monster), "Cutman");
		NewCutman->SetIndex(11);
		NewCutman->SetSpawnPos({ 13057,-4392 });
	}
}


