#pragma once
#include <string>
#include <vector>
#include <GameEngineBase/GameEngineNameObject.h>
#include "GameEngineImage.h"
class GameEngineFolderImage : public GameEngineNameObject
{
public:
	GameEngineFolderImage();
	~GameEngineFolderImage();


	GameEngineFolderImage(const GameEngineFolderImage& _Other) = delete;
	GameEngineFolderImage(const GameEngineFolderImage&& _Other) noexcept = delete;
	GameEngineFolderImage& operator=(const GameEngineFolderImage& _Ohter) = delete;
	GameEngineFolderImage& operator=(const GameEngineFolderImage&& _Other) noexcept = delete;

	bool Load(const std::string& _Path);

	inline GameEngineImage* GetImage(size_t _Index) const
	{
		return Images_[_Index];
	}

private:
	std::vector<GameEngineImage*> Images_;
};

