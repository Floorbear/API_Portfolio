#include "RockmanItem.h"

RockmanItem::RockmanItem()
	:ItemRenderer_(nullptr)
{
	ItemName_[static_cast<int>(ItemType::BigEnergy)] = "BigEnergy";
	ItemName_[static_cast<int>(ItemType::SmallEnergy)] = "SmallEnergy";
	ItemName_[static_cast<int>(ItemType::RedBonusBall)] = "RedBonusBall";
}

RockmanItem::~RockmanItem()
{
}

void RockmanItem::Start()
{
	ItemRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Object));
	ItemRenderer_->CreateAnimation("BonusBall.bmp", "RedBonusBall", 0, 0, 1, false);
	ItemRenderer_->CreateAnimation("RecoveryItem.bmp", "SmallEnergy", 0, 0, 1, false);
	ItemRenderer_->CreateAnimation("RecoveryItem.bmp", "BigEnergy", 1, 2, 1, true);

	ItemRenderer_->ChangeAnimation("RedBonusBall");
}

void RockmanItem::Update()
{
}
