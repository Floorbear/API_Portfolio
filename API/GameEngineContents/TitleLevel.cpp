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
	CreateActor<TitleLogo>(0,"Title");


}

void TitleLevel::Update()
{
}
