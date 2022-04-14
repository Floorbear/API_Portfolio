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
	bool IsPress_; //Ű�� ������ true
	bool IsOn_; //Update�� ���ǹ��� �ѹ� �����ϸ� true
	float Time_Decide_;
	GameEngineRenderer* BackgroundRenderer_;
};

