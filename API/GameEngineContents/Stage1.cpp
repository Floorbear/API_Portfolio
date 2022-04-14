#include "Stage1.h"
#include "BackGround.h"
#include "GameEngine/GameEngineImageManager.h"
#include "GameEngineBase/GameEngineWindow.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Player.h"
#include "GameManager.h"

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

void Stage1::LevelChangeStart()
{
	//필수 액터 로드
	BackGround* BackGround_ = CreateActor<BackGround>(static_cast<int>(GameLayer::Background), "BackGround_Stage1");
	GameEngineRenderer* Render = BackGround_->CreateRenderer("Stage1_1.bmp", static_cast<int>(GameLayer::Background), RenderPivot::LeftTop);
	GameEngineImage* ColImage = GameEngineImageManager::GetInst()->Find("Stage1_1_Col.bmp");
	BackGround_->SetImage(Render->GetImage(),ColImage);
	Player* RockMan = CreateActor<Player>(static_cast<int>(GameLayer::Player), "Player");

	//게임매니저 셋
	GameManager::GetInst()->SetCurrentBackGround(BackGround_);
}
