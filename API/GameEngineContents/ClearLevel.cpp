#include "ClearLevel.h"
#include <GameEngineContents/RockManEnum.h>
#include "CutmanClear.h"
#include <GameEngineBase/GameEngineSound.h>
#include <string>

ClearLevel::ClearLevel()
{
}

ClearLevel::~ClearLevel()
{
}

void ClearLevel::Loading()
{
}

void ClearLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	CreateActor<CutmanClear>(static_cast<int>(GameLayer::Background), "CutmanClear");
}

void ClearLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

void ClearLevel::Update()
{
}
