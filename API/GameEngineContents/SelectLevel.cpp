#include "SelectLevel.h"
#include "SelectBackground.h"
#include <GameEngineContents/RockManEnum.h>
#include "SelectLogo.h"

SelectLevel::SelectLevel()
{
}

SelectLevel::~SelectLevel()
{
}

void SelectLevel::Loading()
{
}

void SelectLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	CreateActor<SelectBackground>(static_cast<int>(GameLayer::Background), "SelectBackground");
}


void SelectLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

void SelectLevel::Update()
{
}
