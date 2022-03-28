#pragma once
#include <GameEngine/GameEngineActor.h>

class TitleBackGround : public GameEngineActor
{
public:
	TitleBackGround();
	~TitleBackGround();


	TitleBackGround(const TitleBackGround& _Other) = delete;
	TitleBackGround(const TitleBackGround&& _Other) noexcept = delete;
	TitleBackGround& operator=(const TitleBackGround& _Ohter) = delete;
	TitleBackGround& operator=(const TitleBackGround&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;
};

