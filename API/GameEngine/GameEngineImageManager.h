#pragma once
#include "GameEngineImage.h"
#include "GameEngineBase/GameEngineMath.h"
#include <string>
#include <map>

class GameEngineImageManager
{
private:
	static GameEngineImageManager* Inst_;

public:
	static inline GameEngineImageManager* GetInst()
	{
		return Inst_;
	}

	static void Destroy()
	{
		if (Inst_ == nullptr)
		{
			return;
		}
		delete Inst_;
		Inst_ = nullptr;
	}

public:

	GameEngineImage* Find(const std::string& _Name);
	//HDC가 존재하는 경우 이미지를 생성하고 HDC와 연결해주는 함수
	GameEngineImage* Create(const std::string& _Name, HDC _DC);
	GameEngineImage* Create(const std::string& _Name, const float4& _Sclae);

private:
	std::map<std::string, GameEngineImage*> AllRes_;

	GameEngineImageManager();
	~GameEngineImageManager();


	GameEngineImageManager(const GameEngineImageManager& _Other) = delete;
	GameEngineImageManager(const GameEngineImageManager&& _Other) noexcept = delete;
	GameEngineImageManager& operator=(const GameEngineImageManager& _Ohter) = delete;
	GameEngineImageManager& operator=(const GameEngineImageManager&& _Other) noexcept = delete;

};

