#pragma once
#include <GameEngine/GameEngineActor.h>
class CutmanClear : public GameEngineActor
{
public:
	CutmanClear();
	~CutmanClear();


	CutmanClear(const CutmanClear& _Other) = delete;
	CutmanClear(const CutmanClear&& _Other) noexcept = delete;
	CutmanClear& operator=(const CutmanClear& _Ohter) = delete;
	CutmanClear& operator=(const CutmanClear&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* BackgroundRenderer_;
	GameEngineRenderer* ClearLogoRenderer_;
	GameEngineRenderer* CutmanLogoRenderer_;
};

