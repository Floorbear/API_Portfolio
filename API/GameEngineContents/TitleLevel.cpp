#include "TitleLevel.h"
#include "TitleLogo.h"
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





void TitleLevel::Update()
{
}

void TitleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	CreateActor<TitleLogo>(static_cast<int>(GameLayer::Background), "TitleLogo");
}

void TitleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}
