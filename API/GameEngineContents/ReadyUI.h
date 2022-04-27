#pragma once
#include <GameEngine/GameEngineActor.h>
#include "RockManEnum.h"
#include "RockmanUtility.h"
#include <GameEngine/GameEngineRenderer.h>

class ReadyUI : public GameEngineActor
{
public:
	ReadyUI();
	~ReadyUI();


	ReadyUI(const ReadyUI& _Other) = delete;
	ReadyUI(const ReadyUI&& _Other) noexcept = delete;
	ReadyUI& operator=(const ReadyUI& _Ohter) = delete;
	ReadyUI& operator=(const ReadyUI&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* ReadyRenderer_;
	float ReadyEndTimer_;

};

