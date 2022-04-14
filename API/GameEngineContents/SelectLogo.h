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
	void StartLogo();//�ΰ� �����ֱ� �����Ѵ�

protected:
	void Start() override;
	void Update() override;

private:
	bool IsOn_1_;//������Ʈ ���ǹ� �ѹ� �����ϱ� ���� �÷���
	GameEngineRenderer* Boss_Name_Renderer_;
	GameEngineRenderer* Clear_Points_Renderer_;
	GameEngineRenderer* Number_Renderer_;

};

