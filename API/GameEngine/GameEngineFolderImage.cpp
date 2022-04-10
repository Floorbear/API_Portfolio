#include "GameEngineFolderImage.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineDebug.h>

GameEngineFolderImage::GameEngineFolderImage()
{
}

GameEngineFolderImage::~GameEngineFolderImage()
{
    for (size_t i = 0; i < Images_.size(); i++)
    {
        delete Images_[i];;
        Images_[i] = nullptr;
    }
}

bool GameEngineFolderImage::Load(const std::string& _Path)
{
    //디렉토리, 리소스폴더 경로 셋
    GameEngineDirectory ResourcesDir = GameEngineDirectory(_Path);

    //폴더 안의 모든 이미지를 찾는다
    std::vector<GameEngineFile> PlayerImageFileList = ResourcesDir.GetAllFile("bmp");

    Images_.reserve(PlayerImageFileList.size());

    for (size_t i = 0; i < PlayerImageFileList.size(); i++)
    {
        GameEngineImage* Image = new GameEngineImage();
        if (false == Image->Load(PlayerImageFileList[i].GetFullPath()))
        {
            MsgBoxAssert("폴더 이미지 로드 중 실패한 이미지가 존재합니다.");
        }
        Images_.push_back(Image);
    }

    return true;
}
