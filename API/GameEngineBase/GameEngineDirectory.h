#pragma once
#include "GameEnginePath.h"
#include <string>
#include <vector>

class GameEngineFile;
class GameEngineDirectory : GameEnginePath
{
public:
	GameEngineDirectory();
	GameEngineDirectory(const std::string& _Path);
	~GameEngineDirectory();


	GameEngineDirectory(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory(const GameEngineDirectory&& _Other) noexcept = delete;
	GameEngineDirectory& operator=(const GameEngineDirectory& _Ohter) = delete;
	GameEngineDirectory& operator=(const GameEngineDirectory&& _Other) noexcept = delete;

	std::vector<GameEngineFile> GetAllFile(const std::string& _Ext = "");

public:
	void MoveParent();
	void MoveParent(const std::string& _Name);
	void Move(const std::string& _Name);
	bool IsRoot();

};

