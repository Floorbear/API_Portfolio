#pragma once
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineActor.h>
#include "RockmanUtility.h"
#include "RockManEnum.h"

class RockmanItem : public GameEngineActor
{
public:
	RockmanItem();
	~RockmanItem();


	RockmanItem(const RockmanItem& _Other) = delete;
	RockmanItem(const RockmanItem&& _Other) noexcept = delete;
	RockmanItem& operator=(const RockmanItem& _Ohter) = delete;
	RockmanItem& operator=(const RockmanItem&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;

private:
	std::string ItemName_[static_cast<int>(ItemType::Max)];
	GameEngineRenderer* ItemRenderer_;
};

