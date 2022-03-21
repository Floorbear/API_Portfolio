#include "GameEngine.h"
#include "GameEngineLevel.h"

std::map<std::string, GameEngineLevel*> GameEngine::AllLevel_;
GameEngineLevel* GameEngine::CurrentLevel_ = nullptr;
GameEngineLevel* GameEngine::NextLevel_= nullptr;

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

	//����� ���� �����ϱ�
}

void GameEngine::EngineLoop()
{
	// �������ؿ��� �� �����Ӹ��� üũ�ϰ� ������
	UserContents_->GameLoop();

	//�����Լ�
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

	//�������ؿ��� �� �����Ӹ��� üũ�ϰ� ���� ��
	CurrentLevel_->Update();
	CurrentLevel_->ActorUpdate();
	CurrentLevel_->ActorRender();
	//���� ������Ʈ ����
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

	//�̹����Ŵ��� �ı��Լ��� �־���� 

	GameEngineWindow::Destory();
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