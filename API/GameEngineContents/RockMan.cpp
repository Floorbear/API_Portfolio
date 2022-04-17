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

//����� �� �ܼ�â ����
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
	//���� ���� ����� �����Ǹ�, ������ �����Ѵ�.
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





