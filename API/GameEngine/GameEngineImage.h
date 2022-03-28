#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include <Windows.h>

class  GameEngineImage : public GameEngineNameObject
{
public:
	GameEngineImage();
	~GameEngineImage();


	GameEngineImage(const GameEngineImage& _Other) = delete;
	GameEngineImage(const GameEngineImage&& _Other) noexcept = delete;
	GameEngineImage& operator=(const GameEngineImage& _Ohter) = delete;
	GameEngineImage& operator=(const GameEngineImage&& _Other) noexcept = delete;

public:
	inline HDC ImageDC()
	{
		return ImageDC_;
	}
	inline float4 GetScale()
	{
		return float4(static_cast<float>(Info_.bmWidth), static_cast<float>(Info_.bmHeight));
	}

	bool Create(HDC _DC);
	bool Create(float4 _Scale);

	void BitCopy(GameEngineImage* _Other);
	void BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyScale, const float4& _OtherPivot);
private:
	void ImageScaleCheck();

private:
	HDC ImageDC_;
	HBITMAP BitMap_; //��Ʈ���� �ڵ�
	HBITMAP OldBitMap_; //DC�� ����� �Ǹ� �ڵ������� ��������� ��Ʈ�� �ڵ�
	BITMAP Info_;//����ü

};

