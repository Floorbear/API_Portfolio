#pragma once
#include <filesystem>


class GameEnginePath
{
public:
	GameEnginePath();
	GameEnginePath(const std::filesystem::path& _Path);
	~GameEnginePath();


	GameEnginePath(const GameEnginePath& _Other) = delete;
	GameEnginePath(const GameEnginePath&& _Other) noexcept = delete;
	GameEnginePath& operator=(const GameEnginePath& _Ohter) = delete;
	GameEnginePath& operator=(const GameEnginePath&& _Other) noexcept = delete;

public:
	std::string GetFileName();
	std::string GetExtension();
	std::string GetFullPath();
	std::string GetStem();

	bool IsExits();

	void SetCurrentPath();


protected:
	std::filesystem::path Path_;

};

