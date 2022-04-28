#pragma once
#include <GameEngine/GameEngineCollision.h>
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
public:
	void SetItem(const float4& _Pos); //아이템 액터를 생성할때 무조건 호출해줘야하는 함수
protected:
	void Start() override;
	void Update() override;

private:
	std::string ItemName_[static_cast<int>(ItemType::Max)];
	GameEngineRenderer* ItemRenderer_;
	GameEngineCollision* ItemCol_;
	float Gravity_;
	float DeathTimer_;

	ItemType CurItemType_;

};

