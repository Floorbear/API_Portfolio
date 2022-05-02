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
}


