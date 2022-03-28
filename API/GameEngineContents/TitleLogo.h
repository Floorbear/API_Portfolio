#pragma once
#include <GameEngine/GameEngineActor.h>

class TitleLogo : public GameEngineActor
{
public:
	TitleLogo();
	~TitleLogo();


	TitleLogo(const TitleLogo& _Other) = delete;
	TitleLogo(const TitleLogo&& _Other) noexcept = delete;
	TitleLogo& operator=(const TitleLogo& _Ohter) = delete;
	TitleLogo& operator=(const TitleLogo&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;

};

