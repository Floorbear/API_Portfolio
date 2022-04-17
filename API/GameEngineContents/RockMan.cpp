#include "RockMan.h"
#include "TitleLevel.h"
#include "SelectLevel.h"
#include "Stage1.h"
#include "GameManager.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineInput.h>

//디버깅 때 콘솔창 띄우기
#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

RockMan::RockMan()
{
}

RockMan::~RockMan()
{
}



void RockMan::GameLoop()
{
	//레벨 변경 명령이 감지되면, 레벨을 변경한다.
	if (GameManager::GetInst()->IsChangeLevel_ == true)
	{
		std::string LevelName = GameManager::GetInst()->GetLevelString();
		ChangeLevel(LevelName);
		GameManager::GetInst()->ResetLevelInfo();
	}
}

void RockMan::GameEnd()
{
	GameManager::GetInst()->Destroy();
}





