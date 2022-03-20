#include "GameEngine.h"

GameEngine* GameEngine::UserContents_ = nullptr;
GameEngine::GameEngine()
{
}

GameEngine::~GameEngine()
{
}

void GameEngine::WindowCreate()
{
	GameEngineWindow::GetInst().CreateGameWindow(nullptr, "RockManWindow");
	GameEngineWindow::GetInst().ShowGameWindow();
	GameEngineWindow::GetInst().MessageLoop(EngineInit,EngineLoop);

}

void GameEngine::EngineInit()
{
	UserContents_->GameInit();

	//백버퍼 생성 구현하기
}

void GameEngine::EngineLoop()
{
}

void GameEngine::EngineEnd()
{
}

void GameEngine::ChangeLevel(const std::string& _Name)
{

}