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
		GameEngineCollision* NewMoveUpCol = StartBackground_->CreateCollision("MoveUP", { 50,10 }, { 3939,0 });
		{
			AllBackground_[0]->AllMoveUPCol_.push_back(NewMoveUpCol);
		}
	}

	// Map index = 1
	{
		GameEngineCollision* NewMoveDownCol = StartBackground_->CreateCollision("MoveDOWN", { 50,10}, { 3939,-30});
		AllBackground_[1]->AllMoveDownCol_.push_back(NewMoveDownCol);

		NewMoveDownCol = StartBackground_->CreateCollision("MoveDOWN", { 135,10 }, { 3735,-30 });
		AllBackground_[1]->AllMoveDownCol_.push_back(NewMoveDownCol);
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
		AllBackground_.push_back(NewBackground);
	}
	// Map index = 1
	{
		BackGround* NewBackground = CreateActor<BackGround>(static_cast<int>(GameLayer::Background), "Stage1_1");
		NewBackground->SetIndex(1);
		NewBackground->SetPosition({ 3072,-1024 });
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
	}


}

void Stage1::InitMonster()
{
	//디버그용 스폰
	//CreateActor<RockmanMonster>(static_cast<int>(GameLayer::Monster), "BunbyHeli_0");
}


