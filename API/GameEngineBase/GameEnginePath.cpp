#include "GameEnginePath.h"

GameEnginePath::GameEnginePath()
{
}

GameEnginePath::GameEnginePath(const std::filesystem::path& _Path)
	:Path_(_Path)
{

}



GameEnginePath::~GameEnginePath()
{
}

std::string GameEnginePath::GetFileName()
{
	return Path_.filename().string();
}

std::string GameEnginePath::GetExtension()
{
	return Path_.extension().string();
}

std::string GameEnginePath::GetFullPath()
{
	return Path_.string();
}

std::string GameEnginePath::GetStem()
{
	return Path_.stem().string();
}

bool GameEnginePath::IsExits()
{
	return std::filesystem::exists(Path_);
}

void GameEnginePath::SetCurrentPath()
{
	//현재 디렉토리
	Path_ = std::filesystem::current_path();
}
