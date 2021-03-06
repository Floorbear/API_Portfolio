#include "RockmanItem.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameManager.h"
#include "BackGround.h"
#include "Player.h"
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "RockmanStage.h"

RockmanItem::RockmanItem()
	:ItemRenderer_(nullptr),
	Gravity_(-600.0f),
	CurItemType_(ItemType::SmallEnergy),
	DeathTimer_(4.0f)
{
	ItemName_[static_cast<int>(ItemType::BigEnergy)] = "BigEnergy";
	ItemName_[static_cast<int>(ItemType::SmallEnergy)] = "SmallEnergy";
	ItemName_[static_cast<int>(ItemType::RedBonusBall)] = "RedBonusBall";
	ItemName_[static_cast<int>(ItemType::ClearItem)] = "ClearItem";
}

RockmanItem::~RockmanItem()
{
}

void RockmanItem::SetItem(const float4& _Pos)
{
	//여기에 스케일
	switch (CurItemType_)
	{
	case ItemType::SmallEnergy:
		SetScale({ 64,64 });
		break;
	case ItemType::BigEnergy:
		SetScale({ 64,64 });
		break;
	case ItemType::RedBonusBall:
		SetScale({ 32,32 });
		break;
	case ItemType::ClearItem:
		SetScale({ 64,64 });
		break;
	case ItemType::Max:
		break;
	default:
		break;
	}

	ItemCol_ = CreateCollision("ItemCol", GetScale());

	float4 MovePos = _Pos+float4(0,-15);
	BackGround* CurrentBackground = GameManager::GetInst()->GetCurrentBackGround();
	if (CurrentBackground->IsBlocked(_Pos) == true) //현재 스폰하는 아이템이 블랙 픽셀이면
	{

		while (CurrentBackground->IsBlocked(MovePos) == true)
		{
			MovePos += float4::RIGHT;
		}
	}
	SetPosition(MovePos);
}

void RockmanItem::Start()
{
	//여기에 확률 변수
	GameEngineRandom NewRandom;
	int RandomValue = NewRandom.RandomInt(0, 100);
	if (RandomValue < 70)
	{
		CurItemType_ = ItemType::RedBonusBall;

	}
	else if (RandomValue >= 70 && RandomValue < 90)
	{
		CurItemType_ = ItemType::SmallEnergy;
	}
	else
	{
		CurItemType_ = ItemType::BigEnergy;
	}

	//최종보스 스테이지면, 보스아이템만 뜨게 한다.
	if (GameManager::GetInst()->GetCurrentBackGround()->GetIndex() == 11)
	{
		CurItemType_ = ItemType::ClearItem;
	}

	ItemRenderer_ = CreateRenderer(static_cast<int>(GameLayer::Object));

	ItemRenderer_->SetTransColor(TransColor);
	ItemRenderer_->CreateAnimation("BonusBall.bmp", "RedBonusBall", 0, 0, 1, false);
	ItemRenderer_->CreateAnimation("RecoveryItem.bmp", "SmallEnergy", 0, 0, 1, false);
	ItemRenderer_->CreateAnimation("RecoveryItem.bmp", "BigEnergy", 1, 2, 1, true);
	ItemRenderer_->CreateAnimation("ClearItem.bmp", "ClearItem", 0, 1, 0.8, true);


	//아이템타입에 따른 이미지 변경
	switch (CurItemType_)
	{
	case ItemType::SmallEnergy:
		ItemRenderer_->ChangeAnimation("SmallEnergy");
		break;
	case ItemType::BigEnergy:
		ItemRenderer_->ChangeAnimation("BigEnergy");
		break;
	case ItemType::RedBonusBall:
		ItemRenderer_->ChangeAnimation("RedBonusBall");
		break;
	case ItemType::ClearItem:
		ItemRenderer_->ChangeAnimation("ClearItem");
		break;
	case ItemType::Max:
		break;
	default:
		break;
	}
	
	

}

void RockmanItem::Update()
{
	DeathTimer_ -= GameEngineTime::GetDeltaTime();
	if (DeathTimer_ <= 0)
	{
		if (CurItemType_ != ItemType::ClearItem)
		{
			Death();
		}
	}

	Gravity_ += 1500*GameEngineTime::GetDeltaTime();



	BackGround* CurrentBackground = GameManager::GetInst()->GetCurrentBackGround();
	float4 CheckUpPos = GetPosition() + float4(0, -GetScale().Half().y);
	float4 CheckDownPos = GetPosition() + float4(0, GetScale().Half().y);
	//윗쪽 픽셀 충돌 검사
	if (CurrentBackground->IsBlocked(CheckUpPos) == true)
	{
		Gravity_ = 0;
		SetMove(float4::DOWN);//1픽셀 아래로
	}

	//아랫쪽

	if (CurrentBackground->IsBlocked(CheckDownPos) == false)
	{
		SetMove(float4::DOWN * Gravity_ * GameEngineTime::GetDeltaTime());
	}

	if (ItemCol_->CollisionCheck("Player", CollisionType::Rect, CollisionType::Rect) == true)
	{
		Player* CurPlayer = GameManager::GetInst()->GetPlayer();
		
		//아이템을 먹으면 효과
		RockmanStage* CurrentStage = dynamic_cast<RockmanStage*>(GetLevel());
		switch (CurItemType_)
		{
		case ItemType::SmallEnergy:
			GameEngineSound::SoundPlayOneShot("HPEnergy.mp3");
			CurPlayer->AddPlayerHP(2);

			break;
		case ItemType::BigEnergy:
			GameEngineSound::SoundPlayOneShot("HPEnergy.mp3");
			CurPlayer->AddPlayerHP(10);
			break;
		case ItemType::RedBonusBall:
			GameEngineSound::SoundPlayOneShot("HPEnergy.mp3");
			GameManager::GetInst()->AddScore(1000);
			break;
		case ItemType::ClearItem:
			CurrentStage->Bgm_ = GameEngineSound::SoundPlayControl("Victory.mp3");
			GameManager::GetInst()->ChangeLevel("ClearLevel");
			break;
		case ItemType::Max:
			break;
		default:
			break;
		}
		
		Death();
	}
}
