#pragma once
#include <GameEngine/GameEngineActor.h>

class SelectLogo : public GameEngineActor
{
public:
	SelectLogo();
	~SelectLogo();


	SelectLogo(const SelectLogo& _Other) = delete;
	SelectLogo(const SelectLogo&& _Other) noexcept = delete;
	SelectLogo& operator=(const SelectLogo& _Ohter) = delete;
	SelectLogo& operator=(const SelectLogo&& _Other) noexcept = delete;

public:
	void StartLogo();//로고를 보여주기 시작한다

protected:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* Boss_Name_Renderer_;
	GameEngineRenderer* Clear_Points_Renderer_;
	GameEngineRenderer* Number_Renderer_;

};

