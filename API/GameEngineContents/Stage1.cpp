#include "Stage1.h"
#include "BackGround.h"
#include "GameEngine/GameEngineImageManager.h"
#include "GameEngineBase/GameEngineWindow.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Player.h"
#include "GameManager.h"
#include "HPBar.h"
#include "Scoreboard.h"
#include "RockManEnum.h"
Stage1::Stage1()
{

}

Stage1::~Stage1()
{
}

void Stage1::InitColPosNScale()
{
	AllMoveUPColScale_[0] = { 50,10 };
	AllMoveUPColPos_[0] = { 3939,0 };


	AllMoveUPColScale_[1] = { 100,100 };
	AllMoveUPColPos_[1] = { 3500,-600 };

}


