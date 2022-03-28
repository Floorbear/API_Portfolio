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
        MsgBoxAssert("ũ�Ⱑ 0�� �̹����� �����Ϸ��� �߽��ϴ�.");
        return false;
    }
    //GetHDC()�� ȣȯ�Ǵ� ��Ʈ���� �����
    BitMap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _Scale.ix(), _Scale.iy());

    //nullptr���� ���� DC�� ȣȯ�Ǵ� DC�� �ڵ� ������� ����
    ImageDC_ = CreateCompatibleDC(nullptr);

    if (ImageDC_ == nullptr)
    {
        MsgBoxAssert("ImageDC ������ �����߽��ϴ�.");
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


//���� DC�� �ִ� ��Ʈ���� �ڵ� ������� �޾ƿ���, �޾ƿ� �ڵ� ���� ��Ʈ���� Info_�� �����ϴ� �Լ� 
void GameEngineImage::ImageScaleCheck()
{
    HBITMAP CurrentBitMap = (HBITMAP)GetCurrentObject(ImageDC_, OBJ_BITMAP);
    GetObject(CurrentBitMap, sizeof(BITMAP),&Info_);
}
