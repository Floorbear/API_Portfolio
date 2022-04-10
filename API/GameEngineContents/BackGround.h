#pragma once
#include <GameEngine/GameEngineActor.h>

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
	inline void SetImage(GameEngineImage* _Other)
	{
		BackGroundImage_ = _Other;
	}

	inline GameEngineImage* GetImage() const
	{
		return BackGroundImage_;
	}

protected:
	void Start() override;

private:
	GameEngineImage* BackGroundImage_;
};

