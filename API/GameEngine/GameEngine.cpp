#include "GameEngine.h"
#include "GameEngineLevel.h"
#include "GameEngineImageManager.h"

std::map<std::string, GameEngineLevel*> GameEngine::AllLevel_;
GameEngineLevel* GameEngine::CurrentLevel_ = nullptr;
GameEngineLevel* GameEngine::NextLevel_= nullptr;
GameEngine* GameEngine::UserContents_ = nullptr;
GameEngineImage* GameEngine::WindowMainImage_ = nullptr;
GameEngineImage* GameEngine::BackBufferImage_= nullptr;



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

	//백버퍼 생성
	WindowMainImage_ = GameEngineImageManager::GetInst()->Create("WindowMain", GameEngineWindow::GetHDC());
	BackBufferImage_ = GameEngineImageManager::GetInst()->Create("BackBuffer", GameEngineWindow::GetScale());
}

void GameEngine::EngineLoop()
{
	// 엔진수준에서 매 프레임마다 체크하고 싶은거
	UserContents_->GameLoop();

	//시점함수
	if (NextLevel_ != nullptr)
	{
		if (CurrentLevel_ != nullptr)
		{
			CurrentLevel_->LevelChangeEnd();
		}
		CurrentLevel_ = NextLevel_;
		if (CurrentLevel_ != nullptr)
		{
			CurrentLevel_->LevelChangeStart();
		}
		NextLevel_ = nullptr;
	}

	if (CurrentLevel_ == nullptr)
	{
		MsgBoxAssert("Level is nullptr => GameEngine Loop Error");
	}

	//레벨수준에서 매 프레임마다 체크하고 싶은 것
	CurrentLevel_->Update();
	CurrentLevel_->ActorUpdate();
	CurrentLevel_->ActorRender();

	//버퍼 업데이트 구현
	WindowMainImage_->BitCopy(BackBufferImage_);

	//엑터 릴리즈 구현
}

void GameEngine::EngineEnd()
{
	UserContents_->GameEnd();
	std::map<std::string, GameEngineLevel*>::iterator StartIter = AllLevel_.begin();
	std::map<std::string, GameEngineLevel*>::iterator EndIter = AllLevel_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (StartIter->second == nullptr)
		{
			continue;
		}
		delete StartIter->second;
	}

	//이미지매니저 파괴함수도 넣어야함 

	GameEngineWindow::Destory();
}

HDC GameEngine::BackBufferDC()
{
	return BackBufferImage_->ImageDC();
}

void GameEngine::ChangeLevel(const std::string& _Name)
{
	std::map<std::string, GameEngineLevel*>::iterator FindIter = AllLevel_.find(_Name);
	if (FindIter == AllLevel_.end())
	{
		MsgBoxAssert("Level Find Error");
		return;
	}
	NextLevel_ = FindIter->second;
}