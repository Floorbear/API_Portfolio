#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>

GameEngineImageManager* GameEngineImageManager::Inst_ = new GameEngineImageManager();

GameEngineImage* GameEngineImageManager::Find(const std::string& _Name)
{
	std::string EngineName = GameEngineString::ToUpperReturn(_Name);

	std::map<std::string, GameEngineImage*>::iterator FindIter = AllRes_.find(EngineName);

	if (FindIter == AllRes_.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

GameEngineImage* GameEngineImageManager::Create(const std::string& _Name, HDC _DC)
{
	std::string EngineName = GameEngineString::ToUpperReturn(_Name);

	//�̹� �ִ� �̹��� �� ����� �� �� ����ó��
	if (AllRes_.find(EngineName) != AllRes_.end())
	{
		MsgBoxAssert("�̹� �����ϴ� �̸��� �̹����� �� ������� �߽��ϴ�.");
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->SetName(EngineName);

	//�̹��� ����
	if (NewImage->Create(_DC) == false)
	{
		delete NewImage;
		MsgBoxAssert("�̹����� �����ϴµ� �����߽��ϴ�.");
		return nullptr;
	}

	AllRes_.insert(std::make_pair(EngineName, NewImage));

	return NewImage;
}

GameEngineImage* GameEngineImageManager::Create(const std::string& _Name, const float4& _Scale)
{
	std::string EngineName = GameEngineString::ToUpperReturn(_Name);

	//�̹� �ִ� �̹��� �� ����� �� �� ����ó��
	if (AllRes_.find(EngineName) != AllRes_.end())
	{
		MsgBoxAssert("�̹� �����ϴ� �̸��� �̹����� �� ������� �߽��ϴ�.");
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->SetName(EngineName);

	//�̹��� ����
	if (NewImage->Create(_Scale) == false)
	{
		delete NewImage;
		MsgBoxAssert("�̹����� �����ϴµ� �����߽��ϴ�.");
		return nullptr;
	}

	AllRes_.insert(std::make_pair(EngineName, NewImage));

	return NewImage;
}

GameEngineImageManager::GameEngineImageManager()
{
}

GameEngineImageManager::~GameEngineImageManager()
{
}