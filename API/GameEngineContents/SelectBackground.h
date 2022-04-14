#pragma once
#include <GameEngine/GameEngineActor.h>


class SelectBackground : public GameEngineActor
{
public:
	SelectBackground();
	~SelectBackground();


	SelectBackground(const SelectBackground& _Other) = delete;
	SelectBackground(const SelectBackground&& _Other) noexcept = delete;
	SelectBackground& operator=(const SelectBackground& _Ohter) = delete;
	SelectBackground& operator=(const SelectBackground&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update() override;

private:
	bool IsPress_; //키가 눌리면 true
	bool IsOn_; //Update의 조건문을 한번 실행하면 true
	float Time_Decide_;
	GameEngineRenderer* BackgroundRenderer_;
};

