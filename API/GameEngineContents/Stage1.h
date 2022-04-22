#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineSound.h>
#include "RockManEnum.h"
#include "RockmanStage.h"

class BackGround;
class Stage1 : public RockmanStage
{
public:
	Stage1();
	~Stage1();


	Stage1(const Stage1& _Other) = delete;
	Stage1(const Stage1&& _Other) noexcept = delete;
	Stage1& operator=(const Stage1& _Ohter) = delete;
	Stage1& operator=(const Stage1&& _Other) noexcept = delete;

protected: 
	void InitColPosNScale() override;

	
};

