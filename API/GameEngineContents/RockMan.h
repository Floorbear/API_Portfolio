#pragma once
#include <GameEngine/GameEngine.h>

class RockMan : public GameEngine
{
public:
	RockMan();
	~RockMan();


	RockMan(const RockMan& _Other) = delete;
	RockMan(const RockMan&& _Other) noexcept = delete;
	RockMan& operator=(const RockMan& _Ohter) = delete;
	RockMan& operator=(const RockMan&& _Other) noexcept = delete;
protected:
	void GameInit() override;
private:

};

