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


//������ ����� �� �� �ε�
void TitleLevel::Loading()
{

}

void TitleLevel::LevelChangeStart()
{
	CreateActor<TitleLogo>(static_cast<int>(GameLayer::Background), "TitleLogo");
}

void TitleLevel::Update()
{
}
