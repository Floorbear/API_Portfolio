#pragma once
#include <GameEngine/GameEngineLevel.h>

class BackGround;
class Stage1 : public GameEngineLevel
{
public:
	Stage1();
	~Stage1();


	Stage1(const Stage1& _Other) = delete;
	Stage1(const Stage1&& _Other) noexcept = delete;
	Stage1& operator=(const Stage1& _Ohter) = delete;
	Stage1& operator=(const Stage1&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;

private:
	
};

