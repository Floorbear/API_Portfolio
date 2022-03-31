#pragma once
#include "GameEnginePath.h"


class GameEngineFile : public GameEnginePath
{
public:
	GameEngineFile();
	GameEngineFile(std::filesystem::path _Path);
	GameEngineFile(const std::string& _Path);
	GameEngineFile(const GameEngineFile& _Other);
	~GameEngineFile();



	GameEngineFile& operator=(const GameEngineFile& _Ohter) = delete;
	GameEngineFile& operator=(const GameEngineFile&& _Other) noexcept = delete;


};

