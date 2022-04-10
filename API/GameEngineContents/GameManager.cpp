#include "GameManager.h"
#include "BackGround.h"

GameManager* GameManager::Inst_ = new GameManager();


BackGround* GameManager::GetCurrentBackGround() const
{
	return CurrentBackGround_;
}

GameManager::GameManager()
	:CurrentBackGround_(nullptr)
{
}

GameManager::~GameManager()
{
}