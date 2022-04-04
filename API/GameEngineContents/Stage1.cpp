#include "Stage1.h"
#include "BackGround.h"
#include "GameEngine/GameEngineImageManager.h"
#include "GameEngineBase/GameEngineWindow.h"
#include "Player.h"

Stage1::Stage1()
{
}

Stage1::~Stage1()
{
}

void Stage1::Loading()
{
	
	BackGround* BackGround_ = CreateActor<BackGround>(0, "BackGround_Stage1");
	BackGround_->CreateRenderer("Stage1_1.bmp",0,RenderPivot::LeftTop);
	Player* RockMan = CreateActor<Player>(3, "Player");
	
}

void Stage1::Update()
{
}
