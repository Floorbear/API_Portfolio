#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineDebug.h>

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
	void SetImage(GameEngineImage* _Map, GameEngineImage* _ColMap);

	inline float4 GetScale()
	{
		if (BackGroundImage_ == nullptr)
		{
			MsgBoxAssert("BackGroundImage�� �������� �ʾҽ��ϴ�.");
		}
		return BackGroundImage_->GetScale();
	}

	//_Pos���� BackGroundCol�� �ȼ����� �������� Ȯ���ϴ� �Լ�
	bool IsBlocked(float4& _Pos);
	bool IsBlocked(float4& _Pos1, float4& _Pos2);


protected:
	void Start() override;

private:
	GameEngineImage* BackGroundImage_;
	GameEngineImage* BackGroundColImage_;
};

