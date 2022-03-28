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

	//이미 있는 이미지 또 만들려 할 때 예외처리
	if (AllRes_.find(EngineName) != AllRes_.end())
	{
		MsgBoxAssert("이미 존재하는 이름의 이미지를 또 만들려고 했습니다.");
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->SetName(EngineName);

	//이미지 생성
	if (NewImage->Create(_DC) == false)
	{
		delete NewImage;
		MsgBoxAssert("이미지를 생성하는데 실패했습니다.");
		return nullptr;
	}

	AllRes_.insert(std::make_pair(EngineName, NewImage));

	return NewImage;
}

GameEngineImage* GameEngineImageManager::Create(const std::string& _Name, const float4& _Scale)
{
	std::string EngineName = GameEngineString::ToUpperReturn(_Name);

	//이미 있는 이미지 또 만들려 할 때 예외처리
	if (AllRes_.find(EngineName) != AllRes_.end())
	{
		MsgBoxAssert("이미 존재하는 이름의 이미지를 또 만들려고 했습니다.");
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->SetName(EngineName);

	//이미지 생성
	if (NewImage->Create(_Scale) == false)
	{
		delete NewImage;
		MsgBoxAssert("이미지를 생성하는데 실패했습니다.");
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