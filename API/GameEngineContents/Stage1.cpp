#include "Stage1.h"
#include "BackGround.h"
#include "GameEngine/GameEngineImageManager.h"
#include "GameEngineBase/GameEngineWindow.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Player.h"
#include "GameManager.h"
#include "HPBar.h"
#include "Scoreboard.h"

Stage1::Stage1()
{
}

Stage1::~Stage1()
{
}

void Stage1::Loading()
{
	

}


void Stage1::Update()
{
}

void Stage1::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	//백그라운드 셋팅
	BackGround* BackGround_ = CreateActor<BackGround>(static_cast<int>(GameLayer::Background), "BackGround_Stage1");
	GameEngineRenderer* Render = BackGround_->CreateRenderer("Stage1_1.bmp", static_cast<int>(GameLayer::Background), RenderPivot::LeftTop);
	GameEngineImage* ColImage = GameEngineImageManager::GetInst()->Find("Stage1_1_Col.bmp");
	BackGround_->SetBackGroundImage(Render->GetImage(), ColImage);
	GameManager::GetInst()->SetCurrentBackGround(BackGround_);

	//UI 셋팅
	CreateActor<HPBar>(static_cast<int>(GameLayer::UI), "HPBar");
	CreateActor<Scoreboard>(static_cast<int>(GameLayer::UI), "Scoreboard");

	Player* RockMan = CreateActor<Player>(static_cast<int>(GameLayer::Player), "Player");
}

void Stage1::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

