#include "TitleLevel.h"
#include "TitleLogo.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Loading()
{
	GameEngineLevel::CreateActor<TitleLogo>("TitleLogo", 0);
}

void TitleLevel::Update()
{
}
