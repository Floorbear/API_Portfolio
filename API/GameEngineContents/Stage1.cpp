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

}


