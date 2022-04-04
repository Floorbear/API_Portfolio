#include "Stage1.h"
#include "BackGround.h"
#include "GameEngine/GameEngineImageManager.h"
#include "GameEngineBase/GameEngineWindow.h"

Stage1::Stage1()
	: BackGround_(nullptr)
{
}

Stage1::~Stage1()
{
}

void Stage1::Loading()
{
	BackGround_ = CreateActor<BackGround>(10, "BackGround_Stage1");
	BackGround_->CreateRenderer("Stage1_1.bmp",10,RenderPivot::LeftTop);
}

void Stage1::Update()
{
}
