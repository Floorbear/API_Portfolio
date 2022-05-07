#pragma once
#include <GameEngine/GameEngineActor.h>

class Cutman;
class BossHPBar : public GameEngineActor
{
public:
	BossHPBar();
	~BossHPBar();


	BossHPBar(const BossHPBar& _Other) = delete;
	BossHPBar(const BossHPBar&& _Other) noexcept = delete;
	BossHPBar& operator=(const BossHPBar& _Ohter) = delete;
	BossHPBar& operator=(const BossHPBar&& _Other) noexcept = delete;

	inline void SetCutman(Cutman* _Cutman)
	{
		Cutman_ = _Cutman;
	}
protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:

private:
	int CurHP_;
	int HPIndex_[7];
	GameEngineRenderer* PerHPRenderer_[7];
	Cutman* Cutman_;
};

