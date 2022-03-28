#include "TitleLevel.h"
#include "TitleLogo.h"
#include "TitleBackGround.h"
#include "Player.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Loading()
{
	CreateActor<TitleLogo>("TitleLogo", 2);
	CreateActor<TitleBackGround>("TitleBackGround", 1);
	CreateActor<Player>("Player", 0);

}

void TitleLevel::Update()
{
}
