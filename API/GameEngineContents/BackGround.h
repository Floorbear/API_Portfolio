#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <Windows.h>

class GameEngineImage;
class GameEngineRenderer;
class RockmanStage;
class Stage1;
class BackGround : public GameEngineActor
{
public:
	friend RockmanStage;
	friend Stage1;
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

	inline size_t GetIndex() const
	{
		return Index_;
	}

	inline void SetIndex(size_t _Index)
	{
		Index_ = _Index;
	}

	inline float4 GetSpawnPoint()
	{
		return SpawnPoint_;
	}

	inline void SetSpawnPoint(const float4& _Pos)
	{
		SpawnPoint_ = _Pos;
	}

	//_Pos에서 BackGroundCol의 픽셀값이 검정인지 확인하는 함수
	bool IsBlocked(const float4& _Pos , unsigned long _RGB = RGB(0,0,0));

protected:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* Renderer_;
	GameEngineImage* BackGroundImage_;
	GameEngineImage* BackGroundColImage_;

	BackGround* DownBackground_;
	BackGround* UpBackground_;

	std::vector<GameEngineCollision*> AllMoveNextCol_;
	std::vector<GameEngineCollision*> AllMovePrevCol_;

	float4 SpawnPoint_;

	size_t Index_;

};

