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
	bool IsOn_1_;//업데이트 조건문 한번 실행하기 위한 플래그
	GameEngineRenderer* Boss_Name_Renderer_;
	GameEngineRenderer* Clear_Points_Renderer_;
	GameEngineRenderer* Number_Renderer_;

};

