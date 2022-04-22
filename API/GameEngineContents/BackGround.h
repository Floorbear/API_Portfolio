#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <Windows.h>

class GameEngineImage;
class GameEngineRenderer;
class BackGround : public GameEngineActor
{
public:
	BackGround();
	~BackGround();


	BackGround(const BackGround& _Other) = delete;
	BackGround(const BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Ohter) = delete;
	BackGround& operator=(const BackGround&& _Other) noexcept = delete;

public:

	inline float4 GetScale()
	{
		if (BackGroundImage_ == nullptr)
		{
			MsgBoxAssert("BackGroundImage가 설정되지 않았습니다.");
		}
		return BackGroundImage_->GetScale();
	}

	//_Pos에서 BackGroundCol의 픽셀값이 검정인지 확인하는 함수
	bool IsBlocked(const float4& _Pos , unsigned long _RGB = RGB(0,0,0));

protected:
	void Start() override;

private:
	GameEngineRenderer* Renderer_;
	GameEngineImage* BackGroundImage_;
	GameEngineImage* BackGroundColImage_;


};

