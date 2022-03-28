#include "GameEngineImage.h"
#include "GameEngineBase/GameEngineWindow.h"
GameEngineImage::GameEngineImage()
{
}

GameEngineImage::~GameEngineImage()
{
}

bool GameEngineImage::Create(HDC _DC)
{
    ImageDC_ = _DC;
    ImageScaleCheck();
    return true;
}

bool GameEngineImage::Create(float4 _Scale)
{
    if (_Scale.IsZero2D() == true)
    {
        MsgBoxAssert("크기가 0인 이미지를 제작하려고 했습니다.");
        return false;
    }
    //GetHDC()와 호환되는 비트맵을 만든다
    BitMap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _Scale.ix(), _Scale.iy());

    //nullptr쓰면 현재 DC와 호환되는 DC를 핸들 방식으로 제공
    ImageDC_ = CreateCompatibleDC(nullptr);

    if (ImageDC_ == nullptr)
    {
        MsgBoxAssert("ImageDC 생성에 실패했습니다.");
    }

    OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

    ImageScaleCheck();

    return true;
}

void GameEngineImage::BitCopy(GameEngineImage* _Other)
{
    BitCopy(_Other, { 0,0 }, _Other->GetScale(), { 0,0 });
}

void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyScale, const float4& _OtherPivot)
{
    BitBlt(
        ImageDC_,
        _CopyPos.ix(),
        _CopyPos.iy(),
        _CopyScale.ix(),
        _CopyScale.iy(),
        _Other->ImageDC_,
        _OtherPivot.ix(),
        _OtherPivot.iy(),
        SRCCOPY
    );
}


//현재 DC에 있는 비트맵을 핸들 방식으로 받아오고, 받아온 핸들 안의 비트맵을 Info_에 저장하는 함수 
void GameEngineImage::ImageScaleCheck()
{
    HBITMAP CurrentBitMap = (HBITMAP)GetCurrentObject(ImageDC_, OBJ_BITMAP);
    GetObject(CurrentBitMap, sizeof(BITMAP),&Info_);
}
