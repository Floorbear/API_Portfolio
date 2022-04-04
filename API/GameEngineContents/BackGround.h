#pragma once
#include <GameEngine/GameEngineActor.h>

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

protected:
	void Start() override;

private:
	
};

