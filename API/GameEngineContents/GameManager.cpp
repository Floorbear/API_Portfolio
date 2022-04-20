#include "GameManager.h"
#include "BackGround.h"
#include <GameEngineBase/GameEngineInput.h>

GameManager* GameManager::Inst_ = new GameManager();


BackGround* GameManager::GetCurrentBackGround() const
{
	return CurrentBackGround_;
}

void GameManager::Update()
{
	if (GameEngineInput::GetInst()->IsDown("DebugMode") == true)
	{
		IsDebugMode_ = !IsDebugMode_;
	}
}

void GameManager::ChangeLevel(const std::string& _Name)
{
	IsChangeLevel_ = true;
	ChangeLevelName_ = _Name;
}

void GameManager::ResetLevelInfo()
{
	ChangeLevelName_.clear();
	IsChangeLevel_ = false;
}

GameManager::GameManager()
	:CurrentBackGround_(nullptr),
	ChangeLevelName_(),
	IsChangeLevel_(false),
	IsDebugMode_(true)
{
}

GameManager::~GameManager()
{
}