#pragma once
#include <GameEngine/GameEngineActor.h>

class HPBar : public GameEngineActor
{
public:
	HPBar();
	~HPBar();


	HPBar(const HPBar& _Other) = delete;
	HPBar(const HPBar&& _Other) noexcept = delete;
	HPBar& operator=(const HPBar& _Ohter) = delete;
	HPBar& operator=(const HPBar&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	GameEngineRenderer* HPBar_;//이거 나중에 변경해야함

};

